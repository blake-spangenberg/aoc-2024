#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../util.h"
#include "input.h"

#define GUARD_UP    ('^')
#define GUARD_DOWN  ('v')
#define GUARD_RIGHT ('>')
#define GUARD_LEFT  ('<')
#define UNVISITED   ('.')
#define VISITED     ('X')
#define OBSTRUCTION ('#')

typedef struct {
    unsigned row;
    unsigned col;
    int row_dir;
    int col_dir;
} position_t;

static void __attribute__((unused)) _print_position(const position_t* position)
{
    char c;
    
    if (position->row_dir > 0) {
        c = GUARD_DOWN;
    } else if (position->row_dir < 0) {
        c = GUARD_UP;
    } else if (position->col_dir > 0) {
        c = GUARD_RIGHT;
    } else if (position->col_dir < 0) {
        c = GUARD_LEFT;
    } else {
        assert(false);
    }

    printf("(%d, %d, %c)\n", position->row, position->col, c);
}

static position_t _starting_position(const puzzle_t* puzzle)
{
    for (unsigned row = 0; row < ROWS; row++) {
        for (unsigned col = 0; col < COLS; col++) {
            switch (puzzle->data[row][col]) {
                case GUARD_UP:
                    return (position_t) { row, col, -1,  0 };
                case GUARD_DOWN:
                    return (position_t) { row, col,  1,  0 };
                case GUARD_RIGHT:
                    return (position_t) { row, col,  0,  1 };
                case GUARD_LEFT:
                    return (position_t) { row, col,  0, -1 };
                case UNVISITED:
                case VISITED:
                case OBSTRUCTION:
                    break;
                default:
                    assert(false);
            }
        }
    }

    assert(false);
}

static bool _inbounds(const position_t* position)
{
    return position->row < ROWS && position->col < COLS;
}

static position_t _move(const puzzle_t* puzzle, const position_t* pos)
{
    position_t next_pos = {
        .row = pos->row + pos->row_dir,
        .col = pos->col + pos->col_dir,
        .row_dir = pos->row_dir,
        .col_dir = pos->col_dir,
    };

    if (!_inbounds(&next_pos) || puzzle->data[next_pos.row][next_pos.col] != OBSTRUCTION) {
        return next_pos; // unobstructed movement
    }

    next_pos.row = pos->row;
    next_pos.col = pos->col;

    // rotate 90 degrees //

    if (pos->row_dir > 0) {
        next_pos.row_dir = 0;
        next_pos.col_dir = -1;
    } else if (pos->row_dir < 0) {
        next_pos.row_dir = 0;
        next_pos.col_dir = 1;  
    } else if (pos->col_dir > 0) {
        next_pos.row_dir = 1;
        next_pos.col_dir = 0;  
    } else if (pos->col_dir < 0) {
        next_pos.row_dir = -1;
        next_pos.col_dir = 0;  
    }

    return next_pos;
}

static unsigned _calculate_tiles(puzzle_t* puzzle, position_t position)
{
    unsigned tiles = 0;
    while (_inbounds(&position))
    {
        if (puzzle->data[position.row][position.col] != VISITED) {
            puzzle->data[position.row][position.col] = VISITED;
            tiles++;
        }

        // _print_position(&position);
        position = _move(puzzle, &position);
    }

    return tiles;
}

int main(void)
{
    puzzle_t puzzle = PUZZLE;
    const position_t start_position = _starting_position(&puzzle);
    const unsigned tiles = _calculate_tiles(&puzzle, start_position);
    printf("%u\n", tiles);

    return 0;
}
