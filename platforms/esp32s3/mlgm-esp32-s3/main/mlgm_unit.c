#include "mlgm_unit.h"

#include "mlgm_logger.h"
#include "mlgm_app.h"

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// struct:mlgm_unit_holder

mlgm_unit_holder *mlgm_unit_holder_new()
{
    const mlgm_uint size = sizeof(mlgm_unit_holder);
    void *p = malloc(size);
    mlgm_unit_holder *h = p;
    if (h)
    {
        memset(p, 0, size);
        h->self = h;
    }
    return h;
}

void mlgm_unit_holder_delete(mlgm_unit_holder *self)
{
    if (self)
    {
        if (self->self == self)
        {
            self->self = NIL;
            free(self);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// struct:mlgm_unit

mlgm_bool mlgm_unit_is_ready(mlgm_unit *unit)
{
    if (unit)
    {
        if (unit->name == NIL)
        {
            unit->name = "unnamed";
        }
        mlgm_bool b1 = unit->enabled;
        mlgm_bool b2 = (unit->fn != NIL);
        return (b1 && b2);
    }
    return NO;
}

mlgm_error mlgm_unit_run(mlgm_unit *unit)
{
    mlgm_unit_func fn = unit->fn;
    return fn(unit);
}

////////////////////////////////////////////////////////////////////////////////
// struct:mlgm_unit_list

void mlgm_unit_list_init(mlgm_unit_list *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
    }
}

void mlgm_unit_list_add_fn(mlgm_unit_list *self, mlgm_string name, mlgm_unit_func fn)
{
    mlgm_unit tmp;
    memset(&tmp, 0, sizeof(tmp));

    tmp.fn = fn;
    tmp.name = name;
    tmp.enabled = YES;
    tmp.order = 0;

    mlgm_unit_list_add(self, &tmp);
}

void mlgm_unit_list_add(mlgm_unit_list *self, mlgm_unit *unit)
{
    if (self == NIL || unit == NIL)
    {
        return;
    }

    mlgm_unit_holder *h = mlgm_unit_holder_new();
    mlgm_unit_holder *tail = self->last;

    if (h)
    {
        h->prev = tail;
        h->next = NIL;
        h->unit = *unit;
        if (tail)
        {
            tail->next = h;
        }
        else
        {
            self->first = h;
        }
        self->last = h;
    }
}

mlgm_error mlgm_unit_list_run_all(mlgm_unit_list *self, mlgm_app_context *ac)
{
    if (self == NIL)
    {
        return mlgm_error_make(500, "mlgm_unit_list_run_all: self(mlgm_unit_list*) is nil");
    }

    mlgm_unit_holder *p = self->first;
    int count_err = 0;
    int count_total = 0;
    int count_done = 0;
    int count_ok = 0;

    mlgm_string bar1, bar2;
    bar1 = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    bar2 = "------------------------------------------------------------------";

    for (; p; p = p->next)
    {
        mlgm_unit *u = &p->unit;
        u->context = ac;
        count_total++;
        if (!mlgm_unit_is_ready(u))
        {
            continue;
        }
        int idx = count_done;
        printf("%s%c", bar1, '\n');
        printf("run unit[%d]: %s \n", idx, u->name);
        mlgm_error err = mlgm_unit_run(u);
        if (err)
        {
            mlgm_string msg = mlgm_error_get_message(err);
            mlgm_logger_error(NIL, "mlgm_unit_list_run_all:unit_error:%s", msg);
            count_err++;
        }
        else
        {
            count_ok++;
        }
        count_done++;
        printf("%s%c", bar2, '\n');
    }

    int count_skip = (count_total - count_done);
    mlgm_logger_info(NIL, "count.error = %d", count_err);
    mlgm_logger_info(NIL, "count.skip  = %d", count_skip);
    mlgm_logger_info(NIL, "count.done  = %d", count_done);
    mlgm_logger_info(NIL, "count.ok    = %d", count_ok);
    mlgm_logger_info(NIL, "count.total = %d", count_done);

    if (count_err > 0)
    {
        return mlgm_error_make_with_format(500, "mlgm_unit_list_run_all: %d unit(s) return error", count_err);
    }
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
