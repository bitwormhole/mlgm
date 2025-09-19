

#ifndef __mlgm_hex_h__
#define __mlgm_hex_h__

#include "mlgm_types.h"
#include "mlgm_errors.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct t_hex_string_codec
{
    // binary
    mlgm_byte *binary;
    mlgm_size binary_length;
    mlgm_size binary_capacity;

    // string
    mlgm_char *string;
    mlgm_size string_length;
    mlgm_size string_capacity;

    // other
    mlgm_bool upper; // 用于编码器，指出是否使用大写字母
    mlgm_error error;

} hex_string_codec;

////////////////////////////////////////////////////////////////////////////////

// 把数字编码为字符
mlgm_char hex_digit_encode(mlgm_byte num, mlgm_bool upper);

// 把字符解码为数字
mlgm_byte hex_digit_decode(mlgm_char ch);

// 编码为 hex 字符串
mlgm_error hex_string_encode(hex_string_codec *codec);

mlgm_error hex_string_prepare_encode(hex_string_codec *codec, mlgm_byte *src, mlgm_size src_len, mlgm_char *dst, mlgm_size dst_cap);

// 解码 hex 字符串
mlgm_error hex_string_decode(hex_string_codec *codec);

mlgm_error hex_string_prepare_decode(hex_string_codec *codec, mlgm_string src, mlgm_size src_len, mlgm_byte *dst, mlgm_size dst_cap);

////////////////////////////////////////////////////////////////////////////////

#endif // __mlgm_hex_h__
