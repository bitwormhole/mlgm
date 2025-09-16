
#ifndef __mlgm_errors_h__
#define __mlgm_errors_h__

#include "mlgm_types.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_error_info
{

    mlgm_int code;
    mlgm_string message;

} mlgm_error_info;

typedef mlgm_error_info *mlgm_error;

mlgm_error mlgm_error_make(mlgm_int code, mlgm_string msg);
mlgm_error mlgm_error_make_with_format(mlgm_int code, mlgm_string format, ...);
mlgm_string mlgm_error_get_message(mlgm_error err);

////////////////////////////////////////////////////////////////////////////////

#endif // __mlgm_errors_h__
