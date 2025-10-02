#include "mlgm_module.h"
#include "mlgm_logger.h"

#include <memory.h>

////////////////////////////////////////////////////////////////////////////////

mlgm_string mlgm_lifecycle_phase_stringify(mlgm_lifecycle_phase phase)
{
    switch (phase)
    {
    case PHASE_INIT:
        return "INIT";
    case PHASE_CREATE:
        return "CREATE";
    case PHASE_START:
        return "START";
    case PHASE_RESUME:
        return "RESUME";
    case PHASE_RUN:
        return "RUN";
    case PHASE_PAUSE:
        return "PAUSE";
    case PHASE_STOP:
        return "STOP";
    case PHASE_DESTROY:
        return "DESTROY";
    default:
        break;
    }
    return "PHASE_UNKNOWN";
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module *mlgm_module_init(mlgm_module *m, mlgm_app_context *ctx, mlgm_module_class cls, mlgm_string name, void *inst)
{
    if (m)
    {
        memset(m, 0, sizeof(m[0]));

        m->enabled = YES;
        m->context = ctx;
        m->name = name;
        m->module_class = cls;
        m->instance = inst;
    }
    return m;
}

mlgm_string mlgm_module_get_name(mlgm_module *m)
{
    if (m == NIL)
    {
        return "nil";
    }
    mlgm_string name = m->name;
    if (name == NIL)
    {
        name = "nil";
    }
    return name;
}

void *mlgm_module_get_instance(mlgm_module *m, mlgm_module_class want_class)
{
    if (m == NIL)
    {
        return NIL;
    }

    void *inst = m->instance;
    mlgm_module_class cls = m->module_class;
    mlgm_string name = m->name;
    mlgm_app_context *ctx = m->context;

    if ((inst == m) && (cls == want_class) && (name) && (ctx))
    {
        return inst;
    }

    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module_manager *mlgm_module_manager_init(mlgm_module_manager *manager)
{
    memset(manager, 0, sizeof(manager[0]));
    manager->capacity = MLGM_MODULE_MANAGER_CAPACITY;
    return manager;
}

mlgm_error mlgm_module_manager_add(mlgm_module_manager *manager, mlgm_module *item)
{
    if (manager == NIL || item == NIL)
    {
        return mlgm_error_make(0, "mlgm_module_manager_add: param(s) is nil");
    }

    mlgm_uint count = manager->count;
    mlgm_uint max = manager->capacity;

    if (count < max)
    {
        manager->modules[count] = item;
        manager->count = count + 1;
        return NIL;
    }

    manager->overflow = YES;
    return mlgm_error_make(0, "mlgm_module_manager_add: too many items");
}

mlgm_error mlgm_module_manager_error(mlgm_module_manager *manager)
{
    if (manager->overflow)
    {
        return mlgm_error_make(0, "mlgm_module_manager_error: too many items");
    }
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

void mlgm_module_manager_iter_init(mlgm_module_manager_iter *iter, mlgm_module_manager *manager, mlgm_bool backward)
{
    if (iter)
    {
        memset(iter, 0, sizeof(iter[0]));
        if (manager)
        {
            iter->current = backward ? (manager->count - 1) : 0;
        }
        iter->manager = manager;
        iter->backward = backward;
    }
}

mlgm_bool mlgm_module_manager_iter_has_more(mlgm_module_manager_iter *iter)
{
    if (iter == NIL)
    {
        return NO;
    }
    // mlgm_bool back = iter->backward;
    mlgm_module_manager *mm = iter->manager;
    if (mm == NIL)
    {
        return NO;
    }

    mlgm_int pos = iter->current;
    mlgm_int len = mm->count;
    mlgm_int cap = mm->capacity;

    return ((0 <= pos) && (pos < len) && (pos < cap));
}

mlgm_module *mlgm_module_manager_iter_next(mlgm_module_manager_iter *iter)
{
    if (iter == NIL)
    {
        return NIL;
    }
    mlgm_bool back = iter->backward;
    mlgm_module_manager *mm = iter->manager;
    if (mm == NIL)
    {
        return NIL;
    }
    mlgm_int pos = iter->current;
    mlgm_int len = mm->count;
    mlgm_int cap = mm->capacity;
    if ((0 <= pos) && (pos < len) && (pos < cap))
    {
        iter->current = back ? (pos - 1) : (pos + 1);
        return mm->modules[pos];
    }
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_error mlgm_module_lifecycle_caller_init(mlgm_module_lifecycle_caller *self, mlgm_module_manager *man)
{
    if (self == NIL || man == NIL)
    {
        return mlgm_error_make(500, "mlgm_module_lifecycle_caller_init(): param(s) is nil");
    }
    memset(self, 0, sizeof(self[0]));
    self->manager = man;
    return NIL;
}

mlgm_error mlgm_module_lifecycle_caller_call(mlgm_module_lifecycle_caller *self)
{
    mlgm_module_manager_iter iter;
    mlgm_module_manager_iter_init(&iter, self->manager, self->backward);

    for (; mlgm_module_manager_iter_has_more(&iter);)
    {
        mlgm_module *mod = mlgm_module_manager_iter_next(&iter);
        if (mod == NIL)
        {
            continue;
        }

        mlgm_string str_mod_name = mlgm_module_get_name(mod); // mod->name;
        mlgm_string str_phase_name = mlgm_lifecycle_phase_stringify(self->phase);

        mlgm_module_lifecycle_func fn = mlgm_module_lifecycle_caller_select_func(self, mod);
        if (fn == NIL)
        {
            continue;
        }

        mlgm_error err = fn(mod);
        if (err)
        {
            mlgm_logger_error(NIL, "call:%s@%s(Err)", str_phase_name, str_mod_name);
            // mlgm_logger_error(NIL, "mlgm_module_lifecycle_caller_call():err", mod->name);
            return err;
        }

        mlgm_logger_info(NIL, "call:%s@%s(OK)", str_phase_name, str_mod_name);
    }

    return NIL;
}

mlgm_module_lifecycle_func mlgm_module_lifecycle_caller_select_func(mlgm_module_lifecycle_caller *self, mlgm_module *module)
{
    if ((self == NIL) || (module == NIL))
    {
        return NIL;
    }

    switch (self->phase)
    {
    case PHASE_CREATE:
        return module->on_create;
    case PHASE_START:
        return module->on_start;
    case PHASE_RESUME:
        return module->on_resume;

    case PHASE_RUN:
        return module->on_run;

    case PHASE_PAUSE:
        return module->on_pause;
    case PHASE_STOP:
        return module->on_stop;
    case PHASE_DESTROY:
        return module->on_destroy;

    default:
        break;
    }

    return NIL;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
