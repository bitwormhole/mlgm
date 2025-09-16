#include "module_ble_comm.h"

#include "mlgm_logger.h"

////////////////////////////////////////////////////////////////////////////////

mlgm_error ble_comm_module_on_create(mlgm_module *m);
mlgm_error ble_comm_module_on_start(mlgm_module *m);
mlgm_error ble_comm_module_on_resume(mlgm_module *m);
mlgm_error ble_comm_module_on_run(mlgm_module *m);
mlgm_error ble_comm_module_on_pause(mlgm_module *m);
mlgm_error ble_comm_module_on_stop(mlgm_module *m);
mlgm_error ble_comm_module_on_destroy(mlgm_module *m);

////////////////////////////////////////////////////////////////////////////////

mlgm_error ble_comm_module_on_create(mlgm_module *m)
{
    mlgm_logger_debug(NIL, "ble_comm_module_on_create(): todo ...");
    return NIL;
}

mlgm_error ble_comm_module_on_start(mlgm_module *m)
{
    mlgm_logger_warn(NIL, "ble_comm_module_on_start(): todo ...");
    return NIL;
}

mlgm_error ble_comm_module_on_resume(mlgm_module *m)
{
    mlgm_logger_debug(NIL, "ble_comm_module_on_resume(): todo ...");
    return NIL;
}

mlgm_error ble_comm_module_on_run(mlgm_module *m)
{
    mlgm_logger_warn(NIL, "ble_comm_module_on_run(): todo ...");
    return NIL;
}

mlgm_error ble_comm_module_on_pause(mlgm_module *m)
{
    mlgm_logger_debug(NIL, "ble_comm_module_on_pause(): todo ...");
    return NIL;
}

mlgm_error ble_comm_module_on_stop(mlgm_module *m)
{
    mlgm_logger_warn(NIL, "ble_comm_module_on_stop(): todo ...");
    return NIL;
}

mlgm_error ble_comm_module_on_destroy(mlgm_module *m)
{
    mlgm_logger_debug(NIL, "ble_comm_module_on_destroy(): todo ...");
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module *ble_comm_init(ble_comm_module *m1)
{
    mlgm_module *m2 = &m1->module;

    m2->name = "ble_comm_module";
    m2->enabled = YES;
    m2->instance = m1;

    m2->on_create = ble_comm_module_on_create;
    m2->on_start = ble_comm_module_on_start;
    m2->on_resume = ble_comm_module_on_resume;
    m2->on_run = ble_comm_module_on_run;
    m2->on_pause = ble_comm_module_on_pause;
    m2->on_stop = ble_comm_module_on_stop;
    m2->on_destroy = ble_comm_module_on_destroy;

    return m2;
}
