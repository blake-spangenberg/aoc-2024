#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../util.h"

#define TEST_DATA (0)

#if TEST_DATA
#include "../3-1/input_test.h"
#else
#include "../3-1/input.h"
#endif

typedef enum {
    PARSER_STATE_OPERATION,
    PARSER_STATE_DO,
    PARSER_STATE_DONT,
    PARSER_STATE_MUL_LOP, // left-hand operand
    PARSER_STATE_MUL_ROP, // right-hand operand
} parser_state_t;

typedef struct {
    parser_state_t state;
    const char* start;
    unsigned lop;
    unsigned sum;
    bool mul_enabled;
} parser_t;

static bool _is_num(const char c)
{
    return c >= '0' && c <= '9';
}

static bool _is_valid_operation_char(const char c)
{
    return (c >= 'a' && c <= 'z') || c == '\'';
}

static bool _matches_op(const char* buff, const unsigned buff_len, const char* op, const unsigned op_len)
{
    if (buff_len < op_len) {
        return false;
    }

    return !strncmp(buff + (buff_len - op_len), op, op_len);
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
        case PARSER_STATE_OPERATION:
            if (!parser->start) {
                if (_is_valid_operation_char(c)) {
                    parser->start = c_ptr;
                }

                break;
            }

            if (c == '(') {
                const unsigned buff_len = c_ptr - parser->start;
                #define MATCHES_OP(op) _matches_op(parser->start, buff_len, (op), sizeof((op)) - 1)
                if (MATCHES_OP("mul")) {
                    parser->state = PARSER_STATE_MUL_LOP;
                } else if (MATCHES_OP("do")) {
                    parser->state = PARSER_STATE_DO;
                } else if (MATCHES_OP("don't")) {
                    parser->state = PARSER_STATE_DONT;
                }

                parser->start = NULL;
                break;
            }

            if (!_is_valid_operation_char(c)) {
                parser->start = NULL;
                break;
            }

            break;
        case PARSER_STATE_DO:
        case PARSER_STATE_DONT:
            if (c == ')') {
                parser->mul_enabled = parser->state == PARSER_STATE_DO;
                // printf("enabled: %d\n", parser->mul_enabled);
            }

            parser->start = NULL;
            parser->state = PARSER_STATE_OPERATION;
            break;
        case PARSER_STATE_MUL_LOP:
            if (c == ',') {
                if (!parser->start) {
                    parser->state = PARSER_STATE_OPERATION;
                    break;
                }

                parser->lop = _parse_operand(parser->start, c_ptr);
                parser->start = NULL;
                parser->state = PARSER_STATE_MUL_ROP;
                break;
            }

            if (!_is_num(c)) {
                parser->start = NULL;
                parser->state = PARSER_STATE_OPERATION;
                break;
            }

            if (!parser->start) {
                parser->start = c_ptr;
            }

            break;
        case PARSER_STATE_MUL_ROP:
            if (c == ')') {

                if (parser->start && parser->mul_enabled) {
                    parser->sum += parser->lop * _parse_operand(parser->start, c_ptr);
                }

                parser->start = NULL;
                parser->state = PARSER_STATE_OPERATION;

                break;
            }

            if (!_is_num(c)) {
                parser->start = NULL;
                parser->state = PARSER_STATE_OPERATION;
                break;
            }

            if (!parser->start) {
                parser->start = c_ptr;
            }

            break;
    }
}

int main(void)
{
    // Init parser state
    parser_t parser = {
        .mul_enabled = true,
    };

    // Iterate all characters through the parser
    for (unsigned i = 0; i < INPUT_LEN; i++) {
        _parse(&parser, (char*) &INPUT[i]);
    }

    // Print result
    printf("%d\n", parser.sum);

    return 0;
}
