#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../util.h"
#include "../7-1/input.h"

static long _concat_long(long a, long b)
{
    char buff[42];
    snprintf(buff, sizeof(buff), "%ld%ld", a, b);
    return strtol(buff, NULL, 10);
}

static bool _is_solveable(const equation_t* equation, unsigned index, unsigned long result)
{
    if (index == equation->operands_len) {
        return equation->result == result;
    }

    if (result > equation->result) {
        return false; // bust
    }

    const long operand = equation->operands[index++];

    if (_is_solveable(equation, index, result * operand)) {
        return true;
    }

    if (_is_solveable(equation, index, result + operand)) {
        return true;
    }

    if (_is_solveable(equation, index, _concat_long(result, operand))) {
        return true;
    }

    return false;
}

int main(void)
{
    unsigned long sum = 0;

    for (unsigned i = 0; i < ARRAY_LEN(EQUATIONS); i++) {

        assert(EQUATIONS[i].operands_len);

        if (_is_solveable(&EQUATIONS[i], 1, EQUATIONS[i].operands[0])) {
            sum += EQUATIONS[i].result;
        }
    }

    printf("%lu\n", sum);

    return 0;
}
