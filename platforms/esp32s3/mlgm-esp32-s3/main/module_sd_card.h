#ifndef __module_sd_card_h__
#define __module_sd_card_h__

#include "mlgm_module.h"
#include "mlgm_bytes.h"
#include "mlgm_strings.h"
#include "mlgm_paths.h"

struct t_sd_card_module_body;
typedef struct t_sd_card_module_body sd_card_module_body;

////////////////////////////////////////////////////////////////////////////////

typedef struct t_sd_card_module
{
    mlgm_module head;

    sd_card_module_body *body;
    sd_card_module *self;

} sd_card_module;

sd_card_module *sd_card_module_get_instance(mlgm_module *m1);
sd_card_module_body *sd_card_module_get_body(mlgm_module *m1);

mlgm_module *sd_card_init(sd_card_module *mod, mlgm_app_context *ac);

mlgm_error sd_card_module_get_mount_path(sd_card_module *m1, mlgm_path *path_out);

////////////////////////////////////////////////////////////////////////////////

#endif // __module_sd_card_h__
