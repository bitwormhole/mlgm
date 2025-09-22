#include "mlgm_hex.h"

#include "mlgm_bytes.h"

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

mlgm_error hex_string_decoder_decode(hex_string_decoder *codec)
{
    int src_len = codec->string_length;
    const char *const src_data = codec->string;
    mlgm_uint hh, hl, b;
    mlgm_bytes_buffer buffer;

    if ((src_len < 1) && (src_data))
    {
        src_len = strlen(src_data);
    }

    mlgm_bytes_buffer_init_with_buffer(&buffer, codec->binary, codec->binary_capacity);
    hh = hl = 0;

    for (int i = 0; i < src_len; i++)
    {
        char ch = src_data[i];
        mlgm_uint hex = hex_digit_decode(ch);
        if (i & 0x01)
        {
            hl = hex;
            b = ((hh << 4) & 0xf0) | (hl & 0x0f);
            mlgm_bytes_buffer_write_byte(&buffer, b);
        }
        else
        {
            hh = hex;
        }
    }

    mlgm_error err = mlgm_bytes_buffer_error(&buffer);
    if (err)
    {
        return err;
    }
    codec->binary_length = buffer.length;
    return NIL;
}

mlgm_error hex_string_encoder_encode(hex_string_encoder *codec)
{
    mlgm_size i;
    mlgm_string_builder builder;

    mlgm_bool upper = codec->upper;
    mlgm_byte *src = codec->binary;
    mlgm_size src_len = codec->binary_length;
    mlgm_char *dst = codec->string;
    mlgm_size dst_cap = codec->string_capacity;

    mlgm_string_builder_init_with_buffer(&builder, dst, dst_cap);

    for (i = 0; i < src_len; i++)
    {
        mlgm_byte b = src[i];
        mlgm_char ch0 = hex_digit_encode(0x0f & (b >> 4), upper);
        mlgm_char ch1 = hex_digit_encode(0x0f & b, upper);
        mlgm_string_builder_append_char(&builder, ch0);
        mlgm_string_builder_append_char(&builder, ch1);
    }

    mlgm_string str = mlgm_string_builder_string(&builder);
    codec->string_length = strlen(str);

    return mlgm_string_builder_error(&builder);
}

mlgm_error hex_string_encoder_prepare(hex_string_encoder *codec, mlgm_byte *src, mlgm_size src_len, mlgm_char *dst, mlgm_size dst_cap)
{
    if (codec == NIL || src == NIL || dst == NIL)
    {
        return mlgm_error_make(500, "hex_string_encoder_prepare: param(s) is nil");
    }
    memset(codec, 0, sizeof(codec[0]));

    codec->string = dst;
    codec->string_capacity = dst_cap;

    codec->binary = src;
    codec->binary_length = src_len;

    return NIL;
}

mlgm_error hex_string_decoder_prepare(hex_string_decoder *codec, mlgm_string src, mlgm_size src_len, mlgm_byte *dst, mlgm_size dst_cap)
{
    if (codec == NIL || src == NIL || dst == NIL)
    {
        return mlgm_error_make(500, "hex_string_decoder_prepare: param(s) is nil");
    }
    memset(codec, 0, sizeof(codec[0]));

    if (src_len < 1)
    {
        src_len = strlen(src);
    }

    codec->string = (void *)src;
    codec->string_length = src_len;

    codec->binary = dst;
    codec->binary_capacity = dst_cap;

    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_error mlgm_hex_to_string(void *src, mlgm_size src_len, void *dst, mlgm_size dst_cap)
{
    hex_string_encoder encoder;
    hex_string_encoder_prepare(&encoder, src, src_len, dst, dst_cap);
    return hex_string_encoder_encode(&encoder);
}

mlgm_error mlgm_hex_parse_string(mlgm_string src, mlgm_size src_len, void *dst, mlgm_size dst_cap)
{
    hex_string_decoder decoder;
    hex_string_decoder_prepare(&decoder, src, src_len, dst, dst_cap);
    return hex_string_decoder_decode(&decoder);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
