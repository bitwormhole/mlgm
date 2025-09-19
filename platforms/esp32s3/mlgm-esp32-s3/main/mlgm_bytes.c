#include "mlgm_bytes.h"

// #include "mlgm_logger.h"
// #include "mlgm_errors.h"

#include <memory.h>

////////////////////////////////////////////////////////////////////////////////
// struct:mlgm_bytes_buffer_entity

mlgm_bytes_buffer_entity *mlgm_bytes_buffer_entity_make(mlgm_size size)
{
    mlgm_size size1 = sizeof(mlgm_bytes_buffer_entity);
    mlgm_size size2 = (size > 0) ? size : 0;
    mlgm_size size3 = size1 + size2;

    void *block = malloc(size3);
    mlgm_bytes_buffer_entity *entity = block;

    if (entity)
    {
        memset(block, 0, size3);
        entity->self = block;
        entity->body_size = size2;
        entity->total_size = size3;
    }
    return entity;
}

void mlgm_bytes_buffer_entity_release(mlgm_bytes_buffer_entity *self)
{
    if (self)
    {
        void *block = self->self;
        if (self == block)
        {
            memset(block, 0, sizeof(mlgm_bytes_buffer_entity));
            free(block);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// struct:mlgm_bytes_buffer

mlgm_bytes_buffer *mlgm_bytes_buffer_init(mlgm_bytes_buffer *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
    }
    return self;
}

mlgm_bytes_buffer *mlgm_bytes_buffer_init_with_size(mlgm_bytes_buffer *self, mlgm_size size)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        mlgm_bytes_buffer_entity *entity = mlgm_bytes_buffer_entity_make(size);
        if (entity)
        {
            self->entity = entity;
            self->data = entity->body;
            self->capacity = entity->body_size;
            self->length = 0;
        }
    }
    return self;
}

mlgm_bytes_buffer *mlgm_bytes_buffer_init_with_buffer(mlgm_bytes_buffer *self, void *buffer, mlgm_size cap)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        self->data = buffer;
        self->capacity = cap;
        self->length = 0;
    }
    return self;
}

mlgm_bytes_buffer *mlgm_bytes_buffer_reset(mlgm_bytes_buffer *self)
{
    if (self)
    {
        self->overflow = NO;
        self->length = 0;
    }
    return self;
}

mlgm_bool mlgm_bytes_buffer_has_space(mlgm_bytes_buffer *self, mlgm_size want_size)
{
    if (self)
    {
        mlgm_size cap = self->capacity;
        mlgm_size len = self->length;
        mlgm_byte *data = self->data;
        if (data)
        {
            if (len + want_size < cap)
            {
                return YES;
            }
        }
    }
    return NO;
}

mlgm_bytes_buffer *mlgm_bytes_buffer_write(mlgm_bytes_buffer *self, mlgm_byte *src, mlgm_size src_len)
{
    if (mlgm_bytes_buffer_has_space(self, src_len))
    {
        mlgm_byte *dst = self->data + self->length;
        memcpy(dst, src, src_len);
        self->length += src_len;
        return self;
    }
    if (self)
    {
        self->overflow = YES;
    }
    return NIL;
}

mlgm_bytes_buffer *mlgm_bytes_buffer_write_byte(mlgm_bytes_buffer *self, mlgm_byte b)
{
    const mlgm_size want_len = 1;
    if (mlgm_bytes_buffer_has_space(self, want_len))
    {
        mlgm_byte *dst = self->data + self->length;
        dst[0] = b;
        self->length++;
        return self;
    }
    if (self)
    {
        self->overflow = YES;
    }
    return NIL;
}

mlgm_bytes_buffer *mlgm_bytes_buffer_write_string(mlgm_bytes_buffer *self, mlgm_string str)
{
    if (self == NIL || str == NIL)
    {
        return NIL;
    }
    const mlgm_size str_len = strlen(str);
    if (mlgm_bytes_buffer_has_space(self, str_len))
    {
        mlgm_byte *dst = self->data + self->length;
        memcpy(dst, str, str_len);
        self->length += str_len;
        return self;
    }
    if (self)
    {
        self->overflow = YES;
    }
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////
// struct:mlgm_string_builder

mlgm_string_builder *mlgm_string_builder_init(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *bb = &self->buffer;
        mlgm_bytes_buffer_init(bb);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_init_with_size(mlgm_string_builder *self, mlgm_size size)
{
    if (self)
    {
        mlgm_bytes_buffer *bb = &self->buffer;
        mlgm_bytes_buffer_init_with_size(bb, size);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_init_with_buffer(mlgm_string_builder *self, void *buf, mlgm_size buf_cap)
{
    if (self)
    {
        mlgm_bytes_buffer *bb = &self->buffer;
        mlgm_bytes_buffer_init_with_buffer(bb, buf, buf_cap);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_reset(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *buffer = &self->buffer;
        mlgm_bytes_buffer_reset(buffer);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_append_string(mlgm_string_builder *self, mlgm_string str) {}

mlgm_string_builder *mlgm_string_builder_append_uint(mlgm_string_builder *self, mlgm_uint n) {}

mlgm_string_builder *mlgm_string_builder_append_int(mlgm_string_builder *self, mlgm_int n) {}

mlgm_string_builder *mlgm_string_builder_append_bool(mlgm_string_builder *self, mlgm_bool b) {}

mlgm_string_builder *mlgm_string_builder_append_char(mlgm_string_builder *self, mlgm_char n) {}

mlgm_string_builder *mlgm_string_builder_append_byte(mlgm_string_builder *self, mlgm_byte n) {}

mlgm_string mlgm_string_builder_string(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *buf = &self->buffer;
        mlgm_byte *data = buf->data;
        mlgm_size len = buf->length;
        mlgm_size cap = buf->capacity;
        if ((data) && (0 <= len) && (len < cap))
        {
            data[len] = 0;
        }
        return data;
    }
    return NIL;
}

mlgm_size mlgm_string_builder_length(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *buffer = &self->buffer;
        return buffer->length;
    }
    return 0;
}

mlgm_error mlgm_string_builder_error(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *buffer = &self->buffer;
        return mlgm_bytes_buffer_error(buffer);
    }
    return NIL;
}

void mlgm_string_builder_release(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *buffer = &self->buffer;
        mlgm_bytes_buffer_release(buffer);
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
