#ifndef __module_udp_debug_h__
#define __module_udp_debug_h__

#include "mlgm_module.h"

typedef struct t_udp_debug_module
{

    mlgm_module module;

} udp_debug_module;

mlgm_module *udp_debug_init(udp_debug_module *mod);

#endif // __module_udp_debug_h__
