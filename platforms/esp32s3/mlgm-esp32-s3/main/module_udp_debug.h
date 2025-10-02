#ifndef __module_udp_debug_h__
#define __module_udp_debug_h__

#include "mlgm_module.h"

struct t_udp_debug_module_body;

typedef struct t_udp_debug_module_body udp_debug_module_body;

typedef struct t_udp_debug_module
{
    mlgm_module head;

    udp_debug_module *self;
    udp_debug_module_body *body;

} udp_debug_module;

mlgm_module *udp_debug_init(udp_debug_module *mod, mlgm_app_context *ac);

#endif // __module_udp_debug_h__
