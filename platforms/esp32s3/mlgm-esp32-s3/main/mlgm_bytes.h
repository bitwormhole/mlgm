
#ifndef __mlgm_bytes_h__
#define __mlgm_bytes_h__

#include "mlgm_types.h"

typedef struct t_mlgm_bytes_buffer
{
    mlgm_size capacity;
    mlgm_size length;
    mlgm_bool overflow;

    mlgm_byte *data;

} mlgm_bytes_buffer;

////////////////////////////////////////////////////////////////////////////////

mlgm_bytes_buffer *mlgm_bytes_buffer_init(mlgm_bytes_buffer *self, mlgm_byte *buffer, mlgm_size cap);
mlgm_bytes_buffer *mlgm_bytes_buffer_reset(mlgm_bytes_buffer *self);

mlgm_bytes_buffer *mlgm_bytes_buffer_write(mlgm_bytes_buffer *self, mlgm_byte *src, mlgm_size src_len);
mlgm_bytes_buffer *mlgm_bytes_buffer_write_byte(mlgm_bytes_buffer *self, mlgm_byte b);
mlgm_bytes_buffer *mlgm_bytes_buffer_write_string(mlgm_bytes_buffer *self, mlgm_string str);

mlgm_bool mlgm_bytes_buffer_has_space(mlgm_bytes_buffer *self, mlgm_size want_size);

////////////////////////////////////////////////////////////////////////////////

#endif // __mlgm_bytes_h__
