#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../util.h"
#include "input.h"


static const unsigned ROWS = ARRAY_LEN(PUZZLE.data);
static const unsigned COLS = ARRAY_LEN(*PUZZLE.data);

static const int DIRECTIONS[][2] = {
    {  0,  1 }, // forwards
    {  0, -1 }, // backwards
    {  1,  0 }, // up
    { -1,  0 }, // down
    {  1,  1 }, // diag up-right
    {  1, -1 }, // diag up-left
    { -1,  1 }, // diag down-right
    { -1, -1 }, // diag down-left
};

static const char XMAS[] = "XMAS";

static bool _is_valid(const puzzle_t* puzzle, unsigned row, unsigned col, int row_dir, int col_dir, const char* str)
{
    if (*str == '\0') {
        return true; // null terminator reached in match-string
    }

    if (row >= ROWS || col >= COLS) {
        return false; // beyond puzzle boundaries
    }

    const char c = puzzle->data[row][col];

    if (c != *str) {
        return false; // character breaks match
    }

    return _is_valid(puzzle, row + row_dir, col + col_dir, row_dir, col_dir, str + 1);
}

int main(void)
{
    unsigned count = 0;

    for (unsigned row = 0; row < ROWS; row++) {
        for (unsigned col = 0; col < COLS; col++) {
            for (unsigned i = 0; i < ARRAY_LEN(DIRECTIONS); i++) {
                if (_is_valid(&PUZZLE, row, col, DIRECTIONS[i][0], DIRECTIONS[i][1], XMAS)) {
                    count++;
                }
            }
        }
    }

    printf("%d\n", count);

    return 0;
}
