#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../util.h"
#include "input.h"

#define AIR       ('.')
#define ROBOT     ('@')
#define WALL      ('#')
#define BOX_LEFT  ('[')
#define BOX_RIGHT (']')

#define UP    ('^')
#define DOWN  ('v')
#define LEFT  ('<')
#define RIGHT ('>')

typedef struct {
    unsigned len;
    xy_t positions[100];
    char c[100];
} obj_list_t;

static uint32_t _box_coord_sum(const map_t* map)
{
    uint32_t sum = 0;
    for (unsigned y = 0; y < ROWS; y++) {
        for (unsigned x = 0; x < COLS; x++) {
            if (map->data[y][x] == BOX_LEFT) {
                sum += 100 * y + x;
            }
        }
    }

    return sum;
}

static void __attribute__((unused)) _debug_print(const map_t* map)
{
    for (unsigned y = 0; y < ROWS; y++) {
        for (unsigned x = 0; x < COLS; x++) {
            printf("%c ", map->data[y][x]);
        }
        putchar('\n');
    }
    putchar('\n');
}

static void _obj_list_push(const map_t* map, obj_list_t* list, xy_t pos)
{
    assert(list->len < ARRAY_LEN(list->positions));
    list->positions[list->len] = pos;
    list->c[list->len] = map->data[pos.y][pos.x];
    list->len++;

    // printf("(%u, %u) %c\n", pos.x, pos.y, map->data[pos.y][pos.x]);
}

static bool _obj_list_has(const obj_list_t* list, xy_t pos)
{
    for (unsigned i = 0; i < list->len; i++) {
        xy_t check_pos = list->positions[i];
        if (check_pos.x == pos.x && check_pos.y == pos.y) {
            return true;
        }
    }

    return false;
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

static bool _build_collision_tree(const map_t* map, obj_list_t* obj_list, xy_t pos, xy_t dir)
{
    if (_obj_list_has(obj_list, pos)) {
        return true;
    }

    const char c = map->data[pos.y][pos.x];

    if (c == WALL) {
        return false;
    }

    if (c == AIR) {
        return true;
    }

    _obj_list_push(map, obj_list, pos);

    if (c == BOX_LEFT) {
        assert(map->data[pos.y][pos.x + 1] == BOX_RIGHT);
        if (!_build_collision_tree(map, obj_list, (xy_t) {pos.x + 1, pos.y}, dir)) {
            return false;
        }
    } else if (c == BOX_RIGHT) {
        assert(map->data[pos.y][pos.x - 1] == BOX_LEFT);
        if (!_build_collision_tree(map, obj_list, (xy_t) {pos.x - 1, pos.y}, dir)) {
            return false;
        }
    }

    pos.x += dir.x;
    pos.y += dir.y;
    return _build_collision_tree(map, obj_list, pos, dir);
}

static void _move_collision_tree(map_t* map, const obj_list_t* obj_list, xy_t dir)
{
    for (unsigned i = 0; i < obj_list->len; i++) {
        xy_t pos = obj_list->positions[i];
        map->data[pos.y][pos.x] = AIR;
    }

    for (unsigned i = 0; i < obj_list->len; i++) {
        xy_t pos = obj_list->positions[i];
        pos.x += dir.x;
        pos.y += dir.y;
        map->data[pos.y][pos.x] = obj_list->c[i];
    }
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

    obj_list_t obj_list = {};
    if (!_build_collision_tree(map, &obj_list, pos, dir)) {
        return; // movement blocked
    }

    _move_collision_tree(map, &obj_list, dir);

    pos.x += dir.x;
    pos.y += dir.y;
}

int main(void)
{
    map_t map = MAP;

    for (unsigned i = 0; i < ARRAY_LEN(MOVES); i++) {
        // printf("%u: %c\n", i, MOVES[i]);
        // _debug_print(&map);
        _move_robot(&map, MOVES[i]);
    }

    printf("%u\n", _box_coord_sum(&map));

    return 0;
}

// too low: 1417858
