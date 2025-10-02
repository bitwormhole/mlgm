#include "module_sd_card.h"

#include "mlgm_logger.h"
#include "mlgm_config.h"
#include "mlgm_time.h"
#include "mlgm_strings.h"

#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"

#include <memory.h>

////////////////////////////////////////////////////////////////////////////////

#define SD_CARD_MOUNT_POINT "/sdcard"

#define TAG NIL

// IN  "mlgm_config.h" ：
// #define MLGM_CONFIG_SDMMC_PIN_CMD 35
// #define MLGM_CONFIG_SDMMC_PIN_CLK 36
// #define MLGM_CONFIG_SDMMC_PIN_D0 37
// #define MLGM_CONFIG_SDMMC_PIN_D1 33
// #define MLGM_CONFIG_SDMMC_PIN_D2 38
// #define MLGM_CONFIG_SDMMC_PIN_D3 34

static const char sd_card_mount_point[] = SD_CARD_MOUNT_POINT;

////////////////////////////////////////////////////////////////////////////////
// sd_card_module_body

typedef struct t_sd_card_module_body
{

    sd_card_module *owner;
    sd_card_module_body *self;

    esp_vfs_fat_sdmmc_mount_config_t mount_config;
    sdmmc_slot_config_t slot_config;
    sdmmc_host_t host;
    sdmmc_card_t *card;
    mlgm_string mount_point;

} sd_card_module_body;

sd_card_module_body *sd_card_module_get_body(mlgm_module *m);
sd_card_module *sd_card_module_get_facade(mlgm_module *m);

sd_card_module_body *sd_card_module_make_body(sd_card_module *m);

sd_card_module_body *sd_card_module_body_init(sd_card_module_body *body, sd_card_module *m2);
void sd_card_module_body_release(sd_card_module_body *body);
void sd_card_module_body_starting_delay(sd_card_module_body *inner, mlgm_time_span delay);

////////////////////////////////////////////////////////////////////////////////

mlgm_error sd_card_module_on_create(mlgm_module *m);
mlgm_error sd_card_module_on_start(mlgm_module *m);
mlgm_error sd_card_module_on_resume(mlgm_module *m);

mlgm_error sd_card_module_on_run(mlgm_module *m);

mlgm_error sd_card_module_on_pause(mlgm_module *m);
mlgm_error sd_card_module_on_stop(mlgm_module *m);
mlgm_error sd_card_module_on_destroy(mlgm_module *m);

////////////////////////////////////////////////////////////////////////////////

mlgm_error sd_card_module_on_create(mlgm_module *m1)
{

    // mlgm_logger_debug(NIL, "sd_card_module_on_create(): todo ...");

    sd_card_module *m2 = sd_card_module_get_instance(m1);
    if (m2)
    {
        sd_card_module_body *body = m2->body;
        if (body == NIL)
        {
            body = sd_card_module_make_body(m2);
            m2->body = body;
        }
        if (body)
        {
            sd_card_module_body_starting_delay(body, 3000);
        }
    }

    return NIL;
}

