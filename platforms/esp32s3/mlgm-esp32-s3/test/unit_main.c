
#include <stdio.h>

#include "unit_include.h"
#include "unit_lib.h"

void main(void)
{
    printf("unit_main.c#main(): \n");

    mlgm_unit_list list;
    mlgm_unit_list *plist = &list;
    mlgm_unit_list_init(plist);

    mlgm_app_context app_context;
    memset(&app_context, 0, sizeof(app_context));

    ////////////////////////////////////////////////////////////////////

    mlgm_unit_list_add_fn(plist, "run_case_hex_codec", run_case_hex_codec);
    mlgm_unit_list_add_fn(plist, "run_case_hex_digit_decode", run_case_hex_digit_decode);
    mlgm_unit_list_add_fn(plist, "run_case_hex_digit_encode", run_case_hex_digit_encode);
    mlgm_unit_list_add_fn(plist, "run_case_hex_string_encode", run_case_hex_string_encode);
    mlgm_unit_list_add_fn(plist, "run_case_hex_string_decode", run_case_hex_string_decode);

    mlgm_unit_list_add_fn(plist, "run_case_pktline_codec", run_case_pktline_codec);
    mlgm_unit_list_add_fn(plist, "run_case_pktline_encode", run_case_pktline_encode);
    mlgm_unit_list_add_fn(plist, "run_case_pktline_decode", run_case_pktline_decode);

    mlgm_unit_list_add_fn(plist, "run_case_sha1_sum_from_hex_string", run_case_sha1_sum_from_hex_string);
    mlgm_unit_list_add_fn(plist, "run_case_defer", run_case_defer);

    mlgm_unit_list_add_fn(plist, "run_case_strings_builder_pool", run_case_strings_builder_pool);
    mlgm_unit_list_add_fn(plist, "run_case_strings_test_string_slice", run_case_strings_test_string_slice);

    ////////////////////////////////////////////////////////////////////

    mlgm_error err = mlgm_unit_list_run_all(plist, &app_context);
    if (err)
    {
        mlgm_string msg = mlgm_error_get_message(err);
        mlgm_logger_error(NIL, "unit_main_error: %s", msg);
    }

    mlgm_logger_info(NIL, "done");
}
