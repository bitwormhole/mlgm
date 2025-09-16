#include "mlgm_format.h"
#include "mlgm_logger.h"
#include "mlgm_errors.h"

#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MLGM_LOGGER_BUFFER_SIZE 256
#define MLGM_ERROR_MSG_BUFFER_SIZE 256

////////////////////////////////////////////////////////////////////////////////

#define MLGM_LOGGER_LOG_WITH_LEVEL(__LEVEL__)        \
    const mlgm_logger_level level = __LEVEL__;       \
                                                     \
    char buffer[MLGM_LOGGER_BUFFER_SIZE];            \
    va_list args;                                    \
    va_start(args, format);                          \
    vsnprintf(buffer, sizeof(buffer), format, args); \
    va_end(args);                                    \
    mlgm_logger_output(level, tag, buffer);

////////////////////////////////////////////////////////////////////////////////

void mlgm_logger_info(mlgm_logger_tag *tag, mlgm_string format, ...)
{
    MLGM_LOGGER_LOG_WITH_LEVEL(MLGM_LOGGER_INFO);
}

void mlgm_logger_error(mlgm_logger_tag *tag, mlgm_string format, ...)
{
    MLGM_LOGGER_LOG_WITH_LEVEL(MLGM_LOGGER_ERROR);
}

void mlgm_logger_warn(mlgm_logger_tag *tag, mlgm_string format, ...)
{
    MLGM_LOGGER_LOG_WITH_LEVEL(MLGM_LOGGER_WARN);
}

void mlgm_logger_debug(mlgm_logger_tag *tag, mlgm_string format, ...)
{
    MLGM_LOGGER_LOG_WITH_LEVEL(MLGM_LOGGER_DEBUG);
}

void mlgm_logger_trace(mlgm_logger_tag *tag, mlgm_string format, ...)
{
    MLGM_LOGGER_LOG_WITH_LEVEL(MLGM_LOGGER_TRACE);
}

void mlgm_logger_fatal(mlgm_logger_tag *tag, mlgm_string format, ...)
{
    MLGM_LOGGER_LOG_WITH_LEVEL(MLGM_LOGGER_FATAL);
}

////////////////////////////////////////////////////////////////////////////////

mlgm_error mlgm_error_make_with_format(mlgm_int code, mlgm_string format, ...)
{
    char buffer[MLGM_ERROR_MSG_BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    return mlgm_error_make(code, buffer);
}

////////////////////////////////////////////////////////////////////////////////

mlgm_string mlgm_format(mlgm_byte *buffer, mlgm_uint buffer_size, mlgm_string format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf((char *)buffer, buffer_size, format, args);
    va_end(args);
    return (char *)buffer;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
