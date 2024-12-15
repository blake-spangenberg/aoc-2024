#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../util.h"
#include "input.h"

#define TEST_INPUT (0)

#if TEST_INPUT
    #define TIME_ELAPSED (100)
    #define COLS (11)
    #define ROWS (7)
#else
    #define TIME_ELAPSED (100)
    #define COLS (101)
    #define ROWS (103)
#endif

// note: % in C is the remainder, not the modulus
static int32_t _mod(int32_t a, int32_t b)
{
    int32_t r = a % b;
    return r < 0 ? r + b : r;
}

static unsigned _quad(xy_t pos)
{
    STATIC_ASSERT(IS_ODD(COLS), "");
    STATIC_ASSERT(IS_ODD(ROWS), "");

    static const xy_t mid = {
        COLS / 2,
        ROWS / 2,
    };

    if (pos.x == mid.x || pos.y == mid.y) {
        return 4;
    }

    if (pos.y < mid.y) {
        return pos.x < mid.x ? 0 : 1;
    }

    return pos.x < mid.x ? 2 : 3;
}

static void _move_robot(const robot_t* robot, unsigned quads[4])
{
    xy_t pos = robot->pos;

    pos.x = _mod(pos.x + robot->vel.x * TIME_ELAPSED, COLS);
    pos.y = _mod(pos.y + robot->vel.y * TIME_ELAPSED, ROWS);

    // printf("(%d, %d)\n", pos.x, pos.y);

    const unsigned quad = _quad(pos);
    if (quad < 4) {
        quads[quad]++;
    }
}

int main(void)
{
    unsigned quads[4] = {};

    for (unsigned i = 0; i < ARRAY_LEN(ROBOTS.data); i++) {
        _move_robot(&ROBOTS.data[i], quads);
    }

    unsigned total = quads[0] * quads[1] * quads[2] * quads[3];
    printf("%u\n", total);

    // printf("%u = %u, %u, %u, %u\n", total, quads[0], quads[1], quads[2], quads[3]);

    return 0;
}
