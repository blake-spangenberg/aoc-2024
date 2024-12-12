#ifndef UTIL_H__
#define UTIL_H__

#include <assert.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define ABS_DIFF(a, b) (((a) > (b)) ? (a - b) : (b - a))

#define ARRAY_LEN(array) (sizeof((array)) / sizeof(array[0]))

#define STATIC_ASSERT(condition, message) _Static_assert(condition, message)

#define IS_ODD(n) ((n) & 1)
#define IS_EVEN(n) (!IS_ODD(n)) 

#endif // UTIL_H__
