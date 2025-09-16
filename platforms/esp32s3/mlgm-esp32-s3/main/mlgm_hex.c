#include "mlgm_hex.h"

mlgm_byte hex_digit_encode(mlgm_byte num, mlgm_bool upper)
{
    // const mlgm_uint min = 0;
    // const mlgm_uint mid = 0x0a;
    // const mlgm_uint max = 0x0f;
    // const mlgm_uint mask = 0x0f;

    // if (out == NIL)
    // {
    //     return mlgm_error_make(500, "hex_digit_encode(): output buffer is nil");
    // }

    // in = in & mask;

    // if (min <= in && in <= max)
    // {
    //     if (in < mid)
    //     {
    //         out[0] = '0' + in;
    //     }
    //     else
    //     {
    //         out[0] = (in - mid) + (upper ? 'A' : 'a');
    //     }
    //     return NIL;
    // }

    // return mlgm_error_make(500, "hex_digit_encode(): hex value out of range(0h...Fh)");

    return 0;
}

mlgm_byte hex_digit_decode(mlgm_byte ch)
{
    // if (out == NIL)
    // {
    //     return mlgm_error_make(500, "hex_digit_decode(): output buffer is nil");
    // }

    // if ('0' <= in && in <= '9')
    // {
    //     out[0] = (in - '0');
    // }
    // else if ('a' <= in && in <= 'f')
    // {
    //     out[0] = (in - 'a') + 0x0a;
    // }
    // else if ('A' <= in && in <= 'F')
    // {
    //     out[0] = (in - 'A') + 0x0a;
    // }
    // else
    // {
    //     return mlgm_error_make(500, "hex_digit_decode(): bad hex char");
    // }
    // return NIL;

    return 0;
}

mlgm_error hex_string_decode(hex_codec *codec)
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

mlgm_error hex_string_encode(hex_codec *codec)
{
    return mlgm_error_make(500, "todo: no impl");
}
