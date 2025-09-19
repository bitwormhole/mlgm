
#ifndef __mlgm_bytes_h__
#define __mlgm_bytes_h__

#include "mlgm_types.h"
#include "mlgm_errors.h"

typedef struct t_mlgm_bytes_buffer_entity
{
    mlgm_size body_size;  // 字段： body[] 的实际大小
    mlgm_size total_size; // sizeof(head + body)

    void *self; // 指向这个 entity 本身

    mlgm_byte body[0]; // 数据的开始

} mlgm_bytes_buffer_entity;

typedef struct t_mlgm_bytes_buffer
{
    mlgm_size capacity;
    mlgm_size length;
    mlgm_bool overflow;

    mlgm_byte *data;

    mlgm_bytes_buffer_entity *entity; // 由这个缓冲区托管的数据块实体， 如果没有则为 NIL

} mlgm_bytes_buffer;

typedef struct t_mlgm_string_builder
{

    mlgm_bytes_buffer buffer;

} mlgm_string_builder;

////////////////////////////////////////////////////////////////////////////////

mlgm_bytes_buffer_entity *mlgm_bytes_buffer_entity_make(mlgm_size size);

void mlgm_bytes_buffer_entity_release(mlgm_bytes_buffer_entity *self);

////////////////////////////////////////////////////////////////////////////////

mlgm_bytes_buffer *mlgm_bytes_buffer_init(mlgm_bytes_buffer *self);
mlgm_bytes_buffer *mlgm_bytes_buffer_init_with_size(mlgm_bytes_buffer *self, mlgm_size size);
mlgm_bytes_buffer *mlgm_bytes_buffer_init_with_buffer(mlgm_bytes_buffer *self, void *buffer, mlgm_size cap);

mlgm_bytes_buffer *mlgm_bytes_buffer_reset(mlgm_bytes_buffer *self);

mlgm_bytes_buffer *mlgm_bytes_buffer_write(mlgm_bytes_buffer *self, mlgm_byte *src, mlgm_size src_len);
mlgm_bytes_buffer *mlgm_bytes_buffer_write_byte(mlgm_bytes_buffer *self, mlgm_byte b);
mlgm_bytes_buffer *mlgm_bytes_buffer_write_string(mlgm_bytes_buffer *self, mlgm_string str);

mlgm_bool mlgm_bytes_buffer_has_space(mlgm_bytes_buffer *self, mlgm_size want_size);
mlgm_error mlgm_bytes_buffer_error(mlgm_bytes_buffer *self);
void mlgm_bytes_buffer_release(mlgm_bytes_buffer *self);

////////////////////////////////////////////////////////////////////////////////

mlgm_string_builder *mlgm_string_builder_init(mlgm_string_builder *self);
mlgm_string_builder *mlgm_string_builder_init_with_size(mlgm_string_builder *self, mlgm_size size);
mlgm_string_builder *mlgm_string_builder_init_with_buffer(mlgm_string_builder *self, void *buf, mlgm_size buf_cap);

mlgm_string_builder *mlgm_string_builder_reset(mlgm_string_builder *self);

mlgm_string_builder *mlgm_string_builder_append_string(mlgm_string_builder *self, mlgm_string str);
mlgm_string_builder *mlgm_string_builder_append_uint(mlgm_string_builder *self, mlgm_uint n);
mlgm_string_builder *mlgm_string_builder_append_int(mlgm_string_builder *self, mlgm_int n);
mlgm_string_builder *mlgm_string_builder_append_bool(mlgm_string_builder *self, mlgm_bool b);
mlgm_string_builder *mlgm_string_builder_append_char(mlgm_string_builder *self, mlgm_char n);
mlgm_string_builder *mlgm_string_builder_append_byte(mlgm_string_builder *self, mlgm_byte n);

mlgm_string mlgm_string_builder_string(mlgm_string_builder *self);
mlgm_size mlgm_string_builder_length(mlgm_string_builder *self);
mlgm_error mlgm_string_builder_error(mlgm_string_builder *self);
void mlgm_string_builder_release(mlgm_string_builder *self);

////////////////////////////////////////////////////////////////////////////////

#endif // __mlgm_bytes_h__
