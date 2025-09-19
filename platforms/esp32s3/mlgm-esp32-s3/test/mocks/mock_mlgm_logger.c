#include "../unit_include.h"

void mlgm_logger_output(mlgm_logger_level level, mlgm_logger_tag *tag, mlgm_string msg)
{
    char l = '?';
    switch (level)
    {
    case MLGM_LOGGER_INFO:
        l = 'I';
        break;
    case MLGM_LOGGER_WARN:
        l = 'W';
        break;
    case MLGM_LOGGER_ERROR:
        l = 'E';
        break;
    case MLGM_LOGGER_DEBUG:
        l = 'D';
        break;
    case MLGM_LOGGER_TRACE:
        l = 'T';
        break;
    case MLGM_LOGGER_FATAL:
        l = 'F';
        break;
    default:
        break;
    }
    printf("mlgm_logger_output(%c): %s\n", l, msg);
}
