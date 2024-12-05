#include <stdio.h>
#include <stdbool.h>

#include "../util.h"
#include "../2-1/input.h"

typedef enum {
    PARSER_STATE_INIT,
    PARSER_STATE_NO_DIRECTION,
    PARSER_STATE_ASCENDING,
    PARSER_STATE_DESCENDING,
} parser_state_t;

static bool _is_safe(const report_t* report, unsigned skip_idx)
{
    STATIC_ASSERT(MIN_REPORT_LEN >= 3, "min report len assumption is wrong");

    parser_state_t state = PARSER_STATE_INIT;
    unsigned previous_value = 0;

    for (unsigned i = 0; i < report->data_len; i++) {
        if (skip_idx == i) {
            continue;
        }

        const unsigned value = report->data[i];

        /* Condition 2 */

        if (state != PARSER_STATE_INIT) {
            const unsigned diff = ABS_DIFF(previous_value, value);
            if (diff < 1 || diff > 3) {
                return false;
            }
        }

        /* Condition 1 */

        switch (state) {
            case PARSER_STATE_INIT:
                state = PARSER_STATE_NO_DIRECTION;
                break;
            case PARSER_STATE_NO_DIRECTION:
                state = value > previous_value ? PARSER_STATE_ASCENDING : PARSER_STATE_DESCENDING;
                break;
            case PARSER_STATE_ASCENDING:
                if (value < previous_value) {
                    return false;
                }
                break;
            case PARSER_STATE_DESCENDING:
                if (value > previous_value) {
                    return false;
                }
                break;
        }

        previous_value = value;
    }

    return true;
}

int main(void)
{
    unsigned count = 0;

    for (unsigned i = 0; i < ARRAY_LEN(REPORTS); i++) {

        bool safe = false;
        const report_t* report = &REPORTS[i];

        for (unsigned skip_idx = 0; skip_idx < report->data_len; skip_idx++) {
            if (_is_safe(report, skip_idx)) {
                safe = true;
                break;
            }
        }

        if (safe) {
            count++;
        }
    }

    printf("%u\n", count);

    return 0;
}
