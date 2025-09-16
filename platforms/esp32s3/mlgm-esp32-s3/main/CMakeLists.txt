idf_component_register(
    SRCS "mlgm_app.c" "mlgm_bytes.c" "mlgm_errors.c" "mlgm_hex.c" "module_pktline_server.c" "module_sd_card.c" "module_usb_hid.c" "module_wifi_comm.c" "mlgm_logger.c" "mlgm_time.c" "mlgm_pktline.c" "mlgm_format.c" "mlgm_module.c" "module_udp_debug.c" "module_ble_comm.c" "tusb_hid_example_main.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES esp_driver_gpio
    )
