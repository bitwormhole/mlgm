#include "mlgm_hex.h"

#include <memory.h>

mlgm_char hex_digit_encode(mlgm_byte num, mlgm_bool upper)
{
    num = num & 0x0f;
    if (num < 0x0a)
    {
        return ('0' + num);
    }
    else
    {
        return (num - 0x0a) + (upper ? 'A' : 'a');
    }
}

mlgm_byte hex_digit_decode(mlgm_char ch)
{
    if ('0' <= ch && ch <= '9')
    {
        return (ch - '0');
    }
    else if ('a' <= ch && ch <= 'f')
    {
        return (ch - 'a') + 0x0a;
    }
    else if ('A' <= ch && ch <= 'F')
    {
        return (ch - 'A') + 0x0a;
    }
    return 0;
}

mlgm_error hex_string_decode(hex_string_codec *codec)
{

    // mlgm_uint value = 0;
    // for (int i = 0; i < src_len; i++)
    // {

    //     mlgm_byte b = src_data[i];
    //     mlgm_uint di = 0;

    //     mlgm_error err = hex_digit_decode(b, di);
    //     if (err)
    //     {
    //         return err;
    //     }
    //     value = () | ();
    // }
    // return NIL;

    return mlgm_error_make(500, "todo: no impl");
}

mlgm_error hex_string_encode(hex_string_codec *codec)
{

    mlgm_size i;
    mlgm_bool upper = codec->upper;
    mlgm_byte *src = codec->binary;
    mlgm_size src_len = codec->binary_length;
    mlgm_char *dst = codec->string;
    mlgm_size dst_cap = codec->string_capacity;

    for (i = 0; i < src_len; i++)
    {
        mlgm_byte b = src[i];
        mlgm_char ch0 = hex_digit_encode(0x0f & (b >> 4), upper);
        mlgm_char ch1 = hex_digit_encode(0x0f & b, upper);
    }

    return mlgm_error_make(500, "todo: no impl");
}

mlgm_error hex_string_prepare_encode(hex_string_codec *codec, mlgm_byte *src, mlgm_size src_len, mlgm_char *dst, mlgm_size dst_cap)
{
    if (codec == NIL || src == NIL || dst == NIL)
    {
        return mlgm_error_make(500, "hex_string_prepare_encode: param(s) is nil");
    }
    memset(codec, 0, sizeof(codec[0]));

    codec->string = dst;
    codec->string_capacity = dst_cap;

    codec->binary = src;
    codec->binary_length = src_len;

    return NIL;
}

mlgm_error hex_string_prepare_decode(hex_string_codec *codec, mlgm_string src, mlgm_size src_len, mlgm_byte *dst, mlgm_size dst_cap)
{
    if (codec == NIL || src == NIL || dst == NIL)
    {
        return mlgm_error_make(500, "hex_string_prepare_decode: param(s) is nil");
    }
    memset(codec, 0, sizeof(codec[0]));

    codec->string = (void *)src;
    codec->string_length = src_len;

    codec->binary = dst;
    codec->binary_capacity = dst_cap;

    return NIL;
}
