
#include "../unit_include.h"

#include "../../main/crypto/sha1.h"

#include <memory.h>

mlgm_error run_case_sha1_sum_from_hex_string(mlgm_unit *unit)
{

    char *str1 = "";
    str1 = "9eddfdd3b2688e1b4cf4bbe70a0d95c406679bf6";
    str1 = "1234567890eddfdd3b26880d9506679bf6abcdef";

    mlgm_sha1_sum sum = mlgm_sha1_sum_from_hex_string(str1);

    mlgm_byte *ss = sum.sum;
    char str_buf[99];

    mlgm_string str2 = mlgm_sha1_sum_to_hex_string(&sum, str_buf, sizeof(str_buf));

    if (strcmp(str1, str2) != 0)
    {
        return mlgm_error_make_with_format(500, "str1 != str2: str1=[%s], str2=[%s]", str1, str2);
    }

    mlgm_logger_info(NIL, "sha1.sum = %s", str2);
    return NIL;
}
