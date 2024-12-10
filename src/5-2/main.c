#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../util.h"
#include "../5-1/input.h"

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

static bool _is_set_valid(const page_set_t* set)
{
    assert(set->len <= ARRAY_LEN(set->pages));
    
    for (unsigned i = 0; i < ARRAY_LEN(PAGE_RULES); i++) {
        if (!_check_rule(&PAGE_RULES[i], set)) {
            return false;
        }
    }

    return true;
}

// a rule is satisfied if no unsatisfied page is the "y" of that rule
static bool _is_rule_satisfied(unsigned rule_idx, const page_set_t* original_set, const bool statisfied_pages[])
{
    const page_rule_t* rule = &PAGE_RULES[rule_idx];

    for (unsigned i = 0; i < original_set->len; i++) {
        if (!statisfied_pages[i] && original_set->pages[i] == rule->y) {
            return false;
        }
    }

    return true;
}

// a page is satisfied if no unsatisfied rule specified that page as it's "x"
static bool _is_page_satisfied(unsigned page, const bool statisfied_rules[PAGE_RULE_COUNT])
{
    for (unsigned i = 0; i < PAGE_RULE_COUNT; i++) {
        if (!statisfied_rules[i] && PAGE_RULES[i].x == page) {
            return false;
        }
    }

    return true;
}

static page_set_t _fix_set(const page_set_t* original_set)
{
    page_set_t fixed_set = {};

    bool statisfied_rules[PAGE_RULE_COUNT] = {};
    bool statisfied_pages[original_set->len];
    memset(statisfied_pages, 0, sizeof(statisfied_pages));

    do {
        // Prune irrelevant rules //

        for (unsigned i = 0; i < PAGE_RULE_COUNT; i++) {
            if (statisfied_rules[i]) {
                continue; // rule already satisfied
            }

            if (_is_rule_satisfied(i, original_set, statisfied_pages)) {
                statisfied_rules[i] = true;
            }
        }

        // Move next satisfied page //

        for (unsigned i = 0; i < original_set->len; i++) {
            if (statisfied_pages[i]) {
                continue; // page already placed
            }

            const unsigned page = original_set->pages[i];

            if (_is_page_satisfied(page, statisfied_rules)) {
                fixed_set.pages[(original_set->len - fixed_set.len) - 1] = page; // move the page
                fixed_set.len++;
                statisfied_pages[i] = true;
                break;
            }            
        }
    } while (fixed_set.len < original_set->len);

    return fixed_set;
}

static unsigned _middle(const page_set_t* set)
{
    assert(set->len & 1); // assume odd

    return set->pages[set->len / 2];
}

int main(void)
{
    unsigned sum = 0;

    for (unsigned i = 0; i < ARRAY_LEN(PAGE_SETS); i++) {
        const page_set_t* orignal_set = &PAGE_SETS[i];
        if (!_is_set_valid(orignal_set)) {
            page_set_t fixed_set = _fix_set(orignal_set);
            sum +=  _middle(&fixed_set);
        }
    }

    printf("%d\n", sum);

    return 0;
}
