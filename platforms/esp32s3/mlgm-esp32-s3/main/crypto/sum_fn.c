
#include "sha1.h"
#include "sha256.h"
#include "md5.h"

#include "../mlgm_hex.h"

#include <memory.h>

////////////////////////////////////////////////////////////////////////////////
// mlgm_sha256_sum

mlgm_sha256_sum mlgm_sha256_sum_from_hex_string(mlgm_string hex)
{
    mlgm_sha256_sum sum;
    mlgm_sha256_sum_init(&sum);
    if (hex == NIL)
    {
        return sum;
    }
    void *dst = sum.head.sum;
    mlgm_size dst_cap = sizeof(sum.body);
    mlgm_size src_len = strlen(hex);
    mlgm_error err = mlgm_hex_parse_string(hex, src_len, dst, dst_cap);
    if (err)
    {
        memset(&sum, 0, sizeof(sum));
    }
    return sum;
}

mlgm_error mlgm_sha256_sum_init(mlgm_sha256_sum *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        self->head.algorithm = MLGM_HASH_ALGORITHM_SHA256;
        self->head.size = sizeof(self->body);
        return NIL;
    }
    return mlgm_error_make(500, "param:self is nil");
}

mlgm_error mlgm_sha256_sum_init_with_hex_string(mlgm_sha256_sum *self, mlgm_string hex)
{
    if (self && hex)
    {
        mlgm_sha256_sum_init(self);
        void *dst = self->body;
        mlgm_size dst_cap = sizeof(self->body);
        mlgm_size src_len = strlen(hex);
        mlgm_error err = mlgm_hex_parse_string(hex, src_len, dst, dst_cap);
        return err;
    }
    return mlgm_error_make(500, "mlgm_sha256_sum_init_with_hex_string: param is nil");
}

mlgm_bool mlgm_sha256_sum_equals(mlgm_sha256_sum *self, mlgm_sha256_sum *other)
{
    int cmp = mlgm_sha256_sum_compare(self, other);
    return (cmp == 0);
}

mlgm_int mlgm_sha256_sum_compare(mlgm_sha256_sum *self, mlgm_sha256_sum *other)
{
    if (self && other)
    {
        mlgm_size len = sizeof(self->body);
        return memcmp(self->body, other->body, len);
    }
    return (self) ? 999 : -999;
}

////////////////////////////////////////////////////////////////////////////////
// mlgm_sha1_sum

mlgm_string mlgm_sha1_sum_to_hex_string(mlgm_sha1_sum *self, mlgm_char *dst, mlgm_size dst_cap)
{
    mlgm_byte *sum_bin = self->body;
    mlgm_size sum_len = sizeof(self->body);
    mlgm_error err = mlgm_hex_to_string(sum_bin, sum_len, dst, dst_cap);
    if (err)
    {
        return NIL;
    }
    return dst;
}

mlgm_sha1_sum mlgm_sha1_sum_from_hex_string(mlgm_string hex)
{
    mlgm_sha1_sum sum;
    mlgm_sha1_sum_init(&sum);
    if (hex == NIL)
    {
        return sum;
    }
    void *dst = sum.head.sum;
    mlgm_size dst_cap = sizeof(sum.body);
    mlgm_size src_len = strlen(hex);
    mlgm_error err = mlgm_hex_parse_string(hex, src_len, dst, dst_cap);
    if (err)
    {
        memset(&sum, 0, sizeof(sum));
    }
    return sum;
}

mlgm_error mlgm_sha1_sum_init(mlgm_sha1_sum *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        self->head.algorithm = MLGM_HASH_ALGORITHM_SHA1;
        self->head.size = sizeof(self->body);
        return NIL;
    }
    return mlgm_error_make(500, "param:self is nil");
}

mlgm_error mlgm_sha1_sum_init_with_hex_string(mlgm_sha1_sum *self, mlgm_string hex)
{
    if (self && hex)
    {
        mlgm_sha1_sum_init(self);
        void *dst = self->body;
        mlgm_size dst_cap = sizeof(self->body);
        mlgm_size src_len = strlen(hex);
        mlgm_error err = mlgm_hex_parse_string(hex, src_len, dst, dst_cap);
        return err;
    }
    return mlgm_error_make(500, "mlgm_sha1_sum_init_with_hex_string: param is nil");
}

mlgm_bool mlgm_sha1_sum_equals(mlgm_sha1_sum *self, mlgm_sha1_sum *other)
{
    int cmp = mlgm_sha1_sum_compare(self, other);
    return (cmp == 0);
}

mlgm_int mlgm_sha1_sum_compare(mlgm_sha1_sum *self, mlgm_sha1_sum *other)
{

    if (self && other)
    {
        mlgm_size len = sizeof(self->body);
        return memcmp(self->body, other->body, len);
    }
    return (self) ? 999 : -999;
}

////////////////////////////////////////////////////////////////////////////////
// mlgm_md5_sum

mlgm_md5_sum mlgm_md5_sum_from_hex_string(mlgm_string hex)
{
    mlgm_md5_sum sum;
    mlgm_md5_sum_init(&sum);
    if (hex == NIL)
    {
        return sum;
    }
    void *dst = sum.head.sum;
    mlgm_size dst_cap = sizeof(sum.body);
    mlgm_size src_len = strlen(hex);
    mlgm_error err = mlgm_hex_parse_string(hex, src_len, dst, dst_cap);
    if (err)
    {
        memset(&sum, 0, sizeof(sum));
    }
    return sum;
}

mlgm_error mlgm_md5_sum_init(mlgm_md5_sum *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        self->head.algorithm = MLGM_HASH_ALGORITHM_MD5;
        self->head.size = sizeof(self->body);
        return NIL;
    }
    return mlgm_error_make(500, "param:self is nil");
}

mlgm_error mlgm_md5_sum_init_with_hex_string(mlgm_md5_sum *self, mlgm_string hex)
{
    if (self && hex)
    {
        mlgm_md5_sum_init(self);
        void *dst = self->body;
        mlgm_size dst_cap = sizeof(self->body);
        mlgm_size src_len = strlen(hex);
        mlgm_error err = mlgm_hex_parse_string(hex, src_len, dst, dst_cap);
        return err;
    }
    return mlgm_error_make(500, "mlgm_md5_sum_init_with_hex_string: param is nil");
}

mlgm_bool mlgm_md5_sum_equals(mlgm_md5_sum *self, mlgm_md5_sum *other)
{
    int cmp = mlgm_md5_sum_compare(self, other);
    return (cmp == 0);
}

mlgm_int mlgm_md5_sum_compare(mlgm_md5_sum *self, mlgm_md5_sum *other)
{
    if (self && other)
    {
        mlgm_size len = sizeof(self->body);
        return memcmp(self->body, other->body, len);
    }
    return (self) ? 999 : -999;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
