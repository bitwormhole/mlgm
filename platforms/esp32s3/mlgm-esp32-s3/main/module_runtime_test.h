#ifndef __module_runtime_test_h__
#define __module_runtime_test_h__

#include "mlgm_module.h"

struct t_runtime_test_module_body;
typedef struct t_runtime_test_module_body runtime_test_module_body;

typedef struct t_runtime_test_module
{
    mlgm_module head;

    runtime_test_module_body *body;
    runtime_test_module *self;

} runtime_test_module;

mlgm_module *runtime_test_init(runtime_test_module *m, mlgm_app_context *ac);

#endif // __module_runtime_test_h__
