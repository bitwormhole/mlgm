#include "module_runtime_test.h"

#include "mlgm_logger.h"
#include "mlgm_unit.h"

#include "units/units.h"

#include "units/rt_unit_example1.c"
#include "units/rt_unit_hash_algorithms.c"

////////////////////////////////////////////////////////////////////////////////

mlgm_error runtime_test_module_on_create(mlgm_module *m);
mlgm_error runtime_test_module_on_run(mlgm_module *m);

////////////////////////////////////////////////////////////////////////////////

mlgm_error runtime_test_module_on_create(mlgm_module *m)
{
    mlgm_logger_debug(NIL, "runtime_test_module_on_create(): todo ...");
    return NIL;
}

mlgm_error runtime_test_module_on_run(mlgm_module *m)
{
    mlgm_logger_debug(NIL, "runtime_test_module_on_run(): todo ...");

    mlgm_unit_list list;
    mlgm_unit_list_init(&list);

    mlgm_unit_list_add_fn(&list, "example1", rt_unit_example1);
    mlgm_unit_list_add_fn(&list, "test_hash_algorithms", rt_unit_test_hash_algorithms);
    mlgm_unit_list_add_fn(&list, "rt_unit_test_sum_struct_bytes_align", rt_unit_test_sum_struct_bytes_align);

    return mlgm_unit_list_run_all(&list);
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module *runtime_test_init(runtime_test_module *m1)
{
    mlgm_module *m2 = &m1->module;

    m2->name = "runtime_test_module";
    m2->enabled = YES;
    m2->instance = m1;

    m2->on_create = runtime_test_module_on_create;
    m2->on_run = runtime_test_module_on_run;

    return m2;
}
