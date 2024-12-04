#include <stdio.h>
#include <stdlib.h>

#include "lists.h"

int compare_unsigned(const void* a, const void* b) {
    const unsigned int* a_int = a;
    const unsigned int* b_int = b;
    return (*a_int > *b_int) - (*a_int < *b_int);
}

static void _sort_list(list_t* list)
{
    qsort(list->data, ARRAY_LEN(list->data), sizeof(list->data[0]), compare_unsigned);
}

int main(void)
{
    list_t list1 = LIST1;
    list_t list2 = LIST2;

    _sort_list(&list1);
    _sort_list(&list2);

    unsigned sum = 0;
    for (int i = 0; i < ARRAY_LEN(list1.data); i++) {
        sum += ABS_DIFF(list1.data[i], list2.data[i]);
    }

    printf("%u\n", sum);

    return 0;
}
