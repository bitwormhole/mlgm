
#ifndef __mlgm_strings_h__
#define __mlgm_strings_h__

#include "mlgm_types.h"
#include "mlgm_bytes.h"
#include "mlgm_defer.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_string_builder mlgm_string_builder;

typedef struct t_mlgm_string_builder_holder mlgm_string_builder_holder;

typedef struct t_mlgm_string_builder_pool mlgm_string_builder_pool;

typedef struct t_mlgm_string_builder_pool_entity mlgm_string_builder_pool_entity;

typedef struct t_mlgm_string_slice mlgm_string_slice;

////////////////////////////////////////////////////////////////////////////////
// mlgm_string_slice

// mlgm_string_slice 表示字符串的一部分， 其长度由字段 'len' 决定, 没有以 '\0' 结尾
typedef struct t_mlgm_string_slice
{

    mlgm_string raw;
    mlgm_size offset;
    mlgm_size length;

    // optional: 如果存在 writer 字段，表示这个对象是 rewritable 的
    mlgm_string_builder *writer;

} mlgm_string_slice;

mlgm_string_slice *mlgm_string_slice_init(mlgm_string_slice *self);

mlgm_string_slice *mlgm_string_slice_init_with_string(mlgm_string_slice *self, mlgm_string str);

mlgm_string_slice *mlgm_string_slice_init_with_buffer(mlgm_string_slice *self, mlgm_string_builder *buffer);

mlgm_string_slice mlgm_string_slice_trim_space(mlgm_string_slice *self);

mlgm_string_slice mlgm_string_slice_sub_string(mlgm_string_slice *self, int start_at, int end_at);

mlgm_error mlgm_string_slice_write_to(mlgm_string_slice *self, mlgm_string_slice *dst);

mlgm_bool mlgm_string_slice_has_prefix(mlgm_string_slice *self, mlgm_string prefix);

mlgm_bool mlgm_string_slice_has_suffix(mlgm_string_slice *self, mlgm_string suffix);

mlgm_bool mlgm_string_slice_is_rewritable(mlgm_string_slice *self);

int mlgm_string_slice_index_of_char(mlgm_string_slice *self, mlgm_char ch);
int mlgm_string_slice_index_of_string(mlgm_string_slice *self, mlgm_string str);

int mlgm_string_slice_last_index_of_char(mlgm_string_slice *self, mlgm_char ch);
int mlgm_string_slice_last_index_of_string(mlgm_string_slice *self, mlgm_string str);

////////////////////////////////////////////////////////////////////////////////
// mlgm_string_builder

typedef struct t_mlgm_string_builder
{

    mlgm_bytes_buffer buffer;

} mlgm_string_builder;

mlgm_string_builder *mlgm_string_builder_init(mlgm_string_builder *self);
mlgm_string_builder *mlgm_string_builder_init_with_size(mlgm_string_builder *self, mlgm_size size);
mlgm_string_builder *mlgm_string_builder_init_with_buffer(mlgm_string_builder *self, void *buf, mlgm_size buf_cap);

mlgm_string_builder *mlgm_string_builder_reset(mlgm_string_builder *self);

mlgm_string_builder *mlgm_string_builder_append_string(mlgm_string_builder *self, mlgm_string str);
mlgm_string_builder *mlgm_string_builder_append_string_slice(mlgm_string_builder *self, mlgm_string_slice *slice);
mlgm_string_builder *mlgm_string_builder_append_uint(mlgm_string_builder *self, mlgm_uint n);
mlgm_string_builder *mlgm_string_builder_append_int(mlgm_string_builder *self, mlgm_int n);
mlgm_string_builder *mlgm_string_builder_append_bool(mlgm_string_builder *self, mlgm_bool b);
mlgm_string_builder *mlgm_string_builder_append_char(mlgm_string_builder *self, mlgm_char n);
mlgm_string_builder *mlgm_string_builder_append_byte(mlgm_string_builder *self, mlgm_byte n);

// alias: mlgm_string_builder_string == mlgm_string_builder_build
mlgm_string mlgm_string_builder_build(mlgm_string_builder *self);

// alias: mlgm_string_builder_string == mlgm_string_builder_build
mlgm_string mlgm_string_builder_string(mlgm_string_builder *self);

mlgm_size mlgm_string_builder_length(mlgm_string_builder *self);
mlgm_error mlgm_string_builder_error(mlgm_string_builder *self);

void mlgm_string_builder_release(mlgm_string_builder *self);

////////////////////////////////////////////////////////////////////////////////
// mlgm_string_builder_holder

typedef struct t_mlgm_string_builder_holder
{

    mlgm_deferable auto_release;

    mlgm_string_builder *builder;

    mlgm_string_builder_pool *pool;

} mlgm_string_builder_holder;

void mlgm_string_builder_holder_init(mlgm_string_builder_holder *self, mlgm_size size);

void mlgm_string_builder_holder_release(mlgm_string_builder_holder *self);

void mlgm_string_builder_holder_auto_release(mlgm_string_builder_holder *self, mlgm_defer_manager *dm);

////////////////////////////////////////////////////////////////////////////////
// mlgm_string_builder_pool

typedef struct t_mlgm_string_builder_pool
{

    mlgm_string_builder_pool_entity *entity;

    mlgm_size min_buffer_size;
    mlgm_size max_buffer_size;

} mlgm_string_builder_pool;

mlgm_string_builder_pool *mlgm_string_builder_pool_get_default_pool();

void mlgm_string_builder_pool_init(mlgm_string_builder_pool *self);
void mlgm_string_builder_pool_destroy(mlgm_string_builder_pool *self);

mlgm_string_builder *mlgm_string_builder_pool_open_builder(mlgm_string_builder_pool *self, mlgm_size want_size);
void mlgm_string_builder_pool_close_builder(mlgm_string_builder_pool *self, mlgm_string_builder *builder);

////////////////////////////////////////////////////////////////////////////////

#endif //  __mlgm_strings_h__
