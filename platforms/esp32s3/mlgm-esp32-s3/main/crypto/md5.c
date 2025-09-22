
#include "md5.h"

#include "../mlgm_hex.h"

#include <memory.h>
#include "mbedtls/md5.h"

////////////////////////////////////////////////////////////////////////////////

mlgm_md5_sum mlgm_md5_compute(const void *data, mlgm_size len)
{
    mlgm_md5_sum sum;
    memset(&sum, 0, sizeof(sum));

    if ((data == NIL) || (len < 1))
    {
        data = "";
        len = 0;
    }

    mbedtls_md5_context ctx;
    mbedtls_md5_init(&ctx);
    mbedtls_md5_starts(&ctx);            // : int
    mbedtls_md5_update(&ctx, data, len); // : int
    mbedtls_md5_finish(&ctx, sum.body);  // : int
    mbedtls_md5_free(&ctx);

    return sum;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
