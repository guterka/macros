#ifndef MT_H
#define MT_H
#include "da.h"
#include <pthread.h>
DA_STRUCT(pthread_t);

typedef pthread_t_DA mt_Pool;
typedef void * mt_Arg;

#define MT_POOL() (mt_Pool) DA_DEFAULT(pthread_t)
#define MT_JOB_BEGIN(funcname, type) void* funcname (mt_Arg _arg) {	\
  type *arg = (type *) _arg					\
    
#define MT_JOB_END return arg;}

#define MT_START_JOB(pool, funcname, arg, argtype) do {			\
    argtype a = arg;							\
    pthread_t jobId;							\
    DA_APPEND(pool, jobId);						\
    pthread_create(&DA_AT(pool, pool.size - 1), NULL, *(funcname), (mt_Arg) &(a)); \
  } while (0)								\

#define MT_WAIT(pool) do {			\
    for (size_t i = 0; i < (pool).size; i++) {	\
      pthread_join(DA_AT(pool, i), NULL);	\
    }						\
  } while (0)					\


#endif // MT_H
