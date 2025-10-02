#ifndef __app_h__
#define __app_h__

#include "mlgm_types.h"
#include "mlgm_structures.h"

#include "module_ble_comm.h"
#include "module_sd_card.h"
#include "module_usb_hid.h"
#include "module_wifi_comm.h"
#include "module_udp_debug.h"
#include "module_runtime_test.h"

typedef struct t_mlgm_app_context
{

    // 这里面包含的都是引用

    mlgm_app *app;
    mlgm_module_manager *modules;

    sd_card_module *sd;
    usb_hid_module *usb;
    ble_comm_module *ble;
    wifi_comm_module *wifi;
    udp_debug_module *udp;
    runtime_test_module *rttest;

} mlgm_app_context;

typedef struct t_mlgm_app
{

    // 这里面包含的都是实体

    mlgm_app_context context;
    mlgm_module_manager modules;

    ble_comm_module ble;
    usb_hid_module usb;
    sd_card_module sd;
    wifi_comm_module wifi;
    udp_debug_module udp;
    runtime_test_module rttest;

} mlgm_app;

mlgm_error mlgm_app_run(mlgm_app *app);

#endif // __app_h__
