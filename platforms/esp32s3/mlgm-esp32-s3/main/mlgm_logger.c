#include "mlgm_logger.h"

#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

////////////////////////////////////////////////////////////////////////////////

// 备注：以下这些函数放在源文件 "mlgm_format.c" 中实现：
//
// void mlgm_logger_info(mlgm_logger_tag *tag, mlgm_string format, ...);
// void mlgm_logger_warn(mlgm_logger_tag *tag, mlgm_string format, ...);
// void mlgm_logger_fatal(mlgm_logger_tag *tag, mlgm_string format, ...);
// void mlgm_logger_error(mlgm_logger_tag *tag, mlgm_string format, ...);
// void mlgm_logger_debug(mlgm_logger_tag *tag, mlgm_string format, ...);
// void mlgm_logger_trace(mlgm_logger_tag *tag, mlgm_string format, ...);

////////////////////////////////////////////////////////////////////////////////

#define MLGM_LOGGER_ACCEPTED_LEVEL_MIN MLGM_LOGGER_INFO

#define MLGM_LOGGER_TAG "MLGM"

////////////////////////////////////////////////////////////////////////////////

mlgm_bool mlgm_logger_accept_level(mlgm_logger_level level)
{
    return (level >= MLGM_LOGGER_ACCEPTED_LEVEL_MIN);
}

void mlgm_logger_output(mlgm_logger_level level, mlgm_logger_tag *tag, mlgm_string msg)
{
    if (!mlgm_logger_accept_level(level))
    {
        return;
    }

    switch (level)
    {
    case MLGM_LOGGER_INFO:
        ESP_LOGI(MLGM_LOGGER_TAG, "%s", msg);
        break;
    case MLGM_LOGGER_WARN:
        ESP_LOGW(MLGM_LOGGER_TAG, "%s", msg);
        break;
    case MLGM_LOGGER_ERROR:
        ESP_LOGE(MLGM_LOGGER_TAG, "%s", msg);
        break;
    case MLGM_LOGGER_FATAL:
        ESP_LOGE(MLGM_LOGGER_TAG, "%s", msg);
        break;
    case MLGM_LOGGER_DEBUG:
        ESP_LOGD(MLGM_LOGGER_TAG, "%s", msg);
        break;
    case MLGM_LOGGER_TRACE:
        ESP_LOGV(MLGM_LOGGER_TAG, "%s", msg);
        break;
    default:
        break;
    }
}
