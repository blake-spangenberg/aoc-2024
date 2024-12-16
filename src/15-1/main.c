#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../util.h"
#include "input.h"

#define AIR   ('.')
#define ROBOT ('@')
#define WALL  ('#')
#define BOX   ('O')

#define UP    ('^')
#define DOWN  ('v')
#define LEFT  ('<')
#define RIGHT ('>')

static uint32_t _box_coord_sum(const map_t* map)
{
    uint32_t sum = 0;
    for (unsigned y = 0; y < ROWS; y++) {
        for (unsigned x = 0; x < COLS; x++) {
            if (map->data[y][x] == BOX) {
                sum += 100 * y + x;
            }
        }
    }

    return sum;
}

static xy_t _find_robot(const map_t* map)
{
    for (unsigned y = 0; y < ROWS; y++) {
        for (unsigned x = 0; x < COLS; x++) {
            if (map->data[y][x] == ROBOT) {
                return (xy_t) { x, y };
            }
        }
    }

    assert(false);
}

static void _move_robot(map_t* map, char move)
{
    static xy_t pos = {};

    if (map->data[pos.y][pos.x] != ROBOT) {
        pos = _find_robot(map);
    }

    xy_t dir;
    switch (move) {
        case UP:
            dir = (xy_t) {  0, -1 };
            break;
        case DOWN:
            dir = (xy_t) {  0,  1 };
            break;
        case LEFT:
            dir = (xy_t) { -1,  0 };
            break;
        case RIGHT:
            dir = (xy_t) {  1,  0 };
            break;
        default:
            assert(false);
    }

    char c;
    do {
        pos.x += dir.x;
        pos.y += dir.y;

        assert(pos.x < COLS && pos.y < ROWS);

        c = map->data[pos.y][pos.x];

        if (c == WALL) {
            return; // cannot move
        }
    } while (c != AIR);

    do {
        c = map->data[pos.y - dir.y][pos.x - dir.x];

        map->data[pos.y][pos.x] = c;

        pos.x -= dir.x;
        pos.y -= dir.y;

        assert(pos.x < COLS && pos.y < ROWS);
    } while (c != ROBOT);

    map->data[pos.y][pos.x] = AIR;
}

int main(void)
{
    map_t map = MAP;

    for (unsigned i = 0; i < ARRAY_LEN(MOVES); i++) {
        _move_robot(&map, MOVES[i]);
    }

    printf("%u\n", _box_coord_sum(&map));

    return 0;
}
