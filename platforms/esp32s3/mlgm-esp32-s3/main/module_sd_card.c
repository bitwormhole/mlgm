#include "module_sd_card.h"

#include "mlgm_logger.h"

////////////////////////////////////////////////////////////////////////////////

mlgm_error sd_card_module_on_create(mlgm_module *m);

mlgm_error sd_card_module_on_start(mlgm_module *m);
mlgm_error sd_card_module_on_resume(mlgm_module *m);
mlgm_error sd_card_module_on_run(mlgm_module *m);

////////////////////////////////////////////////////////////////////////////////

mlgm_error sd_card_module_on_create(mlgm_module *m)
{

    mlgm_logger_debug(NIL, "sd_card_module_on_create(): todo ...");

    return NIL;
}

mlgm_error sd_card_module_on_start(mlgm_module *m)
{
    return NIL;
}

mlgm_error sd_card_module_on_resume(mlgm_module *m)
{
    return NIL;
}

mlgm_error sd_card_module_on_run(mlgm_module *m)
{
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module *sd_card_init(sd_card_module *mod)
{
    if (mod == NIL)
    {
        return NIL;
    }
    mlgm_module *m2 = &mod->module;

    m2->name = "sd_card_module";
    m2->enabled = YES;
    m2->instance = mod;

    m2->on_create = sd_card_module_on_create;
    m2->on_start = sd_card_module_on_start;
    m2->on_resume = sd_card_module_on_resume;
    m2->on_run = sd_card_module_on_run;

    return m2;
}