mlgm_error sd_card_module_on_start(mlgm_module *m)
{
    esp_err_t ret;

    sd_card_module_body *body = sd_card_module_get_body(m);
    if (body == NIL)
    {
        return mlgm_error_make(500, "sd_card_module_on_start: body is nil");
    }

    // config

    sdmmc_host_t host_def = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_def = SDMMC_SLOT_CONFIG_DEFAULT();

    body->slot_config = slot_def;
    body->host = host_def;

    sdmmc_card_t *card = NIL;
    sdmmc_slot_config_t *slot_config = &body->slot_config;
    sdmmc_host_t *host = &body->host;
    esp_vfs_fat_sdmmc_mount_config_t *mount_config = &body->mount_config;
    mlgm_string mount_point = sd_card_mount_point; // inner->mount_point;

    host->max_freq_khz = SDMMC_FREQ_DEFAULT;
    host->slot = SDMMC_HOST_SLOT_1;

    mount_config->format_if_mount_failed = NO;
    mount_config->max_files = 5;
    mount_config->allocation_unit_size = 16 * 1024;

    slot_config->width = 4;
    slot_config->clk = MLGM_CONFIG_SDMMC_PIN_CLK;
    slot_config->cmd = MLGM_CONFIG_SDMMC_PIN_CMD;
    slot_config->d0 = MLGM_CONFIG_SDMMC_PIN_D0;
    slot_config->d1 = MLGM_CONFIG_SDMMC_PIN_D1;
    slot_config->d2 = MLGM_CONFIG_SDMMC_PIN_D2;
    slot_config->d3 = MLGM_CONFIG_SDMMC_PIN_D3;
    slot_config->flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    // mount

    mlgm_logger_info(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdmmc_mount(mount_point, host, slot_config, mount_config, &card);
    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            mlgm_logger_error(TAG, "Failed to mount filesystem. "
                                   "If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        }
        else
        {
            mlgm_logger_error(TAG, "Failed to initialize the card (%s). "
                                   "Make sure SD card lines have pull-up resistors in place.",
                              esp_err_to_name(ret));

            // #ifdef CONFIG_EXAMPLE_DEBUG_PIN_CONNECTIONS
            // check_sd_card_pins(&config, pin_count);
            // #endif
        }
        return mlgm_error_make(500, "sd_card_module_on_start: esp_vfs_fat_sdmmc_mount() return error");
    }

    mlgm_logger_info(TAG, "Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);

    body->card = card;
    return NIL;
}

mlgm_error sd_card_module_on_resume(mlgm_module *m)
{
    return NIL;
}

mlgm_error sd_card_module_on_run(mlgm_module *m)
{
    return NIL;
}

mlgm_error sd_card_module_on_pause(mlgm_module *m)
{

    mlgm_time_sleep_infinity("sd_card_module_on_pause: loop forever");

    return NIL;
}

mlgm_error sd_card_module_on_stop(mlgm_module *m1)
{

    // unmount
    // All done, unmount partition and disable SDMMC peripheral

    sd_card_module_body *body = sd_card_module_get_body(m1);
    if (body == NIL)
    {
        return mlgm_error_make(500, "sd_card_module_on_stop: inner is nil");
    }

    mlgm_string mount_point = body->mount_point;
    sdmmc_card_t *card = body->card;

    esp_vfs_fat_sdcard_unmount(mount_point, card);
    mlgm_logger_info(NIL, "Card unmounted");

    // Deinitialize the power control driver if it was used
    // #if CONFIG_EXAMPLE_SD_PWR_CTRL_LDO_INTERNAL_IO
    // ret = sd_pwr_ctrl_del_on_chip_ldo(pwr_ctrl_handle);
    // if (ret != ESP_OK)
    // {
    //     ESP_LOGE(TAG, "Failed to delete the on-chip LDO power control driver");
    //     return;
    // }
    // #endif

    return NIL;
}

mlgm_error sd_card_module_on_destroy(mlgm_module *m1)
{
    sd_card_module *m2 = sd_card_module_get_instance(m1);
    if (m2)
    {
        sd_card_module_body *body = m2->body;
        sd_card_module_body_release(body);
        m2->body = NIL;
    }
    return NIL;
}

// sd_card_module_inner *sd_card_module_inner_get_instance(mlgm_module *m)
// {
// }

////////////////////////////////////////////////////////////////////////////////
// sd_card_module_inner

sd_card_module_body *sd_card_module_make_body(sd_card_module *m2)
{
    const size_t size = sizeof(sd_card_module_body);
    sd_card_module_body *body = malloc(size);
    if (body)
    {
        // memset(p, 0, size);

        sd_card_module_body_init(body, m2);
    }
    return body;
}

sd_card_module_body *sd_card_module_body_init(sd_card_module_body *body, sd_card_module *m2)
{
    if (body && m2)
    {
        body->self = body;
        body->owner = m2;
        m2->body = body;
        return body;
    }
    return NIL;
}

void sd_card_module_body_release(sd_card_module_body *body)
{
    if (body)
    {
        sd_card_module *m2 = body->owner;
        if (m2)
        {
            m2->body = NIL;
        }
        free(body);
    }
}

void sd_card_module_body_starting_delay(sd_card_module_body *body, mlgm_time_span delay)
{
    mlgm_time_span ttl = 0;
    mlgm_time_span step = 500;
    for (ttl = delay; ttl > 0; ttl -= step)
    {
        int sec = (ttl / 1000);
        mlgm_logger_info(NIL, "sd_card_module_inner_starting_delay: starting in %d sec ...", sec);
        mlgm_time_sleep(step);
    }
}

////////////////////////////////////////////////////////////////////////////////

mlgm_module *sd_card_init(sd_card_module *m2, mlgm_app_context *ac)
{
    if (m2)
    {
        memset(m2, 0, sizeof(m2[0]));
    }
    else
    {
        return NIL;
    }

    mlgm_module_class clazz = MLGM_MODULE_CLASS_SD_CARD;
    mlgm_string name = "sd_card_module";

    mlgm_module *m1 = &m2->head;
    m1 = mlgm_module_init(m1, ac, clazz, name, m2);
    if (m1)
    {
        m1->on_create = sd_card_module_on_create;
        m1->on_start = sd_card_module_on_start;
        m1->on_resume = sd_card_module_on_resume;

        m1->on_run = sd_card_module_on_run;

        m1->on_pause = sd_card_module_on_pause;
        m1->on_stop = sd_card_module_on_stop;
        m1->on_destroy = sd_card_module_on_destroy;
    }

    m2->self = m2;
    return m1;
}

sd_card_module *sd_card_module_get_instance(mlgm_module *m1)
{
    void *inst = mlgm_module_get_instance(m1, MLGM_MODULE_CLASS_SD_CARD);
    if (inst)
    {
        sd_card_module *m2 = inst;
        if (m2->self == m2)
        {
            return m2;
        }
    }
    return NIL;
}

sd_card_module_body *sd_card_module_get_body(mlgm_module *m1)
{
    sd_card_module *m2 = sd_card_module_get_instance(m1);
    if (m2)
    {
        return m2->body;
    }
    return NIL;
}

mlgm_error sd_card_module_get_mount_path(sd_card_module *m1, mlgm_path *path_out)
{
    if ((m1 == NIL) || (path_out == NIL))
    {
        return mlgm_error_make(500, "sd_card_module_get_mount_path: param(s) is nil");
    }
    path_out->string = sd_card_mount_point;
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
