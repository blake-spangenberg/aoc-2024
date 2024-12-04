#include <stdio.h>

#include "../1-1/lists.h"

// Note: For dense datasets, a dict-like hash table would be more efficient

static unsigned _num_occurances(const list_t* list, unsigned x)
{
    unsigned count = 0;
    for (unsigned i = 0; i < ARRAY_LEN(list->data); i++) {
        if (list->data[i] == x) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    unsigned sum = 0;
    for (unsigned i = 0; i < ARRAY_LEN(LIST1.data); i++) {
        const unsigned x = LIST1.data[i];
        sum += x * _num_occurances(&LIST2, x);
    }

    printf("%u\n", sum);

    return 0;
}
