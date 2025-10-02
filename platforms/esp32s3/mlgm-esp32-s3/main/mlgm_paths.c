
#include "mlgm_paths.h"

////////////////////////////////////////////////////////////////////////////////
// mlgm_magic_path

mlgm_error mlgm_magic_path_check(mlgm_magic_path *mp)
{

    return NIL;
}

////////////////////////////////////////////////////////////////////////////////
// mlgm_class_path

mlgm_magic_path *mlgm_class_path_to_magic_path(mlgm_class_path *src)
{

    return NIL;
}

////////////////////////////////////////////////////////////////////////////////
// mlgm_complex_path

void mlgm_complex_path_complete(mlgm_complex_path *comp)
{

    return;
}

////////////////////////////////////////////////////////////////////////////////

mlgm_error mlgm_path_normalize(mlgm_path *path_in, mlgm_path *path_out)
{
    return NIL; // todo : no impl
}

mlgm_error mlgm_path_get_parent(mlgm_path *path_in, mlgm_path *path_out)
{
    return NIL; // todo : no impl
}

mlgm_error mlgm_path_get_child(mlgm_path *path_in, mlgm_string child_name, mlgm_path *path_out)
{
    return NIL; // todo : no impl
}

////////////////////////////////////////////////////////////////////////////////
// EOF
