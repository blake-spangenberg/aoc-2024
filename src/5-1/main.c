#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../util.h"
#include "input.h"

static bool _check_rule(const page_rule_t* rule, const page_set_t* set)
{
    bool y = false;

    for (unsigned i = 0; i < set->len; i++) {
        const unsigned page = set->pages[i];
        
        if (page == rule->x) {
            // If we already saw y then it's out of order. If it exists later, we don't care because it follows the rule
            return !y;
        }

        if (page == rule->y) {
            y = true;
        }
    }

    return true; // not x and not y, or y only
}

static bool _is_valid(const page_set_t* set)
{
    assert(set->len <= ARRAY_LEN(set->pages));
    
    for (unsigned i = 0; i < ARRAY_LEN(PAGE_RULES); i++) {
        if (!_check_rule(&PAGE_RULES[i], set)) {
            return false;
        }
    }

    return true;
}

static unsigned _middle(const page_set_t* set)
{
    assert(set->len & 1); // assume odd

    return set->pages[set->len / 2];
}

int main(void)
{
    unsigned sum = 0;

    // calculate validity

    for (unsigned i = 0; i < ARRAY_LEN(PAGE_SETS); i++) {
        const page_set_t* set = &PAGE_SETS[i];
        if (_is_valid(set)) {
            sum += _middle(set);
        }
    }

    printf("%d\n", sum);

    return 0;
}
