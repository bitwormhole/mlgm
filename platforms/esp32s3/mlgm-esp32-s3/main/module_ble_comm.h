#ifndef __module_ble_comm_h__
#define __module_ble_comm_h__

#include "mlgm_module.h"

typedef struct t_ble_comm_module
{

    mlgm_module module;

} ble_comm_module;

mlgm_module *ble_comm_init(ble_comm_module *mod);

#endif // __module_ble_comm_h__
