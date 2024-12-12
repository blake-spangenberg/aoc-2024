#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../util.h"

#if 0
#include "input_test.h"
#else
#include "input.h"
#endif

#define EMPTY (UINT16_MAX)

static void _parse_input(uint8_t parsed_input[INPUT_LEN])
{
    for (unsigned i = 0; i < INPUT_LEN; i++) {
        const char c = INPUT[i];
        uint8_t n = c - '0';
        assert(n < 10);
        parsed_input[i] = n;
    }
}

static void __attribute__((unused)) _filesystem_debug_print(const uint16_t* filesystem, uint64_t filesystem_size)
{
    for (uint64_t addr = 0; addr < filesystem_size; addr++) {
        if (addr % 100 == 0) {
            printf("\n");
        }

        if (filesystem[addr] == EMPTY) {
            putchar('.');
        } else {
            if (filesystem[addr] > 0xF)  {
                printf("_%X", filesystem[addr]);
            } else {
                printf("%X", filesystem[addr]);
            }
        }
    }

    printf("\n");
}

static uint64_t _filesystem_size(uint8_t parsed_input[INPUT_LEN])
{
    uint64_t sum = 0;
    for (unsigned i = 0; i < INPUT_LEN; i++) {
        sum += parsed_input[i];
    }

    return sum;
}

static void _filesystem_init(uint16_t* filesystem, uint64_t filesystem_size, uint8_t parsed_input[INPUT_LEN])
{
    uint64_t addr = 0;
    uint16_t file_id = 0;
    for (unsigned i = 0; i < INPUT_LEN; i++) {
        const uint8_t size = parsed_input[i];
        const uint16_t id = IS_ODD(i) ? EMPTY : file_id++;

        for (unsigned j = 0; j < size; j++) {
            filesystem[addr++] = id;
        }

        assert(file_id < EMPTY - 1);
    }

    assert(addr == filesystem_size);
}

static void _filesystem_defrag(uint16_t* filesystem, uint64_t filesystem_size)
{
    uint16_t* lptr = filesystem;
    uint16_t* rptr = lptr + (filesystem_size - 1);

    while (lptr < rptr) {
        // advance until next empty block is found
        if (*lptr != EMPTY) {
            lptr++;
            continue;
        }

        // advance until the next file block is found
        if (*rptr == EMPTY) {
            rptr--;
            continue;
        }

        // swap
        *lptr = *rptr;
        *rptr = EMPTY;
    }
}

static uint64_t _filesystem_checksum(uint16_t* filesystem, uint64_t filesystem_size)
{
    uint64_t sum = 0;
    for (uint64_t i = 0; i < filesystem_size; i++) {
        if (filesystem[i] == EMPTY) {
            break;
        }
        sum += i * filesystem[i];
    }
    return sum;
}

int main(void)
{
    uint8_t parsed_input[INPUT_LEN];
    _parse_input(parsed_input);

    const uint64_t filesystem_size = _filesystem_size(parsed_input);
    uint16_t filesystem[filesystem_size];
    _filesystem_init(filesystem, filesystem_size, parsed_input);
    _filesystem_defrag(filesystem, filesystem_size);
    // _filesystem_debug_print(filesystem, filesystem_size);
    uint64_t sum = _filesystem_checksum(filesystem, filesystem_size);
    printf("%lu\n", sum);

    return 0;
}

// too low: 156197338403
