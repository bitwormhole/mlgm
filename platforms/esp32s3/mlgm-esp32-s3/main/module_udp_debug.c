#include "module_udp_debug.h"

#include "mlgm_logger.h"

////////////////////////////////////////////////////////////////////////////////

mlgm_error udp_debug_module_on_create(mlgm_module *m);

// mlgm_error udp_debug_module_on_start(mlgm_module *m);
// mlgm_error udp_debug_module_on_resume(mlgm_module *m);
// mlgm_error udp_debug_module_on_run(mlgm_module *m);
// mlgm_error udp_debug_module_on_pause(mlgm_module *m);
// mlgm_error udp_debug_module_on_stop(mlgm_module *m);
// mlgm_error udp_debug_module_on_destroy(mlgm_module *m);

////////////////////////////////////////////////////////////////////////////////

mlgm_error udp_debug_module_on_create(mlgm_module *m)
{
    mlgm_logger_debug(NIL, "udp_debug_module_on_create(): todo ...");
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module *udp_debug_init(udp_debug_module *m1)
{
    mlgm_module *m2 = &m1->module;

    m2->name = "udp_debug_module";
    m2->enabled = YES;
    m2->instance = m1;

    m2->on_create = udp_debug_module_on_create;

    // m2->on_start = udp_debug_module_on_start;
    // m2->on_resume = udp_debug_module_on_resume;
    // m2->on_run = udp_debug_module_on_run;
    // m2->on_pause = udp_debug_module_on_pause;
    // m2->on_stop = udp_debug_module_on_stop;
    // m2->on_destroy = udp_debug_module_on_destroy;

    return m2;
}
