#include "mlgm_bytes.h"

// #include "mlgm_logger.h"
// #include "mlgm_errors.h"

#include <memory.h>

////////////////////////////////////////////////////////////////////////////////

mlgm_bytes_buffer *mlgm_bytes_buffer_init(mlgm_bytes_buffer *self, mlgm_byte *buffer, mlgm_size cap)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        self->data = buffer;
        self->capacity = cap;
        return self;
    }
    return NIL;
}

mlgm_bytes_buffer *mlgm_bytes_buffer_reset(mlgm_bytes_buffer *self)
{
    if (self)
    {
        self->overflow = NO;
        self->length = 0;
        return self;
    }
    return NIL;
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
// EOF
