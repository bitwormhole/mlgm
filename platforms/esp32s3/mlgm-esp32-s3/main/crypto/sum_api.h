
#ifndef __crypto_sum_api_h__
#define __crypto_sum_api_h__

#include "../mlgm_types.h"
#include "../mlgm_errors.h"

#include "crypto_api.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_sum_head
{
    mlgm_crypto_algorithm algorithm; // [MD5|SHA1|SHA256|...]
    mlgm_size size;                  // size in bytes
    mlgm_byte sum[0];                // 定位 byte[] 的开头

} mlgm_sum_head;

////////////////////////////////////////////////////////////////////////////////

#endif // __crypto_sum_api_h__
