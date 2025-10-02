#include "module_usb_hid.h"

#include "mlgm_logger.h"

#include <memory.h>

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

mlgm_module *usb_hid_init(usb_hid_module *m2, mlgm_app_context *ac)
{
    if (m2)
    {
        memset(m2, 0, sizeof(m2[0]));
    }
    else
    {
        return NIL;
    }

    mlgm_module_class clazz = MLGM_MODULE_CLASS_USB_HID;
    mlgm_string name = "usb_hid_module";

    mlgm_module *m1 = &m2->head;
    m1 = mlgm_module_init(m1, ac, clazz, name, m2);
    if (m1)
    {
        m1->on_create = usb_hid_module_on_create;
        m1->on_start = usb_hid_module_on_start;
        m1->on_resume = usb_hid_module_on_resume;
        m1->on_run = usb_hid_module_on_run;
    }

    m2->self = m2;
    return m1;
}
