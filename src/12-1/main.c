#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../util.h"
#include "input.h"

#define VISITED ('#')

typedef struct {
    unsigned row;
    unsigned col;
} pos_t;

typedef struct {
    unsigned area;
    unsigned perimiter;
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

static void _count_region(map_t* map, pos_t pos, region_t* region, char region_type)
{
    if (pos.row >= ROWS || pos.col >= COLS) {
        region->perimiter++;
        return;
    }

    char* c = &map->data[pos.row][pos.col];
    if (*c == VISITED) {
        return;
    }

    if (*c != region_type) {
        region->perimiter++;
        return;
    }

    region->area++;
    *c = VISITED;

    static const pos_t DIRECTIONS[] = {
        {  0,  1 },
        {  0, -1 },
        {  1,  0 },
        { -1,  0 },
    };

    for (unsigned i = 0; i < ARRAY_LEN(DIRECTIONS); i++) {
        pos_t new_pos = (pos_t) { pos.row + DIRECTIONS[i].row, pos.col + DIRECTIONS[i].col };
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
        // printf("%c: %u = %u * %u\n", region_type, region.area * region.perimiter, region.area, region.perimiter);
        cost += region.area * region.perimiter;
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
