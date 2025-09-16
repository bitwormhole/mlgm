#include "mlgm_errors.h"

// #include <stdlib.h>

#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct t_inner_mlgm_error_buffer
{
    mlgm_error_info info;
    char text[256];
    char text0;
} inner_mlgm_error_buffer;

static inner_mlgm_error_buffer theMlgmErrorBuffer;

////////////////////////////////////////////////////////////////////////////////

mlgm_error mlgm_error_make(mlgm_int code, mlgm_string msg)
{
    inner_mlgm_error_buffer *pbuf = &theMlgmErrorBuffer;

    char *dst = pbuf->text;
    mlgm_string src = msg;
    size_t size1 = strlen(msg);
    size_t size2 = sizeof(pbuf->text);
    memcpy(dst, src, MLGM_MIN(size1, size2));

    pbuf->info.code = code;
    pbuf->info.message = pbuf->text;
    pbuf->text0 = 0;

    return &pbuf->info;
}

mlgm_string mlgm_error_get_message(mlgm_error err)
{
    if (err)
    {
        mlgm_string msg = err->message;
        return msg;
    }
    return NIL;
}
