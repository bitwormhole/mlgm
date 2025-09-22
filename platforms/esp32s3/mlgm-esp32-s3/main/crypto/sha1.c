
#include "sha1.h"

#include "../mlgm_hex.h"

#include <memory.h>
#include "esp_tls.h"
#include "mbedtls/sha1.h"

////////////////////////////////////////////////////////////////////////////////

mlgm_sha1_sum mlgm_sha1_compute(const void *data, mlgm_size len)
{
    mlgm_sha1_sum sum;
    memset(&sum, 0, sizeof(sum));

    if ((data == NIL) || (len < 1))
    {
        data = "";
        len = 0;
    }

    mbedtls_sha1_context ctx;
    mbedtls_sha1_init(&ctx);
    mbedtls_sha1_starts(&ctx);            // : int
    mbedtls_sha1_update(&ctx, data, len); // : int
    mbedtls_sha1_finish(&ctx, sum.body);  // : int
    mbedtls_sha1_free(&ctx);

    return sum;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
