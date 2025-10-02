

#include "mlgm_defer.h"

#include "mlgm_types.h"
#include "mlgm_logger.h"

#include <memory.h>

////////////////////////////////////////////////////////////////////////////////
// mlgm_defer_manager

void mlgm_defer_manager_init(mlgm_defer_manager *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
    }
}

void mlgm_defer_manager_execute(mlgm_defer_manager *self)
{
    if (self == NIL)
    {
        return;
    }

    mlgm_deferable *p = self->head;
    mlgm_deferable *tmp = NIL;
    int ttl = 999; // 最多管理 ttl 个对象

    self->head = NIL;

    for (; p; ttl--)
    {
        if (ttl < 0)
        {
            mlgm_logger_warn(NIL, "mlgm_defer_manager_execute: too many deferable objects");
            break;
        }
        tmp = p;
        p = p->next;
        mlgm_deferable_func fn = tmp->fn;
        void *tar = tmp->target;
        if (fn && tar)
        {
            fn(tmp);
        }
    }
}

void mlgm_defer_manager_add(mlgm_defer_manager *self, mlgm_deferable *deferable)
{
    if (self && deferable)
    {
        deferable->next = self->head;
        self->head = deferable;
    }
}

////////////////////////////////////////////////////////////////////////////////
// mlgm_deferable

void mlgm_deferable_init(mlgm_deferable *self, void *target, mlgm_deferable_func fn)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        self->fn = fn;
        self->target = target;
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
