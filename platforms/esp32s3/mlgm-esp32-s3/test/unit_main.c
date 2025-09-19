
#include <stdio.h>

#include "unit_include.h"
#include "unit_lib.h"

void main(void)
{
    printf("unit_main.c#main(): \n");

    mlgm_unit_list list;
    mlgm_unit_list *plist = &list;
    mlgm_unit_list_init(plist);

    ////////////////////////////////////////////////////////////////////

    mlgm_unit_list_add_fn(plist, "run_case_hex_codec", run_case_hex_codec);
    mlgm_unit_list_add_fn(plist, "run_case_hex_digit_decode", run_case_hex_digit_decode);
    mlgm_unit_list_add_fn(plist, "run_case_hex_digit_encode", run_case_hex_digit_encode);
    mlgm_unit_list_add_fn(plist, "run_case_hex_string_encode", run_case_hex_string_encode);
    mlgm_unit_list_add_fn(plist, "run_case_hex_string_decode", run_case_hex_string_decode);

    mlgm_unit_list_add_fn(plist, "run_case_pktline_codec", run_case_pktline_codec);

    ////////////////////////////////////////////////////////////////////

    mlgm_error err = mlgm_unit_list_run_all(plist);
    if (err)
    {
        mlgm_string msg = mlgm_error_get_message(err);
        mlgm_logger_error(NIL, "unit_main_error: %s", msg);
    }

    mlgm_logger_info(NIL, "done");
}
