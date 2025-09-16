#include "module_wifi_comm.h"

#include "mlgm_logger.h"

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

mlgm_module *wifi_comm_init(wifi_comm_module *m1)
{
    mlgm_module *m2 = &m1->module;

    m2->name = "wifi_comm_module";
    m2->enabled = YES;
    m2->instance = m1;

    m2->on_create = wifi_comm_module_on_create;

    // m2->on_start = wifi_comm_module_on_start;
    // m2->on_resume = wifi_comm_module_on_resume;
    // m2->on_run = wifi_comm_module_on_run;
    // m2->on_pause = wifi_comm_module_on_pause;
    // m2->on_stop = wifi_comm_module_on_stop;
    // m2->on_destroy = wifi_comm_module_on_destroy;

    return m2;
}
