#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../util.h"
#include "input.h"

#define PART_TWO (1)

/*

Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

ax = 94
ay = 34
bx = 22
by = 67
px = 8400
py = 5400

assume:
all values positive integers
ax, bx < px
ay, by < py

representative equation

an * ax + bn * bx = px
an * ay + bn * by = py

solve for an:

an = (px - bn * bx) / ax
an = (py - bn * by) / ay

solve for ab:

bn = (px - an * ax) / bx
bn = (py - an * ay) / by

substitute an:

bn = (py * ax - ay * px) / (by * ax - ay * bx)

substitute bn:

an = (px - bn * bx) / ax

calculate cost

cost = 3 * an + bn

*/

static bool _clean_divide(int64_t numerator, int64_t denominator)
{
    return denominator != 0 && numerator % denominator == 0;
}

static int64_t _solve(const machine_t* machine)
{
    const int64_t ax = machine->buttons[0].xy[0];
    const int64_t ay = machine->buttons[0].xy[1];
    const int64_t bx = machine->buttons[1].xy[0];
    const int64_t by = machine->buttons[1].xy[1];

    const int64_t px = machine->prize.xy[0] + PART_TWO * 10000000000000;
    const int64_t py = machine->prize.xy[1] + PART_TWO * 10000000000000;

    assert(ax < px);
    assert(ay < py);
    assert(bx < px);
    assert(by < py);

    int64_t bn;
    {
        int64_t denominator = by * ax - ay * bx;
        int64_t numerator = py * ax - ay * px;
        if (!_clean_divide(numerator, denominator)) {
            return 0;
        }
        bn = numerator / denominator;
    }

    int64_t an;
    {
        int64_t numerator = px - bn * bx;
        int64_t denominator = ax;
        if (!_clean_divide(numerator, denominator)) {
            return 0;
        }
        an = numerator / denominator;
    }

    int64_t cost = 3 * an + bn;

    return cost;
}

int main(void)
{
    int64_t sum = 0;

    for (int i = 0; i < ARRAY_LEN(MACHINES); i++) {
        sum += _solve(&MACHINES[i]);
    }

    printf("%lu\n", sum);

    return 0;
}
