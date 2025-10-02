#ifndef __module_ble_comm_h__
#define __module_ble_comm_h__

#include "mlgm_module.h"

struct t_ble_comm_module_body;
typedef struct t_ble_comm_module_body ble_comm_module_body;

typedef struct t_ble_comm_module
{

    mlgm_module head;
    ble_comm_module_body *body;

    ble_comm_module *self;

} ble_comm_module;

mlgm_module *ble_comm_init(ble_comm_module *mod, mlgm_app_context *ac);

#endif // __module_ble_comm_h__
