#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../util.h"

#define MAX_UNIQUE_STONES (5000)

typedef struct {
    unsigned unique_stones;
    unsigned long stones[MAX_UNIQUE_STONES];
    unsigned long stone_frequencies[MAX_UNIQUE_STONES];
} stone_collection_t;

#define TEST_INPUT (0)

#if TEST_INPUT
    static const unsigned BLINK_COUNT = 25;
    static const unsigned long STONES[] = {
        125, 17,
    };
#else
    static const unsigned BLINK_COUNT = 75;
    static const unsigned long STONES[] = {
        4329, 385, 0, 1444386, 600463, 19, 1, 56615,
    };
#endif

static void _add_stones(stone_collection_t* stones, unsigned long stone, unsigned long count)
{
    for (unsigned i = 0; i < stones->unique_stones; i++) {
        if (stones->stones[i] == stone) {
            stones->stone_frequencies[i] += count;
            return;
        }
    }

    assert(stones->unique_stones < MAX_UNIQUE_STONES);

    stones->stones[stones->unique_stones] = stone;
    stones->stone_frequencies[stones->unique_stones] = count;
    stones->unique_stones++; 
}

static void _stones_init(stone_collection_t* stones)
{
    for (unsigned i = 0; i < ARRAY_LEN(STONES); i++) {
        _add_stones(stones, STONES[i], 1);
    }
}

static void __attribute__((unused)) _stones_print(const stone_collection_t* stones)
{
    for (unsigned i = 0; i < stones->unique_stones; i++) {
        printf("(%lu:%lu) ", stones->stones[i], stones->stone_frequencies[i]);
    }
    printf("\n");
}

static unsigned long _stones_count(const stone_collection_t* stones)
{
    unsigned long count = 0;
    for (unsigned i = 0; i < stones->unique_stones; i++) {
        count += stones->stone_frequencies[i];
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

static void _blink(stone_collection_t* stones)
{
    static stone_collection_t _out_stones = {};
    static stone_collection_t* out_stones = &_out_stones;

    out_stones->unique_stones = 0;

    for (unsigned i = 0; i < stones->unique_stones; i++) {
        unsigned long stone = stones->stones[i];
        unsigned long count = stones->stone_frequencies[i];
        if (!count) {
            continue;
        }

        if (stone == 0) {

            /* Rule 1 - 0 -> 1 */

            _add_stones(out_stones, 1, count);
        } else if (IS_EVEN(_digits(stone))) {

            /* Rule 2 - Split Even Digits */

            unsigned long left, right;
            _split(stone, &left, &right);
            _add_stones(out_stones, left, count);
            _add_stones(out_stones, right, count);
        } else {
            /* Rule 3 - Multiply 2024 */

            _add_stones(out_stones, stone * 2024, count);
        }
    }
    
    *stones = *out_stones;
}

int main(void)
{
    stone_collection_t stones = {};

    _stones_init(&stones);
    // _stones_print(&stones);
    for (unsigned i = 0; i < BLINK_COUNT; i++) {
        _blink(&stones);
        // _stones_print(&stones);
    }

    unsigned long count = _stones_count(&stones);
    printf("%lu\n", count);

    return 0;
}
