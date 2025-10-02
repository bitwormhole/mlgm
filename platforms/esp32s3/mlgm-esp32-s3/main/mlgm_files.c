
#include "mlgm_files.h"

#include "mlgm_logger.h"

#include <stdio.h>
#include <memory.h>

////////////////////////////////////////////////////////////////////////////////
// mlgm_file_reader

mlgm_file_reader *mlgm_file_reader_init(mlgm_file_reader *self, mlgm_string path)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        mlgm_bytes_buffer_init(&self->buffer);
        self->path.string = path;
    }
    return self;
}

mlgm_error mlgm_file_reader_read(mlgm_file_reader *self)
{

    return mlgm_error_make(500, "mlgm_file_reader_read: no impl");
}

////////////////////////////////////////////////////////////////////////////////
// mlgm_file_writer

mlgm_file_writer *mlgm_file_writer_init(mlgm_file_writer *self, mlgm_string path)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        mlgm_bytes_buffer_init(&self->buffer);
        self->path.string = path;
    }
    return self;
}

mlgm_error mlgm_file_writer_write(mlgm_file_writer *self)
{
    mlgm_error err;
    mlgm_defer_manager dm;
    mlgm_string_builder_holder parent_path_sbh;
    mlgm_path this_file_path, parent_dir_path;

    // init

    mlgm_defer_manager_init(&dm);
    mlgm_string_builder_holder_init(&parent_path_sbh, 1024);

    mlgm_string_builder_holder_auto_release(&parent_path_sbh, &dm);

    // prepare path

    this_file_path = self->path;

    err = mlgm_path_get_parent(&this_file_path, &parent_dir_path);
    if (err)
    {
        mlgm_defer_manager_execute(&dm);
        return err;
    }

    mlgm_string file_path_str = this_file_path.string;

    // prepare data

    mlgm_byte *data = self->buffer.data;
    mlgm_size data_len = self->buffer.length;

    // try mkdirs

    if (self->flag_mkdirs)
    {
        mlgm_error err = mlgm_fs_mkdirs(parent_dir_path);
        if (err)
        {
            mlgm_defer_manager_execute(&dm);
            return err;
        }
    }

    // open

    FILE *f = fopen(file_path_str, "w");
    if (f == NULL)
    {
        mlgm_defer_manager_execute(&dm);
        return mlgm_error_make_with_format(500, "mlgm_file_writer_write: fopen(path:'%s') return fail", file_path_str);
    }

    // write

    mlgm_size cb = fwrite(data, 1, data_len, f);
    if (cb == data_len)
    {
        mlgm_logger_info(NIL, "mlgm_file_writer_write: ok, write %d byte(s) to file [%s]", cb, file_path_str);
    }
    else
    {
        mlgm_logger_error(NIL, "mlgm_file_writer_write: fail to write %d byte(s) to file [%s]", data_len, file_path_str);
    }

    // close

    fclose(f);

    // done

    mlgm_defer_manager_execute(&dm);
    return NIL;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_error mlgm_fs_mkdir(mlgm_path path)
{
    return NIL; // todo : no impl
}

mlgm_error mlgm_fs_mkdirs(mlgm_path path)
{
    return NIL; // todo : no impl
}

mlgm_bool mlgm_fs_exists_file(mlgm_path path)
{
    return NIL; // todo : no impl
}

mlgm_bool mlgm_fs_exists_dir(mlgm_path path)
{
    return NIL; // todo : no impl
}

////////////////////////////////////////////////////////////////////////////////
// EOF
