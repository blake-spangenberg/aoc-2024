#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../util.h"
#include "../10-1/input.h"

static unsigned _score(const map_t* map, unsigned row, unsigned col, unsigned char height)
{
    if (row >= ROWS || col >= COLS) {
        return 0;
    }

    if (map->data[row][col] != height) {
        return 0;
    }

    if (height == 9) {
        return 1;
    }

    height++;

    static const int DIRECTIONS[][2] = {
        {  0,  1 },
        {  0, -1 },
        {  1,  0 },
        { -1,  0 },
    };

    unsigned score = 0;
    for (unsigned i = 0; i < ARRAY_LEN(DIRECTIONS); i++) {
        score += _score(map, row + DIRECTIONS[i][0], col + DIRECTIONS[i][1], height);
    }

    return score;
}

int main(void)
{
    unsigned sum = 0;

    for (unsigned row = 0; row < ROWS; row++) {
        for (unsigned col = 0; col < COLS; col++) {
            sum += _score(&MAP, row, col, 0);
        }
    }

    printf("%u\n", sum);

    return 0;
}
