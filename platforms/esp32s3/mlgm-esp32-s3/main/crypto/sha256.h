#ifndef __crypto_sha256_h__
#define __crypto_sha256_h__

#include "../mlgm_types.h"
#include "../mlgm_errors.h"

#include "sum_api.h"

#define MLGM_SHA256_SUM_LENGTH_IN_BITS 256
#define MLGM_SHA256_SUM_LENGTH_IN_BYTES (MLGM_SHA256_SUM_LENGTH_IN_BITS / 8)

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_sha256_sum
{
    // 注意： 这里的 body 必须紧跟在 head 后面， 以便使 head.sum 的地址跟 body 一致。

    mlgm_sum_head head;
    mlgm_byte body[MLGM_SHA256_SUM_LENGTH_IN_BYTES];

} mlgm_sha256_sum;

mlgm_error mlgm_sha256_sum_init(mlgm_sha256_sum *self);
mlgm_error mlgm_sha256_sum_init_with_hex_string(mlgm_sha256_sum *self, mlgm_string hex);

mlgm_sha256_sum mlgm_sha256_sum_from_hex_string(mlgm_string hex);

mlgm_bool mlgm_sha256_sum_equals(mlgm_sha256_sum *self, mlgm_sha256_sum *other);
mlgm_int mlgm_sha256_sum_compare(mlgm_sha256_sum *self, mlgm_sha256_sum *other);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_sha256
{
    mlgm_int todo;
} sha256;

mlgm_sha256_sum mlgm_sha256_compute(const void *const data, mlgm_size len);

#endif //  __crypto_sha256_h__
