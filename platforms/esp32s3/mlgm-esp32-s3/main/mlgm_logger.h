
#ifndef __mlgm_logger_h__
#define __mlgm_logger_h__

#include "mlgm_types.h"

typedef char mlgm_logger_level;

#define MLGM_LOGGER_TRACE 1
#define MLGM_LOGGER_DEBUG 2
#define MLGM_LOGGER_INFO 3
#define MLGM_LOGGER_WARN 4
#define MLGM_LOGGER_ERROR 5
#define MLGM_LOGGER_FATAL 6

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_logger_tag
{
    mlgm_string major;
    mlgm_string minor;

} mlgm_logger_tag;

////////////////////////////////////////////////////////////////////////////////

mlgm_bool mlgm_logger_accept_level(mlgm_logger_level level);

void mlgm_logger_output(mlgm_logger_level level, mlgm_logger_tag *tag, mlgm_string msg);

void mlgm_logger_info(mlgm_logger_tag *tag, mlgm_string format, ...);
void mlgm_logger_warn(mlgm_logger_tag *tag, mlgm_string format, ...);
void mlgm_logger_fatal(mlgm_logger_tag *tag, mlgm_string format, ...);
void mlgm_logger_error(mlgm_logger_tag *tag, mlgm_string format, ...);
void mlgm_logger_debug(mlgm_logger_tag *tag, mlgm_string format, ...);
void mlgm_logger_trace(mlgm_logger_tag *tag, mlgm_string format, ...);

#endif // __mlgm_logger_h__
