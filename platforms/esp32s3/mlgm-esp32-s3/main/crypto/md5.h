#ifndef __crypto_md5_h__
#define __crypto_md5_h__

#include "../mlgm_types.h"
#include "../mlgm_errors.h"

#include "sum_api.h"

#define MLGM_MD5_SUM_LENGTH_IN_BITS 128
#define MLGM_MD5_SUM_LENGTH_IN_BYTES (MLGM_MD5_SUM_LENGTH_IN_BITS / 8)

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_md5_sum
{
    // 注意： 这里的 body 必须紧跟在 head 后面， 以便使 head.sum 的地址跟 body 一致。

    mlgm_sum_head head;
    mlgm_byte body[MLGM_MD5_SUM_LENGTH_IN_BYTES];

} mlgm_md5_sum;

mlgm_error mlgm_md5_sum_init(mlgm_md5_sum *self);
mlgm_error mlgm_md5_sum_init_with_hex_string(mlgm_md5_sum *self, mlgm_string hex);

mlgm_md5_sum mlgm_md5_sum_from_hex_string(mlgm_string hex);

mlgm_bool mlgm_md5_sum_equals(mlgm_md5_sum *self, mlgm_md5_sum *other);
mlgm_int mlgm_md5_sum_compare(mlgm_md5_sum *self, mlgm_md5_sum *other);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_md5
{
    mlgm_int todo;
} md5;

mlgm_md5_sum mlgm_md5_compute(const void *const data, mlgm_size len);

#endif //  __crypto_md5_h__
