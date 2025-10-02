#ifndef __module_wifi_comm_h__
#define __module_wifi_comm_h__

#include "mlgm_module.h"

struct t_wifi_comm_module_body;
typedef struct t_wifi_comm_module_body wifi_comm_module_body;

typedef struct t_wifi_comm_module
{

    mlgm_module head;

    wifi_comm_module_body *body;
    wifi_comm_module *self;

} wifi_comm_module;

mlgm_module *wifi_comm_init(wifi_comm_module *mod, mlgm_app_context *ac);

#endif // __module_wifi_comm_h__
