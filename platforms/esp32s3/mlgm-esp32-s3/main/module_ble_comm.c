#include "module_ble_comm.h"

#include "mlgm_logger.h"

#include <memory.h>

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

mlgm_module *ble_comm_init(ble_comm_module *m2, mlgm_app_context *ac)
{
    if (m2)
    {
        memset(m2, 0, sizeof(m2[0]));
    }
    else
    {
        return NIL;
    }

    mlgm_module_class clazz = MLGM_MODULE_CLASS_BLE;
    mlgm_string name = "ble_comm_module";

    mlgm_module *m1 = &m2->head;
    m1 = mlgm_module_init(m1, ac, clazz, name, m2);
    if (m1)
    {

        // m1->on_create = ble_comm_module_on_create;
        // m1->on_start = ble_comm_module_on_start;
        // m1->on_resume = ble_comm_module_on_resume;
        // m1->on_run = ble_comm_module_on_run;
        // m1->on_pause = ble_comm_module_on_pause;
        // m1->on_stop = ble_comm_module_on_stop;
        // m1->on_destroy = ble_comm_module_on_destroy;
    }

    m2->self = m2;
    return m1;
}
