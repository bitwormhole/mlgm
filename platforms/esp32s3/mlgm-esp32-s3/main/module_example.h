#ifndef __module_example_h__
#define __module_example_h__

#include "mlgm_module.h"

typedef struct t_example_module
{

    mlgm_module module;

} example_module;

mlgm_module *example_init(example_module *mod);

#endif // __module_example_h__
