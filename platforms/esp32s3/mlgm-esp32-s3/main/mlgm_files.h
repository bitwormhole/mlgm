
#ifndef __mlgm_files_h__
#define __mlgm_files_h__

#include "mlgm_types.h"
#include "mlgm_strings.h"
#include "mlgm_paths.h"

////////////////////////////////////////////////////////////////////////////////

mlgm_error mlgm_fs_mkdir(mlgm_path path);
mlgm_error mlgm_fs_mkdirs(mlgm_path path);

mlgm_bool mlgm_fs_exists_file(mlgm_path path);
mlgm_bool mlgm_fs_exists_dir(mlgm_path path);

////////////////////////////////////////////////////////////////////////////////
// mlgm_file_reader

typedef struct t_mlgm_file_reader
{

    mlgm_path path;

    mlgm_bytes_buffer buffer;

} mlgm_file_reader;

mlgm_file_reader *mlgm_file_reader_init(mlgm_file_reader *self, mlgm_string path);
mlgm_error mlgm_file_reader_read(mlgm_file_reader *self);

////////////////////////////////////////////////////////////////////////////////
// mlgm_file_writer

typedef struct t_mlgm_file_writer
{

    mlgm_path path;

    mlgm_bytes_buffer buffer;

    mlgm_bool flag_mkdirs;
    mlgm_bool flag_create;
    mlgm_bool flag_append;

} mlgm_file_writer;

mlgm_file_writer *mlgm_file_writer_init(mlgm_file_writer *self, mlgm_string path);
mlgm_error mlgm_file_writer_write(mlgm_file_writer *self);

////////////////////////////////////////////////////////////////////////////////

#endif //  __mlgm_files_h__
