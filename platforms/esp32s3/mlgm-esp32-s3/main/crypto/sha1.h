#ifndef __crypto_sha1_h__
#define __crypto_sha1_h__

#include "../mlgm_types.h"
#include "../mlgm_errors.h"

#include "sum_api.h"

#define MLGM_SHA1_SUM_LENGTH_IN_BITS 160
#define MLGM_SHA1_SUM_LENGTH_IN_BYTES (MLGM_SHA1_SUM_LENGTH_IN_BITS / 8)

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_sha1_sum
{
    // 注意： 这里的 body 必须紧跟在 head 后面， 以便使 head.sum 的地址跟 body 一致。

    mlgm_sum_head head;
    mlgm_byte body[MLGM_SHA1_SUM_LENGTH_IN_BYTES];

} mlgm_sha1_sum;

mlgm_error mlgm_sha1_sum_init(mlgm_sha1_sum *self);
mlgm_error mlgm_sha1_sum_init_with_hex_string(mlgm_sha1_sum *self, mlgm_string hex);

mlgm_sha1_sum mlgm_sha1_sum_from_hex_string(mlgm_string hex);
mlgm_string mlgm_sha1_sum_to_hex_string(mlgm_sha1_sum *self, mlgm_char *dst, mlgm_size dst_cap);

mlgm_bool mlgm_sha1_sum_equals(mlgm_sha1_sum *self, mlgm_sha1_sum *other);
mlgm_int mlgm_sha1_sum_compare(mlgm_sha1_sum *self, mlgm_sha1_sum *other);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_sha1
{
    mlgm_int todo;
} sha1;

mlgm_sha1_sum mlgm_sha1_compute(const void *const data, mlgm_size len);

#endif //  __crypto_sha1_h__
