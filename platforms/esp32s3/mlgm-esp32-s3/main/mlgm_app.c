#include "mlgm_app.h"
#include "mlgm_all_in_one.h"

#include <memory.h>

typedef mlgm_error (*mlgm_app_lifecycle_step_func)(mlgm_app *app);

////////////////////////////////////////////////////////////////////////////////

mlgm_error mlgm_app_on_init(mlgm_app *app);

mlgm_error mlgm_app_on_create(mlgm_app *app);
mlgm_error mlgm_app_on_start(mlgm_app *app);
mlgm_error mlgm_app_on_resume(mlgm_app *app);

mlgm_error mlgm_app_on_run(mlgm_app *app);

mlgm_error mlgm_app_on_pause(mlgm_app *app);
mlgm_error mlgm_app_on_stop(mlgm_app *app);
mlgm_error mlgm_app_on_destroy(mlgm_app *app);

////////////////////////////////////////////////////////////////////////////////

mlgm_error mlgm_app_run(mlgm_app *app)
{
    const int count_steps = 10;
    mlgm_app_lifecycle_step_func steps[count_steps];
    int i = 0;

    steps[i++] = mlgm_app_on_init;
    steps[i++] = mlgm_app_on_create;
    steps[i++] = mlgm_app_on_start;
    steps[i++] = mlgm_app_on_resume;
    steps[i++] = mlgm_app_on_run;
    steps[i++] = mlgm_app_on_pause;
    steps[i++] = mlgm_app_on_stop;
    steps[i++] = mlgm_app_on_destroy;
    steps[i++] = NIL;

    if (i >= count_steps)
    {
        return mlgm_error_make(500, "too many steps");
    }

    for (i = 0; i < count_steps; i++)
    {
        mlgm_app_lifecycle_step_func fn = steps[i];
        if (fn == NIL)
        {
            break;
        }
        mlgm_error err = fn(app);
        if (err)
        {
            return err;
        }
    }

    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_error mlgm_app_on_init(mlgm_app *app)
{

    // 初始化 app
    memset(app, 0, sizeof(app[0]));

    // 初始化模块管理器
    mlgm_app_modules *mods = &app->modules;
    mlgm_module_manager *mm = &mods->manager;
    mlgm_module_manager_init(mm);

    // 列举，并初始化各个模块

    ble_comm_module *mod_ble_1 = &app->ble;
    sd_card_module *mod_sd_1 = &app->sd;
    usb_hid_module *mod_usb_1 = &app->usb;
    wifi_comm_module *mod_wifi_1 = &app->wifi;
    udp_debug_module *mod_udp_1 = &app->udp;
    runtime_test_module *mod_rttest_1 = &app->rttest;

    mlgm_module *mod_ble_2 = ble_comm_init(mod_ble_1);
    mlgm_module *mod_sd_2 = sd_card_init(mod_sd_1);
    mlgm_module *mod_usb_2 = usb_hid_init(mod_usb_1);
    mlgm_module *mod_wifi_2 = wifi_comm_init(mod_wifi_1);
    mlgm_module *mod_udp_2 = udp_debug_init(mod_udp_1);
    mlgm_module *mod_rttest_2 = runtime_test_init(mod_rttest_1);

    mlgm_module_manager_add(mm, mod_ble_2);
    mlgm_module_manager_add(mm, mod_sd_2);
    mlgm_module_manager_add(mm, mod_usb_2);
    mlgm_module_manager_add(mm, mod_wifi_2);
    mlgm_module_manager_add(mm, mod_udp_2);
    mlgm_module_manager_add(mm, mod_rttest_2);

    return mlgm_module_manager_error(mm);
}

mlgm_error mlgm_app_on_create(mlgm_app *app)
{
    mlgm_module_lifecycle_caller caller;
    mlgm_module_manager *man = &app->modules.manager;
    mlgm_error err = mlgm_module_lifecycle_caller_init(&caller, man);
    if (err)
    {
        return err;
    }
    caller.backward = NO;
    caller.phase = PHASE_CREATE;
    return mlgm_module_lifecycle_caller_call(&caller);
}

mlgm_error mlgm_app_on_start(mlgm_app *app)
{

    mlgm_module_lifecycle_caller caller;
    mlgm_module_manager *man = &app->modules.manager;
    mlgm_error err = mlgm_module_lifecycle_caller_init(&caller, man);
    if (err)
    {
        return err;
    }
    caller.backward = NO;
    caller.phase = PHASE_START;
    return mlgm_module_lifecycle_caller_call(&caller);
}

mlgm_error mlgm_app_on_resume(mlgm_app *app)
{

    mlgm_module_lifecycle_caller caller;
    mlgm_module_manager *man = &app->modules.manager;
    mlgm_error err = mlgm_module_lifecycle_caller_init(&caller, man);
    if (err)
    {
        return err;
    }
    caller.backward = NO;
    caller.phase = PHASE_RESUME;
    return mlgm_module_lifecycle_caller_call(&caller);
}

mlgm_error mlgm_app_on_run(mlgm_app *app)
{
    mlgm_module_lifecycle_caller caller;
    mlgm_module_manager *man = &app->modules.manager;
    mlgm_error err = mlgm_module_lifecycle_caller_init(&caller, man);
    if (err)
    {
        return err;
    }
    caller.backward = NO;
    caller.phase = PHASE_RUN;
    return mlgm_module_lifecycle_caller_call(&caller);
}

mlgm_error mlgm_app_on_pause(mlgm_app *app)
{
    mlgm_module_lifecycle_caller caller;
    mlgm_module_manager *man = &app->modules.manager;
    mlgm_error err = mlgm_module_lifecycle_caller_init(&caller, man);
    if (err)
    {
        return err;
    }
    caller.backward = YES;
    caller.phase = PHASE_PAUSE;
    return mlgm_module_lifecycle_caller_call(&caller);
}

mlgm_error mlgm_app_on_stop(mlgm_app *app)
{
    mlgm_module_lifecycle_caller caller;
    mlgm_module_manager *man = &app->modules.manager;
    mlgm_error err = mlgm_module_lifecycle_caller_init(&caller, man);
    if (err)
    {
        return err;
    }
    caller.backward = YES;
    caller.phase = PHASE_STOP;
    return mlgm_module_lifecycle_caller_call(&caller);
}

mlgm_error mlgm_app_on_destroy(mlgm_app *app)
{
    mlgm_module_lifecycle_caller caller;
    mlgm_module_manager *man = &app->modules.manager;
    mlgm_error err = mlgm_module_lifecycle_caller_init(&caller, man);
    if (err)
    {
        return err;
    }
    caller.backward = YES;
    caller.phase = PHASE_DESTROY;
    return mlgm_module_lifecycle_caller_call(&caller);
}

////////////////////////////////////////////////////////////////////////////////
