#include <stdio.h>
#include <stdbool.h>

#include "../util.h"

#define TEST_DATA (0)

#if TEST_DATA
#include "input_test.h"
#else
#include "input.h"
#endif

typedef enum {
    PARSER_STATE_NONE,
    PARSER_STATE_M,
    PARSER_STATE_U,
    PARSER_STATE_L,
    PARSER_STATE_LOP, // left-hand operand
    PARSER_STATE_ROP, // right-hand operand
} parser_state_t;

typedef struct {
    parser_state_t state;
    const char* lop_ptr;
    const char* rop_ptr;
    unsigned lop;
    unsigned sum;
} parser_t;

static bool _is_num(const char c)
{
    return c >= '0' && c <= '9';
}

static unsigned _parse_operand(const char* start, const char* end)
{
    assert(end > start);
    const unsigned len = end - start;
    assert(len >= 1 && len <= 3);
    
    unsigned result = 0;
    while (start < end) {
        result = result * 10 + (*start - '0');
        start++;
    }

    return result;
}

static void _parse(parser_t* parser, const char* c_ptr)
{
    const char c = *c_ptr;

    switch (parser->state) {
        case PARSER_STATE_NONE:
            if (c == 'm') {
                parser->state = PARSER_STATE_M;
            }
            break;
        case PARSER_STATE_M:
            if (c == 'u') {
                parser->state = PARSER_STATE_U;
            } else {
                parser->state = PARSER_STATE_NONE;
            }
            break;
        case PARSER_STATE_U:
            if (c == 'l') {
                parser->state = PARSER_STATE_L;
            } else {
                parser->state = PARSER_STATE_NONE;
            }
            break;
        case PARSER_STATE_L:
            if (c == '(') {
                parser->lop_ptr = NULL;
                parser->rop_ptr = NULL;
                parser->state = PARSER_STATE_LOP;
            } else {
                parser->state = PARSER_STATE_NONE;
            }
            break;
        case PARSER_STATE_LOP:
            if (c == ',') {
                if (!parser->lop_ptr) {
                    parser->state = PARSER_STATE_NONE;
                    break;
                }

                parser->lop = _parse_operand(parser->lop_ptr, c_ptr);
                parser->state = PARSER_STATE_ROP;
                break;
            }

            if (!_is_num(c)) {
                parser->state = PARSER_STATE_NONE;
                break;
            }

            if (!parser->lop_ptr) {
                parser->lop_ptr = c_ptr;
            }

            break;
        case PARSER_STATE_ROP:
            if (c == ')') {
                parser->state = PARSER_STATE_NONE;

                if (parser->rop_ptr) {
                    parser->sum += parser->lop * _parse_operand(parser->rop_ptr, c_ptr);
                }

                break;
            }

            if (!_is_num(c)) {
                parser->state = PARSER_STATE_NONE;
                break;
            }

            if (!parser->rop_ptr) {
                parser->rop_ptr = c_ptr;
            }

            break;
    }
}

int main(void)
{
    // Init parser state
    parser_t parser = {};

    // Iterate all characters through the parser
    for (unsigned i = 0; i < INPUT_LEN; i++) {
        _parse(&parser, (char*) &INPUT[i]);
    }

    // Print result
    printf("%d\n", parser.sum);

    return 0;
}
