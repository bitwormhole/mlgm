// mlgm_unit.h
//
// 提供单元测试的功能

#ifndef __mlgm_unit_h__
#define __mlgm_unit_h__

#include "mlgm_types.h"
#include "mlgm_errors.h"
#include "mlgm_structures.h"

typedef mlgm_error (*mlgm_unit_func)(mlgm_unit *unit);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_unit
{

    mlgm_string name;
    mlgm_bool enabled;
    mlgm_int order;
    mlgm_unit_func fn;

    mlgm_app_context *context; // the mlgm_app*

} mlgm_unit;

mlgm_error mlgm_unit_run(mlgm_unit *unit);
mlgm_bool mlgm_unit_is_ready(mlgm_unit *unit);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_unit_holder
{

    mlgm_unit unit;

    struct t_mlgm_unit_holder *prev;
    struct t_mlgm_unit_holder *next;
    struct t_mlgm_unit_holder *self;

} mlgm_unit_holder;

mlgm_unit_holder *mlgm_unit_holder_new();
void mlgm_unit_holder_delete(mlgm_unit_holder *self);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_unit_list
{

    mlgm_unit_holder *first;
    mlgm_unit_holder *last;

} mlgm_unit_list;

void mlgm_unit_list_init(mlgm_unit_list *self);
mlgm_error mlgm_unit_list_run_all(mlgm_unit_list *self, struct t_mlgm_app_context *ac);

void mlgm_unit_list_add(mlgm_unit_list *self, mlgm_unit *unit);
void mlgm_unit_list_add_fn(mlgm_unit_list *self, mlgm_string name, mlgm_unit_func fn);

////////////////////////////////////////////////////////////////////////////////

#endif //  __mlgm_unit_h__
