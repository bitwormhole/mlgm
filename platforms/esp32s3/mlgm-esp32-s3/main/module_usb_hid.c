#include "module_usb_hid.h"

#include "mlgm_logger.h"

////////////////////////////////////////////////////////////////////////////////

mlgm_error usb_hid_module_on_create(mlgm_module *m);
mlgm_error usb_hid_module_on_start(mlgm_module *m);
mlgm_error usb_hid_module_on_resume(mlgm_module *m);
mlgm_error usb_hid_module_on_run(mlgm_module *m);

////////////////////////////////////////////////////////////////////////////////

mlgm_error usb_hid_module_on_create(mlgm_module *m)
{

    mlgm_logger_debug(NIL, "usb_hid_module_on_create(): todo ...");

    return NIL;
}

mlgm_error usb_hid_module_on_start(mlgm_module *m)
{
    return NIL;
}

mlgm_error usb_hid_module_on_resume(mlgm_module *m)
{
    return NIL;
}

mlgm_error usb_hid_module_on_run(mlgm_module *m)
{
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module *usb_hid_init(usb_hid_module *mod)
{
    if (mod == NIL)
    {
        return NIL;
    }
    mlgm_module *m2 = &mod->module;

    m2->name = "usb_hid_module";
    m2->enabled = YES;
    m2->instance = mod;

    m2->on_create = usb_hid_module_on_create;
    m2->on_start = usb_hid_module_on_start;
    m2->on_resume = usb_hid_module_on_resume;
    m2->on_run = usb_hid_module_on_run;

    return m2;
}
