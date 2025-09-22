
#include "sha256.h"

#include "../mlgm_hex.h"

#include <memory.h>
#include "mbedtls/sha256.h"

////////////////////////////////////////////////////////////////////////////////

mlgm_sha256_sum mlgm_sha256_compute(const void *data, mlgm_size len)
{
    mlgm_sha256_sum sum;
    memset(&sum, 0, sizeof(sum));

    if ((data == NIL) || (len < 1))
    {
        data = "";
        len = 0;
    }

    mbedtls_sha256_context ctx;
    mbedtls_sha256_init(&ctx);
    mbedtls_sha256_starts(&ctx, NO);        // : int
    mbedtls_sha256_update(&ctx, data, len); // : int
    mbedtls_sha256_finish(&ctx, sum.body);  // : int
    mbedtls_sha256_free(&ctx);

    return sum;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
