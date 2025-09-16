#ifndef __app_module_h__
#define __app_module_h__

#include "mlgm_types.h"
#include "mlgm_errors.h"

#define MLGM_MODULE_MANAGER_CAPACITY 10

struct t_mlgm_module;
struct t_mlgm_app_modules;

////////////////////////////////////////////////////////////////////////////////

typedef enum t_mlgm_lifecycle_phase
{
      PHASE_INIT,
      PHASE_CREATE,
      PHASE_START,
      PHASE_RESUME,
      PHASE_RUN,
      PHASE_PAUSE,
      PHASE_STOP,
      PHASE_DESTROY,

} mlgm_lifecycle_phase;

mlgm_string mlgm_lifecycle_phase_stringify(mlgm_lifecycle_phase phase);

////////////////////////////////////////////////////////////////////////////////

// 模块的生命周期回调函数：
typedef mlgm_error (*mlgm_module_lifecycle_func)(struct t_mlgm_module *module);

// 包含模块信息的结构：
typedef struct t_mlgm_module
{

      mlgm_string name;

      mlgm_bool enabled;

      void *instance; // the instance of module

      struct t_mlgm_app_modules *modules;

      mlgm_module_lifecycle_func on_create;
      mlgm_module_lifecycle_func on_start;
      mlgm_module_lifecycle_func on_resume;

      mlgm_module_lifecycle_func on_run;

      mlgm_module_lifecycle_func on_pause;
      mlgm_module_lifecycle_func on_stop;
      mlgm_module_lifecycle_func on_destroy;

} mlgm_module;

mlgm_string mlgm_module_get_name(mlgm_module *m);

////////////////////////////////////////////////////////////////////////////////

// 模块管理器:
typedef struct t_mlgm_module_manager
{
      mlgm_uint count;
      mlgm_uint capacity;
      mlgm_bool overflow;

      mlgm_module *modules[MLGM_MODULE_MANAGER_CAPACITY];

} mlgm_module_manager;

mlgm_module_manager *mlgm_module_manager_init(mlgm_module_manager *manager);
mlgm_error mlgm_module_manager_add(mlgm_module_manager *manager, mlgm_module *item);
mlgm_error mlgm_module_manager_error(mlgm_module_manager *manager);

////////////////////////////////////////////////////////////////////////////////

// mlgm_module_manager_iter 用于迭代访问模块管理器
typedef struct t_mlgm_module_manager_iter
{
      mlgm_int current;
      mlgm_bool backward;
      mlgm_module_manager *manager;

} mlgm_module_manager_iter;

void mlgm_module_manager_iter_init(mlgm_module_manager_iter *iter, mlgm_module_manager *manager, mlgm_bool backward);
mlgm_bool mlgm_module_manager_iter_has_more(mlgm_module_manager_iter *iter);
mlgm_module *mlgm_module_manager_iter_next(mlgm_module_manager_iter *iter);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_module_lifecycle_caller
{

      mlgm_module_manager *manager;

      mlgm_lifecycle_phase phase;

      mlgm_bool backward;

} mlgm_module_lifecycle_caller;

mlgm_error mlgm_module_lifecycle_caller_init(mlgm_module_lifecycle_caller *self, mlgm_module_manager *man);
mlgm_error mlgm_module_lifecycle_caller_call(mlgm_module_lifecycle_caller *self);

mlgm_module_lifecycle_func mlgm_module_lifecycle_caller_select_func(mlgm_module_lifecycle_caller *self, mlgm_module *module);

////////////////////////////////////////////////////////////////////////////////

#endif // __app_module_h__
