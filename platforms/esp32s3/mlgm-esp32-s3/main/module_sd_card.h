#ifndef __module_sd_card_h__
#define __module_sd_card_h__

#include "mlgm_module.h"

typedef struct t_sd_card_module
{

    mlgm_module module;

} sd_card_module;

mlgm_module *sd_card_init(sd_card_module *mod);

#endif // __module_sd_card_h__
