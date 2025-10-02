
#ifndef __mlgm_defer_h__
#define __mlgm_defer_h__

////////////////////////////////////////////////////////////////////////////////
// typedef

typedef struct t_mlgm_defer_manager mlgm_defer_manager;

typedef struct t_mlgm_deferable mlgm_deferable;

typedef void (*mlgm_deferable_func)(mlgm_deferable *deferable);

////////////////////////////////////////////////////////////////////////////////
// mlgm_defer_manager

typedef struct t_mlgm_defer_manager
{

    mlgm_deferable *head;

} mlgm_defer_manager;

void mlgm_defer_manager_init(mlgm_defer_manager *self);
void mlgm_defer_manager_execute(mlgm_defer_manager *self);
void mlgm_defer_manager_add(mlgm_defer_manager *self, mlgm_deferable *deferable);

////////////////////////////////////////////////////////////////////////////////
// mlgm_deferable

typedef struct t_mlgm_deferable
{

    mlgm_deferable *next;
    mlgm_deferable_func fn;

    void *target;

} mlgm_deferable;

void mlgm_deferable_init(mlgm_deferable *self, void *target, mlgm_deferable_func fn);

////////////////////////////////////////////////////////////////////////////////

#endif //   __mlgm_defer_h__
