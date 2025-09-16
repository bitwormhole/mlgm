

#ifndef __mlgm_hex_h__
#define __mlgm_hex_h__

#include "mlgm_types.h"
#include "mlgm_errors.h"

typedef struct t_hex_codec
{

    mlgm_byte *src; // in
    mlgm_byte *dst; // out

    mlgm_size src_length;   // in
    mlgm_size dst_length;   // out
    mlgm_size dst_capacity; // in

    mlgm_bool upper; // 用于编码器，指出是否使用大写字母

    mlgm_error error;

} hex_codec;

// 把数字编码为字符
mlgm_byte hex_digit_encode(mlgm_byte num, mlgm_bool upper);

// 把字符解码为数字
mlgm_byte hex_digit_decode(mlgm_byte ch);

// 编码为 hex 字符串
mlgm_error hex_string_encode(hex_codec *codec);

// 解码 hex 字符串
mlgm_error hex_string_decode(hex_codec *codec);

#endif // __mlgm_hex_h__
