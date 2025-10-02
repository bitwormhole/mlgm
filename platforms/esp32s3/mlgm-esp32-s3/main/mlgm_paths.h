
#ifndef __mlgm_paths_h__
#define __mlgm_paths_h__

#include "mlgm_types.h"
#include "mlgm_errors.h"
#include "mlgm_strings.h"

////////////////////////////////////////////////////////////////////////////////

// 表示一个通用的路径 ，like: '/a0/b1/c2/3/456789abcd'
typedef struct t_mlgm_path
{

    mlgm_string string;

    // optional: 如果存在 writer 字段，表示这个对象是 rewritable 的
    mlgm_string_builder *writer;

} mlgm_path;

mlgm_error mlgm_path_normalize(mlgm_path *path_in, mlgm_path *path_out);
mlgm_error mlgm_path_get_parent(mlgm_path *path_in, mlgm_path *path_out);
mlgm_error mlgm_path_get_child(mlgm_path *path_in, mlgm_string child_name, mlgm_path *path_out);

////////////////////////////////////////////////////////////////////////////////

// 表示一个 魔术 路径 ，like: '/.mlgm/0/1/2/3/456789abcd'
typedef struct t_mlgm_magic_path
{

    mlgm_path path;

} mlgm_magic_path;

mlgm_error mlgm_magic_path_check(mlgm_magic_path *mp);

////////////////////////////////////////////////////////////////////////////////

// 表示一个分类路径 ，like: '/.mlgm/classes/{email}/{domain1}/{domain2}/{username}/{scene}/'
typedef struct t_mlgm_class_path
{

    mlgm_path path; // 完整的路径

    // 以下是路径的各个组成部分

    mlgm_string email;    // 管理者邮箱地址
    mlgm_string domain1;  // 管理者域名
    mlgm_string domain2;  // 被管理者的域名
    mlgm_string username; // 被管理者的用户名
    mlgm_string scene;    // 被管理的账户使用场景

    mlgm_string file; //  文件的 simple-name

} mlgm_class_path;

mlgm_magic_path *mlgm_class_path_to_magic_path(mlgm_class_path *cp);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_complex_path
{

    mlgm_magic_path mp;
    mlgm_class_path cp;

} mlgm_complex_path;

void mlgm_complex_path_complete(mlgm_complex_path *self);

////////////////////////////////////////////////////////////////////////////////

#endif //  __mlgm_paths_h__
