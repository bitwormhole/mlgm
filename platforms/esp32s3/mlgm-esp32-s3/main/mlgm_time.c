#include "mlgm_time.h"

#include "mlgm_logger.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void mlgm_time_sleep(mlgm_time_span ms)
{
    if (ms < 1)
    {
        return;
    }
    mlgm_int64 ticks = ms / portTICK_PERIOD_MS;
    vTaskDelay(ticks);
}

void mlgm_time_sleep_infinity(mlgm_string tag)
{
    mlgm_int index = 0;
    mlgm_time_stamp t1 = 0;
    mlgm_time_span step = 1000;
    if (tag == NIL)
    {
        tag = "nil";
    }
    for (;;)
    {
        mlgm_logger_info(NIL, "mlgm_time_sleep_infinity(%s): index=%d, time_at=%llu", tag, index, t1 / 1000);
        mlgm_time_sleep(step);
        t1 += step;
        if (step < (3600 * 1000))
        {
            step *= 2;
        }
        index++;
    }
}
