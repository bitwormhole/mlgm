#ifndef __module_usb_hid_h__
#define __module_usb_hid_h__

#include "mlgm_module.h"

typedef struct t_usb_hid_module
{

    mlgm_module module;

} usb_hid_module;

mlgm_module *usb_hid_init(usb_hid_module *mod);

#endif // __module_usb_hid_h__
