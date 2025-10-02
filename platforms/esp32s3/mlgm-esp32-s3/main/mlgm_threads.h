
#ifndef __mlgm_threads_h__
#define __mlgm_threads_h__

#include "mlgm_types.h"
#include "mlgm_errors.h"

////////////////////////////////////////////////////////////////////////////////
// mlgm_thread

struct t_mlgm_thread;

typedef struct t_mlgm_thread mlgm_thread;

typedef mlgm_error (*mlgm_thread_run_fn)(mlgm_thread *thread);

typedef struct t_mlgm_thread
{

    int id;

    int priority;

    void *param;

    mlgm_string name;

    mlgm_thread_run_fn run;

} mlgm_thread;

void mlgm_thread_init(mlgm_thread *self);
void mlgm_thread_start(mlgm_thread *self);
void mlgm_thread_join(mlgm_thread *self);

////////////////////////////////////////////////////////////////////////////////
// mlgm_mutex

typedef struct t_mlgm_mutex
{

    int foo;

} mlgm_mutex;

void mlgm_mutex_init(mlgm_mutex *self);
void mlgm_mutex_lock(mlgm_mutex *self);
void mlgm_mutex_unlock(mlgm_mutex *self);
void mlgm_mutex_destroy(mlgm_mutex *self);

////////////////////////////////////////////////////////////////////////////////

#endif //  __mlgm_threads_h__
