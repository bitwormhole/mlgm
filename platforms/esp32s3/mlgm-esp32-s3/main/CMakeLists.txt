idf_component_register(
    SRCS "crypto/sum_fn.c" "crypto/md5.c" "crypto/sha1.c" "crypto/sha256.c" "module_runtime_test.c" "mlgm_unit.c" "mlgm_app.c" "mlgm_bytes.c" "mlgm_errors.c" "mlgm_hex.c" "module_pktline_server.c" "module_sd_card.c" "module_usb_hid.c" "module_wifi_comm.c" "mlgm_logger.c" "mlgm_time.c" "mlgm_pktline.c" "mlgm_format.c" "mlgm_module.c" "module_udp_debug.c" "module_ble_comm.c" "tusb_hid_example_main.c"
    INCLUDE_DIRS "." "./crypto" "./units"
    PRIV_REQUIRES esp_driver_gpio  mbedtls nvs_flash esp-tls
    )
