#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../util.h"

#define TEST_INPUT (0)

#if TEST_INPUT
    static const unsigned BLINK_COUNT = 6;
    static const unsigned long STONES[] = {
        125, 17,
    };
#else
    static const unsigned BLINK_COUNT = 25;
    static const unsigned long STONES[] = {
        4329, 385, 0, 1444386, 600463, 19, 1, 56615,
    };
#endif

typedef struct stone_t stone_t;

struct stone_t {
    unsigned long value;
    stone_t* next_stone;
};

typedef struct {
    stone_t* first;
} stone_list_t;

static stone_list_t _allocate_stones(void)
{
    stone_t* first = NULL;
    stone_t* last = NULL;

    for (unsigned i = 0; i < ARRAY_LEN(STONES); i++) {

        // Make stone //
        stone_t* stone = malloc(sizeof(stone_t));
        assert(stone);
        *stone = (stone_t) {
            .value = STONES[i],
        };

        // Add stone to list //
        if (last) {
            last->next_stone = stone;
        } else {
            first = stone;
        }

        last = stone;
    }

    return (stone_list_t) {
        first
    };
}

static void __attribute__((unused)) _debug_print(const stone_list_t* stones)
{
    for (const stone_t* stone = stones->first; stone; stone = stone->next_stone) {
        printf("%lu ", stone->value);
    }
    printf("\n");
}

static unsigned _stone_count(const stone_list_t* stones)
{
    unsigned count = 0;

    for (const stone_t* stone = stones->first; stone; stone = stone->next_stone) {
        count++;
    }

    return count;
}

static unsigned _digits(unsigned long n) {
    if (n == 0) {
        return 1;
    }

    unsigned count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }

    return count;
}

static void _split(unsigned long n, unsigned long* out1, unsigned long* out2)
{
    char buff1[30];
    char buff2[20];

    snprintf(buff1, sizeof(buff1), "%lu", n);
    size_t len = strlen(buff1);
    assert(IS_EVEN(len));
    len /= 2;

    strncpy(buff2, buff1 + len, len);
    buff2[len] = '\0';
    *out2 = strtol(buff2, NULL, 10);

    buff1[len] = '\0';
    *out1 = strtol(buff1, NULL, 10);
}

static void _insert_stone(stone_list_t* stones, stone_t** prev_stone, unsigned long value)
{
    stone_t* new_stone = malloc(sizeof(stone_t));

    assert(new_stone);
    if (*prev_stone) {
        *new_stone = (stone_t) {
            .value = value,
            .next_stone = (*prev_stone)->next_stone,
        };
        (*prev_stone)->next_stone = new_stone;
    } else {
        *new_stone = (stone_t) {
            .value = value,
            .next_stone = stones->first,
        };
        stones->first = new_stone;
    }

    (*prev_stone) = new_stone;
}

static void _blink(stone_list_t* stones)
{
    stone_t* prev_stone = NULL;
    int i = 0;
    for (stone_t* stone = stones->first; stone; stone = stone->next_stone) {
        assert(i++ < 10000000);
        if (stone->value == 0) {
            stone->value = 1;
        } else if (IS_EVEN(_digits(stone->value))) {
            unsigned long left, right;
            _split(stone->value, &left, &right);
            stone->value = right;
            _insert_stone(stones, &prev_stone, left);
        } else { 
            stone->value *= 2024;
        }

        prev_stone = stone;

        // _debug_print(stones);
    }
}

int main(void)
{
    stone_list_t stones = _allocate_stones();
    for (unsigned i = 0; i < BLINK_COUNT; i++) {
        _blink(&stones);
        // printf("\n");
    }

    unsigned count = _stone_count(&stones);
    printf("%u\n", count);

    // intentional memory leak (lazy free)
    return 0;
}
