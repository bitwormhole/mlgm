#ifndef __mlgm_pktline_h__
#define __mlgm_pktline_h__

#include "mlgm_types.h"
#include "mlgm_errors.h"

typedef struct t_mlgm_pktline_size
{

    mlgm_byte raw[4];

} mlgm_pktline_size;

typedef struct t_mlgm_pktline_head
{

    mlgm_string text;
    mlgm_size length;

} mlgm_pktline_head;

typedef struct t_mlgm_pktline_body
{

    mlgm_byte *data;
    mlgm_size length;

} mlgm_pktline_body;

typedef struct t_mlgm_pktline_pack
{

    mlgm_size total; // the pack total size (decoded)

    mlgm_pktline_size size; // the pack total size (encoded)
    mlgm_pktline_head head;
    mlgm_pktline_body body;

} mlgm_pktline_pack;

////////////////////////////////////////////////////////////////////////////////

// mlgm_pktline_buffer 是缓冲区的抽象接口
typedef struct t_mlgm_pktline_buffer
{
    mlgm_pktline_pack pack;

    mlgm_byte *raw_buffer_data;
    mlgm_size raw_buffer_capacity;

} mlgm_pktline_buffer;

// 以下是各种容量的缓冲区实体

// mlgm_pktline_buffer_4k 是容量为 4k 的缓冲区实体
typedef struct t_mlgm_pktline_buffer_4k
{
    mlgm_pktline_buffer buffer;
    mlgm_byte raw[4 * 1024];

} mlgm_pktline_buffer_4k;

// mlgm_pktline_buffer_16k 是容量为 16k 的缓冲区实体
typedef struct t_mlgm_pktline_buffer_16k
{
    mlgm_pktline_buffer buffer;
    mlgm_byte raw[16 * 1024];

} mlgm_pktline_buffer_16k;

// mlgm_pktline_buffer_64k 是容量为 64k 的缓冲区实体
typedef struct t_mlgm_pktline_buffer_64k
{
    mlgm_pktline_buffer buffer;
    mlgm_byte raw[64 * 1024];

} mlgm_pktline_buffer_64k;

////////////////////////////////////////////////////////////////////////////////
// codec

typedef struct t_mlgm_pktline_encoder
{

    // src

    mlgm_pktline_pack *pack; // in

    // dst

    mlgm_byte *data;                // io
    mlgm_size data_length;          // out
    mlgm_size data_buffer_capacity; // in

    // options

    mlgm_pktline_buffer *buffer;

} mlgm_pktline_encoder;

typedef struct t_mlgm_pktline_decoder
{

    // src

    mlgm_byte *data;       // in
    mlgm_size data_length; // in

    // dst

    mlgm_pktline_pack *pack; // out

    // options

    mlgm_pktline_buffer *buffer;

} mlgm_pktline_decoder;

////////////////////////////////////////////////////////////////////////////////

// mlgm_pktline_size

mlgm_size mlgm_pktline_size_get(mlgm_pktline_size *self);
void mlgm_pktline_size_set(mlgm_pktline_size *self, mlgm_size size);

// mlgm_pktline_encoder

mlgm_error mlgm_pktline_encoder_init(mlgm_pktline_encoder *self, mlgm_pktline_buffer *buffer);
mlgm_error mlgm_pktline_encoder_encode(mlgm_pktline_encoder *self);

// mlgm_pktline_decoder

mlgm_error mlgm_pktline_decoder_init(mlgm_pktline_decoder *self, mlgm_pktline_buffer *buffer);
mlgm_error mlgm_pktline_decoder_decode(mlgm_pktline_decoder *self);

// mlgm_pktline_buffer

mlgm_pktline_buffer *mlgm_pktline_buffer_init(mlgm_pktline_buffer *self, mlgm_byte *raw, mlgm_size raw_size);
mlgm_error mlgm_pktline_buffer_encode(mlgm_pktline_buffer *self);
mlgm_error mlgm_pktline_buffer_decode(mlgm_pktline_buffer *self);

// buffer (4k)
mlgm_pktline_buffer_4k *mlgm_pktline_buffer_4k_init(mlgm_pktline_buffer_4k *self);
mlgm_pktline_buffer *mlgm_pktline_buffer_4k_to_buffer(mlgm_pktline_buffer_4k *self);

// buffer (16k)
mlgm_pktline_buffer_16k *mlgm_pktline_buffer_16k_init(mlgm_pktline_buffer_16k *self);
mlgm_pktline_buffer *mlgm_pktline_buffer_16k_to_buffer(mlgm_pktline_buffer_16k *self);

// buffer (64k)
mlgm_pktline_buffer_64k *mlgm_pktline_buffer_64k_init(mlgm_pktline_buffer_64k *self);
mlgm_pktline_buffer *mlgm_pktline_buffer_64k_to_buffer(mlgm_pktline_buffer_64k *self);

#endif // __mlgm_pktline_h__
