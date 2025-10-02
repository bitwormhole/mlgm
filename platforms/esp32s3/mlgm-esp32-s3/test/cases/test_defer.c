

#include "../unit_include.h"

#include "../../main/mlgm_defer.h"

#include <memory.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////

typedef struct t_run_case_defer_example_node run_case_defer_example_node;

void run_case_defer_example_node_delete_defer(mlgm_deferable *deferable);
run_case_defer_example_node *run_case_defer_example_node_new(int id);
mlgm_deferable *run_case_defer_example_node_to_deferable(run_case_defer_example_node *self);
void run_case_defer_example_node_init(run_case_defer_example_node *self);
void run_case_defer_example_node_delete(run_case_defer_example_node *self);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_run_case_defer_example_node
{

    mlgm_deferable deferable;

    run_case_defer_example_node *self;

    int id;

} run_case_defer_example_node;

run_case_defer_example_node *run_case_defer_example_node_new(int id)
{
    size_t size = sizeof(run_case_defer_example_node);
    run_case_defer_example_node *p = malloc(size);
    run_case_defer_example_node_init(p);
    if (p)
    {
        p->id = id;
        mlgm_logger_info(NIL, "run_case_defer_example_node_new(): node_id=%d", id);
    }
    return p;
}

mlgm_deferable *run_case_defer_example_node_to_deferable(run_case_defer_example_node *self)
{
    return &self->deferable;
}

void run_case_defer_example_node_init(run_case_defer_example_node *self)
{
    if (self)
    {
        mlgm_deferable_init(&self->deferable, self, run_case_defer_example_node_delete_defer);
        self->id = 0;
        self->self = self;
    }
}

void run_case_defer_example_node_delete(run_case_defer_example_node *self)
{
    if (self)
    {
        if (self == self->self)
        {
            int id = self->id;
            mlgm_logger_info(NIL, "run_case_defer_example_node_delete(): node_id=%d", id);
            memset(self, 0, sizeof(self[0]));
            free(self);
        }
    }
}

void run_case_defer_example_node_delete_defer(mlgm_deferable *deferable)
{
    if (deferable)
    {
        run_case_defer_example_node *self = deferable->target;
        if (self)
        {
            run_case_defer_example_node_delete(self);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

mlgm_error run_case_defer(mlgm_unit *unit)
{

    mlgm_logger_debug(NIL, "run_case_defer: todo...");

    int id_gen = 0;
    int i1, i2, i3;
    mlgm_defer_manager dm1, dm2, dm3;

    mlgm_defer_manager_init(&dm1);
    mlgm_defer_manager_init(&dm2);
    mlgm_defer_manager_init(&dm3);

    for (i1 = 0; i1 < 2; i1++)
    {
        run_case_defer_example_node *node11 = run_case_defer_example_node_new(id_gen++);
        run_case_defer_example_node *node12 = run_case_defer_example_node_new(id_gen++);
        run_case_defer_example_node *node13 = run_case_defer_example_node_new(id_gen++);

        mlgm_defer_manager_add(&dm1, run_case_defer_example_node_to_deferable(node11));
        mlgm_defer_manager_add(&dm1, run_case_defer_example_node_to_deferable(node12));
        mlgm_defer_manager_add(&dm1, run_case_defer_example_node_to_deferable(node13));

        for (i2 = 0; i2 < 3; i2++)
        {
            run_case_defer_example_node *node21 = run_case_defer_example_node_new(id_gen++);
            run_case_defer_example_node *node22 = run_case_defer_example_node_new(id_gen++);
            run_case_defer_example_node *node23 = run_case_defer_example_node_new(id_gen++);

            mlgm_defer_manager_add(&dm2, run_case_defer_example_node_to_deferable(node21));
            mlgm_defer_manager_add(&dm2, run_case_defer_example_node_to_deferable(node22));
            mlgm_defer_manager_add(&dm2, run_case_defer_example_node_to_deferable(node23));

            for (i3 = 0; i3 < 4; i3++)
            {
                run_case_defer_example_node *node31 = run_case_defer_example_node_new(id_gen++);
                run_case_defer_example_node *node32 = run_case_defer_example_node_new(id_gen++);
                run_case_defer_example_node *node33 = run_case_defer_example_node_new(id_gen++);

                mlgm_defer_manager_add(&dm3, run_case_defer_example_node_to_deferable(node31));
                mlgm_defer_manager_add(&dm3, run_case_defer_example_node_to_deferable(node32));
                mlgm_defer_manager_add(&dm3, run_case_defer_example_node_to_deferable(node33));

                mlgm_defer_manager_execute(&dm3);
            }

            mlgm_defer_manager_execute(&dm2);
        }

        mlgm_defer_manager_execute(&dm1);
    }

    return NIL;
}
