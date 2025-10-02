
#ifndef __mlgm_structures_h__
#define __mlgm_structures_h__

#include "mlgm_types.h"

////////////////////////////////////////////////////////////////////////////////

struct t_mlgm_app;

struct t_mlgm_app_context;

struct t_mlgm_module;

struct t_mlgm_unit;

struct t_mlgm_module_manager;

struct t_sd_card_module;
struct t_usb_hid_module;
struct t_ble_comm_module;
struct t_wifi_comm_module;
struct t_udp_debug_module;
struct t_runtime_test_module;

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_app mlgm_app;

typedef struct t_mlgm_app_context mlgm_app_context;

typedef struct t_mlgm_module mlgm_module;

typedef struct t_mlgm_unit mlgm_unit;

typedef struct t_mlgm_module_manager mlgm_module_manager;

typedef struct t_sd_card_module sd_card_module;
typedef struct t_usb_hid_module usb_hid_module;
typedef struct t_ble_comm_module ble_comm_module;
typedef struct t_wifi_comm_module wifi_comm_module;
typedef struct t_udp_debug_module udp_debug_module;
typedef struct t_runtime_test_module runtime_test_module;

////////////////////////////////////////////////////////////////////////////////

#endif // __mlgm_structures_h__
