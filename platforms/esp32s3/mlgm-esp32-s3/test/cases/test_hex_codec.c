

#include "../unit_include.h"

mlgm_error run_case_hex_codec(mlgm_unit *unit)
{

    hex_string_codec codec;

    hex_string_decode(&codec);

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
