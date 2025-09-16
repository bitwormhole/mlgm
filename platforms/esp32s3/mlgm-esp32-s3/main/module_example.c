#include "module_example.h"

#include "mlgm_logger.h"

////////////////////////////////////////////////////////////////////////////////

mlgm_error example_module_on_create(mlgm_module *m);

// mlgm_error example_module_on_start(mlgm_module *m);
// mlgm_error example_module_on_resume(mlgm_module *m);
// mlgm_error example_module_on_run(mlgm_module *m);
// mlgm_error example_module_on_pause(mlgm_module *m);
// mlgm_error example_module_on_stop(mlgm_module *m);
// mlgm_error example_module_on_destroy(mlgm_module *m);

////////////////////////////////////////////////////////////////////////////////

mlgm_error example_module_on_create(mlgm_module *m)
{
    mlgm_logger_debug(NIL, "example_module_on_create(): todo ...");
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module *example_init(example_module *m1)
{
    mlgm_module *m2 = &m1->module;

    m2->name = "example_module";
    m2->enabled = YES;
    m2->instance = m1;

    m2->on_create = example_module_on_create;

    // m2->on_start = example_module_on_start;
    // m2->on_resume = example_module_on_resume;
    // m2->on_run = example_module_on_run;
    // m2->on_pause = example_module_on_pause;
    // m2->on_stop = example_module_on_stop;
    // m2->on_destroy = example_module_on_destroy;

    return m2;
}
