

#ifndef __mlgm_time_h__
#define __mlgm_time_h__

#include "mlgm_types.h"

// mlgm_time_stamp 表示一个时间戳;
// in ms;
// 0 = [1970-01-01_00:00:00.000]
typedef mlgm_int64 mlgm_time_stamp;

// mlgm_time_span 表示时间长度
// in ms
typedef mlgm_int64 mlgm_time_span;

void mlgm_time_sleep(mlgm_time_span ms);
void mlgm_time_sleep_infinity(mlgm_string tag);

#endif // __mlgm_time_h__
