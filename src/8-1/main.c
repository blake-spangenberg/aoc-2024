#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../util.h"
#include "input.h"

#define AIR      ('.')
#define ANTINODE ('#')

typedef struct {
    unsigned row;
    unsigned col;
} coordinates_t;

typedef struct {
    unsigned len;
    coordinates_t* list;
} coordinates_list_t;

static coordinates_list_t _collect_antenna(const map_t* map, char antenna)
{
    unsigned alloc_len = 1;
    coordinates_list_t coords = {
        .list = malloc(alloc_len * sizeof(*coords.list)),
    };

    for (unsigned row = 0; row < ROWS; row++) {
        for (unsigned col = 0; col < COLS; col++) {
            if (map->data[row][col] != antenna) {
                continue;
            }

            if (coords.len >= alloc_len) {
                alloc_len *= 2;
                coords.list = realloc(coords.list, alloc_len * sizeof(*coords.list));
            }

            coords.list[coords.len++] = (coordinates_t) { row, col };
        }
    }

    return coords;
}

static void _mark_antinode(map_t* map, coordinates_t a, coordinates_t b)
{
    const coordinates_t antinode = {
        .row = a.row + (a.row - b.row),
        .col = a.col + (a.col - b.col),
    };

    if (antinode.row >= ROWS || antinode.col >= COLS) {
        return;
    }

    map->data[antinode.row][antinode.col] = ANTINODE;
}

static void _mark_antinodes(map_t* map, char antenna, const coordinates_list_t antenna_list)
{
    for (unsigned i = 0; i < antenna_list.len; i++) {
        for (unsigned j = 0; j < antenna_list.len; j++) {
            if (i == j) {
                continue; // can't resonate with yourself
            }

            const coordinates_t a = antenna_list.list[i];
            const coordinates_t b = antenna_list.list[j];

            _mark_antinode(map, a, b);
            _mark_antinode(map, b, a);
        }
    }
}

int main(void)
{
    map_t map = MAP;

    static const unsigned ANTENNA_TYPE_COUNT = ARRAY_LEN(ANTENNA_TYPES);

    coordinates_list_t antenna_positions[ANTENNA_TYPE_COUNT];
    for (unsigned i = 0; i < ANTENNA_TYPE_COUNT; i++) {
        antenna_positions[i] = _collect_antenna(&map, ANTENNA_TYPES[i]);
    }

    for (unsigned i = 0; i < ANTENNA_TYPE_COUNT; i++) {
        _mark_antinodes(&map, ANTENNA_TYPES[i], antenna_positions[i]);
        free(antenna_positions[i].list);
    }

    coordinates_list_t coords = _collect_antenna(&map, ANTINODE);
    printf("%u\n", coords.len);
    free(coords.list);

    return 0;
}
