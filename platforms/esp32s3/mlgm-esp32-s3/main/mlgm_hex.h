

#ifndef __mlgm_hex_h__
#define __mlgm_hex_h__

#include "mlgm_types.h"
#include "mlgm_errors.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct t_hex_string_encoder
{
    // binary (src)

    mlgm_byte *binary;       // in
    mlgm_size binary_length; // in

    // string (dst)

    mlgm_char *string;         // io
    mlgm_size string_length;   // out
    mlgm_size string_capacity; // in

    // other
    mlgm_bool upper; // 用于编码器，指出是否使用大写字母
    mlgm_error error;

} hex_string_encoder;

typedef struct t_hex_string_decoder
{
    // binary (dst)

    mlgm_byte *binary;         // io
    mlgm_size binary_length;   // io
    mlgm_size binary_capacity; // in

    // string (src)

    mlgm_string string;      // in
    mlgm_size string_length; // in

    // other
    // mlgm_bool upper; // 用于编码器，指出是否使用大写字母
    mlgm_error error;

} hex_string_decoder;

////////////////////////////////////////////////////////////////////////////////

// 把数字编码为字符
mlgm_char hex_digit_encode(mlgm_byte num, mlgm_bool upper);

// 把字符解码为数字
mlgm_byte hex_digit_decode(mlgm_char ch);

// 编码为 hex 字符串
mlgm_error hex_string_encoder_encode(hex_string_encoder *codec);
mlgm_error hex_string_encoder_prepare(hex_string_encoder *codec, mlgm_byte *src, mlgm_size src_len, mlgm_char *dst, mlgm_size dst_cap);

// 解码 hex 字符串
mlgm_error hex_string_decoder_decode(hex_string_decoder *codec);
mlgm_error hex_string_decoder_prepare(hex_string_decoder *codec, mlgm_string src, mlgm_size src_len, mlgm_byte *dst, mlgm_size dst_cap);

////////////////////////////////////////////////////////////////////////////////

#endif // __mlgm_hex_h__
