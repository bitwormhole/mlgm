

#include "../unit_include.h"

#include "../../main/mlgm_strings.h"
#include "../../main/mlgm_defer.h"

#include <memory.h>

mlgm_error run_case_strings_builder_pool(mlgm_unit *unit)
{

    mlgm_logger_debug(NIL, "todo...");

    mlgm_defer_manager dm;
    mlgm_string_builder_holder sbh1;
    mlgm_string_builder_holder sbh2;

    const int sbh_n_count = 5;
    mlgm_string_builder_holder sbh_n[sbh_n_count];

    mlgm_defer_manager_init(&dm);

    mlgm_string_builder_holder_init(&sbh1, 2333);
    mlgm_string_builder_holder_auto_release(&sbh1, &dm);

    mlgm_string_builder_holder_init(&sbh2, 567);
    mlgm_string_builder_holder_auto_release(&sbh2, &dm);

    for (int j = 0; j < sbh_n_count; j++)
    {
        mlgm_string_builder_holder *holder = sbh_n + j;
        mlgm_string_builder_holder_init(holder, 64);
        mlgm_string_builder_holder_auto_release(holder, &dm);
    }

    for (int i = 0; i < 5; i++)
    {

        mlgm_string_builder *builder1 = sbh1.builder;
        mlgm_string_builder *builder2 = sbh2.builder;

        if (builder1 && builder2)
        {
            // mlgm_string_builder_reset(builder1);
            mlgm_string_builder_append_int(builder1, i);

            // mlgm_string_builder_reset(builder2);
            mlgm_string_builder_append_char(builder2, '/');
            mlgm_string_builder_append_string(builder2, "part");
            mlgm_string_builder_append_int(builder2, i);

            mlgm_string str1 = mlgm_string_builder_string(builder1);
            mlgm_string str2 = mlgm_string_builder_string(builder2);

            mlgm_logger_info(NIL, "str1 = [%s]", str1);
            mlgm_logger_info(NIL, "str2 = [%s]", str2);
        }
    }

    // build string:

    const char nl = '\n';
    mlgm_string str = "";
    mlgm_string_builder *builder = sbh1.builder;
    mlgm_string_builder_reset(builder);

    // for (bool)

    mlgm_string_builder_append_char(builder, nl);
    mlgm_string_builder_append_string(builder, "bool(Y):");
    mlgm_string_builder_append_bool(builder, YES);
    mlgm_string_builder_append_char(builder, nl);
    mlgm_string_builder_append_string(builder, "bool(N):");
    mlgm_string_builder_append_bool(builder, NO);
    mlgm_string_builder_append_char(builder, nl);

    str = mlgm_string_builder_string(builder);
    mlgm_logger_info(NIL, "mlgm_string_builder: \n %s", str);

    // for (uint)
    mlgm_string_builder_reset(builder);
    for (mlgm_uint i1 = 0; i1 < 8; i1++)
    {
        mlgm_string_builder_append_string(builder, "sb.append_uint: ");
        mlgm_string_builder_append_uint(builder, i1);
        mlgm_string_builder_append_char(builder, nl);
    }
    str = mlgm_string_builder_string(builder);
    mlgm_logger_info(NIL, "mlgm_string_builder: \n %s", str);

    // for (int)
    mlgm_string_builder_reset(builder);
    for (mlgm_int i2 = -5; i2 < 5; i2++)
    {
        mlgm_string_builder_append_string(builder, "sb.append_int: ");
        mlgm_string_builder_append_int(builder, i2);
        mlgm_string_builder_append_byte(builder, nl);
    }
    str = mlgm_string_builder_string(builder);
    mlgm_logger_info(NIL, "mlgm_string_builder: \n %s", str);

    // done

    mlgm_error err = mlgm_string_builder_error(builder);
    if (err)
    {
        mlgm_string msg = mlgm_error_get_message(err);
        mlgm_logger_warn(NIL, "run_case_strings_builder_pool: %s", msg);
    }

    mlgm_defer_manager_execute(&dm);
    return NIL;
}

mlgm_error run_case_strings_test_string_slice(mlgm_unit *unit)
{

    const mlgm_string full_str = "hello, how are you?";

    mlgm_string_slice sli_1;
    mlgm_string_slice_init_with_string(&sli_1, full_str);
    mlgm_string fmt;

    const mlgm_string str_prefix_1 = "hello";
    const mlgm_string str_prefix_2 = "helle";
    const mlgm_string str_suffix_1 = "you?";
    const mlgm_string str_suffix_2 = "you";

    mlgm_bool b_has_prefix_1 = mlgm_string_slice_has_prefix(&sli_1, str_prefix_1);
    mlgm_bool b_has_prefix_2 = mlgm_string_slice_has_prefix(&sli_1, str_prefix_2);
    mlgm_bool b_has_suffix_1 = mlgm_string_slice_has_suffix(&sli_1, str_suffix_1);
    mlgm_bool b_has_suffix_2 = mlgm_string_slice_has_suffix(&sli_1, str_suffix_2);

    fmt = "[mlgm_string_slice_has_prefix slice:'%s' prefix:'%s' return:'%d']";
    mlgm_logger_debug(NIL, fmt, full_str, str_prefix_1, b_has_prefix_1);
    mlgm_logger_debug(NIL, fmt, full_str, str_prefix_2, b_has_prefix_2);

    fmt = "[mlgm_string_slice_has_suffix slice:'%s' suffix:'%s' return:'%d']";
    mlgm_logger_debug(NIL, fmt, full_str, str_suffix_1, b_has_suffix_1);
    mlgm_logger_debug(NIL, fmt, full_str, str_suffix_2, b_has_suffix_2);

    return NIL;
}
