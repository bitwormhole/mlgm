#include "mlgm_pktline.h"

#include "mlgm_logger.h"

#include <memory.h>

////////////////////////////////////////////////////////////////////////////////
// mlgm_pktline_size

mlgm_size mlgm_pktline_size_get(mlgm_pktline_size *self)
{
    if (!self)
    {
        return 0;
    }

    mlgm_size size = 0;
    mlgm_size src_len = sizeof(self->raw);
    // mlgm_byte *src = self->raw;

    for (int i = 0; i < src_len; i++)
    {
        // mlgm_byte b = src[i];

        // todo ...
    }

    return size;
}

void mlgm_pktline_size_set(mlgm_pktline_size *self, mlgm_size size)
{
}

////////////////////////////////////////////////////////////////////////////////
// mlgm_pktline_buffer

mlgm_pktline_buffer *mlgm_pktline_buffer_init(mlgm_pktline_buffer *self, mlgm_byte *raw, mlgm_size raw_size)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        self->raw_buffer_data = raw;
        self->raw_buffer_capacity = raw_size;
    }
    return NIL;
}

mlgm_error mlgm_pktline_buffer_encode(mlgm_pktline_buffer *self)
{
    // todo ...
    return mlgm_error_make(500, "todo: no impl");
}

mlgm_error mlgm_pktline_buffer_decode(mlgm_pktline_buffer *self)
{
    // todo ...
    return mlgm_error_make(500, "todo: no impl");
}

////////////////////////////////////////////////////////////////////////////////

// buffer (4k)
mlgm_pktline_buffer_4k *mlgm_pktline_buffer_4k_init(mlgm_pktline_buffer_4k *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        mlgm_pktline_buffer *buf = &self->buffer;
        mlgm_byte *raw = self->raw;
        mlgm_size size = sizeof(self->raw);
        mlgm_pktline_buffer_init(buf, raw, size);
        return self;
    }
    return NIL;
}

// buffer (16k)
mlgm_pktline_buffer_16k *mlgm_pktline_buffer_16k_init(mlgm_pktline_buffer_16k *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        mlgm_pktline_buffer *buf = &self->buffer;
        mlgm_byte *raw = self->raw;
        mlgm_size size = sizeof(self->raw);
        mlgm_pktline_buffer_init(buf, raw, size);
        return self;
    }
    return NIL;
}

// buffer (64k)
mlgm_pktline_buffer_64k *mlgm_pktline_buffer_64k_init(mlgm_pktline_buffer_64k *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        mlgm_pktline_buffer *buf = &self->buffer;
        mlgm_byte *raw = self->raw;
        mlgm_size size = sizeof(self->raw);
        mlgm_pktline_buffer_init(buf, raw, size);
        return self;
    }
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
