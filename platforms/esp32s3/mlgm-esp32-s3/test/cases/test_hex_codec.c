

#include "../unit_include.h"

#include <memory.h>

mlgm_error run_case_hex_codec(mlgm_unit *unit)
{
    const int buffer_size = 256;

    char buffer1[buffer_size];           // bin
    char buffer2[(buffer_size * 2) + 5]; // string
    char buffer3[buffer_size];           // bin

    for (int i = 0; i < buffer_size; ++i)
    {
        buffer1[i] = (211 - i) & 0xff;
    }

    hex_string_encoder encoder;
    hex_string_decoder decoder;
    mlgm_error err = NIL;

    // encode (1=>2)
    hex_string_encoder_prepare(&encoder, buffer1, buffer_size, buffer2, sizeof(buffer2));
    err = hex_string_encoder_encode(&encoder);
    if (err)
    {
        return err;
    }

    // encode (2=>3)
    hex_string_decoder_prepare(&decoder, buffer2, 0, buffer3, sizeof(buffer3));
    err = hex_string_decoder_decode(&decoder);
    if (err)
    {
        return err;
    }

    if (memcmp(buffer1, buffer3, buffer_size) != 0)
    {
        return mlgm_error_make(500, "run_case_hex_codec: data(buffer1) != data(buffer3)");
    }
    return NIL;
}

mlgm_error run_case_hex_digit_encode(mlgm_unit *unit)
{
    const mlgm_byte max = 20;
    mlgm_byte num = 0;

    for (; num < max; num++)
    {
        mlgm_char ch1 = hex_digit_encode(num, YES);
        mlgm_char ch2 = hex_digit_encode(num, NO);
        mlgm_logger_info(NIL, "hex_digit_encode(%d) : (ch1='%c', ch2='%c')", num, ch1, ch2);
    }

    return NIL;
}

mlgm_error run_case_hex_digit_decode(mlgm_unit *unit)
{
    mlgm_string clist = ".0123456789abcdef....0123456789ABCDEF..";
    for (int i = 0;; i++)
    {
        mlgm_char ch = clist[i];
        if (ch == 0)
        {
            break;
        }
        mlgm_byte num = hex_digit_decode(ch);
        mlgm_logger_info(NIL, "hex_digit_decode[%d] ('%c') : %d", i, ch, num);
    }
    return NIL;
}

mlgm_error run_case_hex_string_encode(mlgm_unit *unit)
{
    mlgm_byte src[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xab, 0xcd, 0xef};
    char dst[256];
    hex_string_encoder encoder;

    mlgm_error err = hex_string_encoder_prepare(&encoder, src, sizeof(src), dst, sizeof(dst));
    if (err)
    {
        return err;
    }

    err = hex_string_encoder_encode(&encoder);
    if (err)
    {
        return err;
    }

    // log
    int src_len = sizeof(src);
    for (int i = 0; i < src_len; i++)
    {
        mlgm_byte b = src[i];
        mlgm_logger_info(NIL, "  src.bytes[%d] = %xH", i, b);
    }
    mlgm_string dst_str = dst;
    mlgm_logger_info(NIL, "dst.string = %s", dst_str);

    return NIL;
}

mlgm_error run_case_hex_string_decode(mlgm_unit *unit)
{

    mlgm_string src = "abcd0123456789ef";
    mlgm_byte dst[256];
    hex_string_decoder decoder;

    hex_string_decoder_prepare(&decoder, src, 0, dst, sizeof(dst));

    mlgm_error err = hex_string_decoder_decode(&decoder);
    if (err)
    {
        return err;
    }

    mlgm_logger_info(NIL, "  src.string = %s", src);

    int cb = decoder.binary_length;
    for (int i = 0; i < cb; i++)
    {
        mlgm_byte b = dst[i];
        mlgm_logger_info(NIL, "  dst.bin[%d] = %xH", i, b);
    }

    return NIL;
}
