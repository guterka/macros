// Dynamic array macros
#ifndef DA_H
#define DA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DA_RATIO 1.618
#define DA_DEFAULT_CAPACITY 2048
#define MAX(x, y) (x) < (y) ? (y) : (x)
#ifndef assert
#define assert(expr) if (!(expr)) {fprintf(stderr, "ERROR: Assertion failed: %s:%d\n", __FILE__, __LINE__); exit(1);}
#endif // assert


#define DA_STRUCT(type) typedef struct { type *items; size_t size; size_t capacity;} type##_DA;	\
  type##_DA da_##type##_default(void) {					\
    type##_DA d = {							\
      .items = NULL,							\
      .size = 0,							\
      .capacity = DA_DEFAULT_CAPACITY,					\
    };									\
    d.items = malloc(DA_DEFAULT_CAPACITY * sizeof(type));		\
    return d;								\
  }									\
  
#define DA_DEFAULT(type) da_##type##_default()

#define DA_APPEND(da, item) do {					\
    size_t new_cap = MAX((da).capacity + sizeof((item)), (size_t) ((da).capacity * DA_RATIO)); \
    if ((da).size == (da).capacity) {					\
      (da).items = realloc((da).items, new_cap * sizeof((da).items[0])); \
      (da).capacity = new_cap;						\
    }									\
    assert((da).items);							\
    (da).items[(da).size] = (item);					\
    (da).size += 1;							\
  } while(0)								\

#define DA_APPEND_ARR(da, arr, sz) do {					\
    size_t new_cap = MAX((da).capacity + (sz), (size_t) ((da).capacity * DA_RATIO)); \
    if ((da).size + (sz) >= (da).capacity) {				\
      (da).items = realloc((da).items, new_cap * sizeof((da).items[0])); \
      (da).capacity = new_cap;						\
    }									\
    assert((da).items);							\
    memcpy((da).items + (da).size, arr, sizeof((da).items[0]) * (sz));	\
    (da).size += (sz);							\
  } while(0)

#define DA_FREE(da) free(da.items)

#define DA_AT(da, i) ((da).items[(i)])

#define DA_POP(da, i) do {						\
    assert(0 < (i) && (i) < (da).size);					\
    for (size_t pos = (i); pos < (da).size - 1; pos++) (da).items[pos] = (da).items[pos+1]; \
    (da).size--;							\
  } while(0)								\

#define DA_INSERT(da, i, val) do {					\
    assert(0 < (i) && (i) < (da).size);					\
    DA_APPEND((da), DA_AT((da), (da).size - 1));			\
    for (size_t pos = (i); pos < (da).size - 2; pos++) (da).items[pos + 1] = (da).items[pos]; \
    (da).items[(i)] = val;						\
  } while(0)								\

#endif // DA_H
