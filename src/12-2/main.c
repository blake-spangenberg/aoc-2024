#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../util.h"
#include "../12-1/input.h"

#define VISITED ('#')

typedef struct {
    unsigned row;
    unsigned col;
} pos_t;

typedef struct {
    unsigned area;
    unsigned corners;
} region_t;

static const pos_t NULL_POS = { UINT32_MAX, UINT32_MAX };

static pos_t _next_unvisited_region(const map_t* map, pos_t pos, char region_type)
{
    for (unsigned row = pos.row; row < ROWS; row++) {
        for (unsigned col = 0; col < COLS; col++) {
            if (map->data[row][col] == region_type) {
                return (pos_t) { row, col };
            }
        }
    }

    return NULL_POS;
}

static bool _is_edge(const map_t* map, pos_t pos, char region_type)
{
    if (pos.row >= ROWS || pos.col >= COLS) {
        return true;
    }

    const char c = map->data[pos.row][pos.col];

    return c != region_type && c != VISITED;
}

static void _count_region(map_t* map, pos_t pos, region_t* region, char region_type)
{
    region->area++;
    map->data[pos.row][pos.col] = VISITED;

    static const pos_t DIRECTIONS[] = {
        {  0,  1 },
        {  1,  0 },
        {  0, -1 },
        { -1,  0 },
    };

    static const pos_t CLOCKWISE_DIAG_DIRECTIONS[] = {
        {  1,  1 },
        {  1, -1 },
        { -1, -1 },
        { -1,  1 },
    };

    for (unsigned i = 0; i < ARRAY_LEN(DIRECTIONS); i++) {
        const pos_t new_pos = (pos_t) {
            pos.row + DIRECTIONS[i].row,
            pos.col + DIRECTIONS[i].col,
        };

        if (_is_edge(map, new_pos, region_type)) {
            unsigned diag_i = (i + 1) % ARRAY_LEN(DIRECTIONS);
            const pos_t clockwise_pos = {
                pos.row + DIRECTIONS[diag_i].row,
                pos.col + DIRECTIONS[diag_i].col,
            };

            const pos_t clockwise_diag_pos = {
                pos.row + CLOCKWISE_DIAG_DIRECTIONS[i].row,
                pos.col + CLOCKWISE_DIAG_DIRECTIONS[i].col,
            };

            if (_is_edge(map, clockwise_pos, region_type) || !_is_edge(map, clockwise_diag_pos, region_type)) {
                region->corners++;
                printf("corner - (%u, %u)\n", pos.row, pos.col);
            }

            continue;
        }

        if (map->data[new_pos.row][new_pos.col] == VISITED) {
            continue; // already explored region
        }

        // otherwise it's unexplored region
        _count_region(map, new_pos, region, region_type);
    }
}

static unsigned _region_type_cost(char region_type)
{
    pos_t pos = {};
    map_t map = MAP;
    unsigned cost = 0;

    while (true) {
        pos = _next_unvisited_region(&map, pos, region_type);

        if (pos.row == NULL_POS.row || pos.col == NULL_POS.col) {
            return cost;
        }

        region_t region = {};
        _count_region(&map, pos, &region, region_type);
        const unsigned edges = region.corners;
        printf("%c: area=%u, corners=%u\n\n", region_type, region.area, region.corners);
        cost += region.area * edges;
    }
}

int main(void)
{
    unsigned sum = 0;

    for (unsigned i = 0; i < ARRAY_LEN(REGION_TYPES); i++) {
        sum += _region_type_cost(REGION_TYPES[i]);
    }

    printf("%u\n", sum);

    return 0;
}

// too low: 848448
