#ifndef __module_runtime_test_h__
#define __module_runtime_test_h__

#include "mlgm_module.h"

typedef struct t_runtime_test_module
{

    mlgm_module module;

} runtime_test_module;

mlgm_module *runtime_test_init(runtime_test_module *m);

#endif // __module_runtime_test_h__
