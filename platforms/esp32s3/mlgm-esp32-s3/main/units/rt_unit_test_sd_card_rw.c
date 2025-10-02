
#include "units.h"

#include "../module_sd_card.h"
#include "../mlgm_logger.h"
#include "../mlgm_app.h"
#include "../mlgm_strings.h"
#include "../mlgm_files.h"

#include <memory.h>

mlgm_error rt_unit_test_sd_card_rw(mlgm_unit *unit)
{

    mlgm_defer_manager dm;
    mlgm_string_builder_holder buffer_w;
    mlgm_string_builder_holder buffer_r;
    mlgm_string_builder_holder buffer4path;
    mlgm_file_reader reader;
    mlgm_file_writer writer;
    mlgm_error err;

    char mock_data[] = "mock_data_of(rt_unit_test_sd_card_rw)";
    mlgm_string path1 = "/.mlgm/test/a/b/cdefg.txt";
    mlgm_app_context *app_ctx = unit->context;
    sd_card_module *sd = app_ctx->sd;

    // init

    mlgm_defer_manager_init(&dm);
    mlgm_string_builder_holder_init(&buffer_r, 1024);
    mlgm_string_builder_holder_init(&buffer_w, 1024);
    mlgm_string_builder_holder_init(&buffer4path, 1024);

    mlgm_string_builder_holder_auto_release(&buffer_r, &dm);
    mlgm_string_builder_holder_auto_release(&buffer_w, &dm);
    mlgm_string_builder_holder_auto_release(&buffer4path, &dm);

    // prepare path
    mlgm_path sd_path;
    err = sd_card_module_get_mount_path(sd, &sd_path);
    if (err)
    {
        mlgm_defer_manager_execute(&dm);
        return err;
    }

    mlgm_path target_path;

    err = mlgm_path_get_child(&sd_path, path1, &target_path);
    if (err)
    {
        mlgm_defer_manager_execute(&dm);
        return err;
    }

    mlgm_string path2 = target_path.string;

    // init r/w

    mlgm_file_reader_init(&reader, path2);
    mlgm_file_writer_init(&writer, path2);

    // prepare data

    mlgm_bytes_buffer *p_buffer_w = &buffer_w.builder->buffer;
    mlgm_bytes_buffer *p_buffer_r = &buffer_r.builder->buffer;

    mlgm_bytes_buffer_init_with_buffer(&reader.buffer, p_buffer_r->data, p_buffer_r->capacity);
    mlgm_bytes_buffer_init_with_buffer(&writer.buffer, p_buffer_w->data, p_buffer_w->capacity);

    // read (1)

    mlgm_bytes_buffer_reset(&reader.buffer);
    err = mlgm_file_reader_read(&reader);
    if (err)
    {
        // return err;
        mlgm_string msg = mlgm_error_get_message(err);
        mlgm_logger_warn(NIL, "%s", msg);
    }

    // write

    mlgm_bytes_buffer_reset(&writer.buffer);
    mlgm_bytes_buffer_write_string(&writer.buffer, mock_data);
    err = mlgm_file_writer_write(&writer);
    if (err)
    {
        mlgm_defer_manager_execute(&dm);
        return err;
    }

    // read (2)

    mlgm_bytes_buffer_reset(&reader.buffer);
    err = mlgm_file_reader_read(&reader);
    if (err)
    {
        mlgm_defer_manager_execute(&dm);
        return err;
    }

    mlgm_defer_manager_execute(&dm);
    return NIL;
}
