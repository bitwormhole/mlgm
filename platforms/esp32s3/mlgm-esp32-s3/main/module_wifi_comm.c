#include "module_wifi_comm.h"

#include "mlgm_logger.h"

#include <memory.h>

////////////////////////////////////////////////////////////////////////////////

mlgm_error wifi_comm_module_on_create(mlgm_module *m);

// mlgm_error wifi_comm_module_on_start(mlgm_module *m);
// mlgm_error wifi_comm_module_on_resume(mlgm_module *m);
// mlgm_error wifi_comm_module_on_run(mlgm_module *m);
// mlgm_error wifi_comm_module_on_pause(mlgm_module *m);
// mlgm_error wifi_comm_module_on_stop(mlgm_module *m);
// mlgm_error wifi_comm_module_on_destroy(mlgm_module *m);

////////////////////////////////////////////////////////////////////////////////

mlgm_error wifi_comm_module_on_create(mlgm_module *m)
{
    mlgm_logger_debug(NIL, "wifi_comm_module_on_create(): todo ...");
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module *wifi_comm_init(wifi_comm_module *m2, mlgm_app_context *ac)
{
    if (m2)
    {
        memset(m2, 0, sizeof(m2[0]));
    }
    else
    {
        return NIL;
    }

    mlgm_module_class clazz = MLGM_MODULE_CLASS_WIFI;
    mlgm_string name = "wifi_comm_module";

    mlgm_module *m1 = &m2->head;
    m1 = mlgm_module_init(m1, ac, clazz, name, m2);
    if (m1)
    {
        m1->on_create = wifi_comm_module_on_create;
    }

    m2->self = m2;
    return m1;
}
