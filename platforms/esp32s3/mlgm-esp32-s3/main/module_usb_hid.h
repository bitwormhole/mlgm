#ifndef __module_usb_hid_h__
#define __module_usb_hid_h__

#include "mlgm_module.h"

struct t_usb_hid_module_body;
typedef struct t_usb_hid_module_body usb_hid_module_body;

typedef struct t_usb_hid_module
{

    mlgm_module head;

    usb_hid_module_body *body;
    usb_hid_module *self;

} usb_hid_module;

mlgm_module *usb_hid_init(usb_hid_module *mod, mlgm_app_context *ac);

#endif // __module_usb_hid_h__
