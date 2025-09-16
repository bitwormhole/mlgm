#ifndef __module_wifi_comm_h__
#define __module_wifi_comm_h__

#include "mlgm_module.h"

typedef struct t_wifi_comm_module
{

    mlgm_module module;

} wifi_comm_module;

mlgm_module *wifi_comm_init(wifi_comm_module *mod);

#endif // __module_wifi_comm_h__
