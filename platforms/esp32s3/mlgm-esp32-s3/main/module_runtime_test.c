#include "module_runtime_test.h"

#include "mlgm_logger.h"
#include "mlgm_unit.h"
#include "mlgm_time.h"

#include "units/units.h"

#include "units/rt_unit_example1.c"
#include "units/rt_unit_hash_algorithms.c"
#include "units/rt_unit_test_sd_card_rw.c"

////////////////////////////////////////////////////////////////////////////////

mlgm_error runtime_test_module_on_create(mlgm_module *m);
mlgm_error runtime_test_module_on_run(mlgm_module *m);
mlgm_error runtime_test_module_on_stop(mlgm_module *m);

////////////////////////////////////////////////////////////////////////////////

mlgm_error runtime_test_module_on_create(mlgm_module *m)
{
    mlgm_logger_debug(NIL, "runtime_test_module_on_create(): todo ...");

    runtime_test_module_on_stop(m);

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
    mlgm_unit_list_add_fn(&list, "rt_unit_test_sd_card_rw", rt_unit_test_sd_card_rw);

    mlgm_app_context *ctx = m->context;
    return mlgm_unit_list_run_all(&list, ctx);
}

mlgm_error runtime_test_module_on_stop(mlgm_module *m)
{
    for (;;)
    {
        mlgm_logger_info(NIL, "runtime_test_module_on_stop() : keep-alive");
        mlgm_time_sleep(5000);
    }
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module *runtime_test_init(runtime_test_module *m2, mlgm_app_context *ac)
{
    if (m2)
    {
        memset(m2, 0, sizeof(m2[0]));
    }
    else
    {
        return NIL;
    }

    mlgm_module_class clazz = MLGM_MODULE_CLASS_RUNTIME_TEST;
    mlgm_string name = "runtime_test_module";

    mlgm_module *m1 = &m2->head;
    m1 = mlgm_module_init(m1, ac, clazz, name, m2);
    if (m1)
    {
        m1->on_create = runtime_test_module_on_create;
        m1->on_run = runtime_test_module_on_run;
        m1->on_stop = runtime_test_module_on_stop;
    }

    m2->self = m2;
    return m1;
}
