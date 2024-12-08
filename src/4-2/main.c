#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../util.h"
#include "../4-1/input.h"


static const unsigned ROWS = ARRAY_LEN(PUZZLE.data);
static const unsigned COLS = ARRAY_LEN(*PUZZLE.data);

typedef struct {
    int row_dir;
    int col_dir;
    char c;
} corner_t;

typedef struct {
    corner_t corners[4];
} permutation_t;

static bool _is_match(const puzzle_t* puzzle, unsigned row, unsigned col)
{    
    // Start with A as there is only one per match
    if (puzzle->data[row][col] != 'A') {
        return false;
    }

    if (row == 0 || col == 0 || row == ROWS - 1 || col == COLS - 1) {
        return false; // cannot be on perimiter
    }

    // There aren't that many permutations, so just define them statically
    static const permutation_t PERMUTATIONS[] = {
        {{
                {  1,  1, 'M' },
                { -1,  1, 'M' },
                {  1, -1, 'S' },
                { -1, -1, 'S' },
        }},
        {{
            {  1,  1, 'S' },
            { -1,  1, 'S' },
            {  1, -1, 'M' },
            { -1, -1, 'M' },
        }},
        {{
            {  1,  1, 'M' },
            { -1,  1, 'S' },
            {  1, -1, 'M' },
            { -1, -1, 'S' },
        }},
        {{
            {  1,  1, 'S' },
            { -1,  1, 'M' },
            {  1, -1, 'S' },
            { -1, -1, 'M' },
        }},
    };

    for (unsigned i = 0; i < ARRAY_LEN(PERMUTATIONS); i++) {
        bool match = true;
        
        for (unsigned j = 0; j < ARRAY_LEN(PERMUTATIONS[i].corners); j++) {
            const corner_t* corner = &PERMUTATIONS[i].corners[j];
            if (corner->c != puzzle->data[row + corner->row_dir][col + corner->col_dir]) {
                match = false;
                break;
            }
        }

        if (match) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    unsigned count = 0;

    for (unsigned row = 0; row < ROWS; row++) {
        for (unsigned col = 0; col < COLS; col++) {
            if (_is_match(&PUZZLE, row, col)) {
                count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}
