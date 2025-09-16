#ifndef __mlgm_types_h__
#define __mlgm_types_h__

typedef int mlgm_int;
typedef char mlgm_int8;
typedef short mlgm_int16;
typedef long mlgm_int32;
typedef long long mlgm_int64;

typedef unsigned int mlgm_uint;
typedef unsigned char mlgm_uint8;
typedef unsigned short mlgm_uint16;
typedef unsigned long mlgm_uint32;
typedef unsigned long long mlgm_uint64;

typedef char mlgm_bool;
typedef mlgm_uint8 mlgm_byte;
typedef mlgm_int mlgm_size;

typedef const char *mlgm_string;

////////////////////////////////////////////////////////////////////////////////

#ifndef NIL
#define NIL 0
#endif // NIL

#ifndef YES
#define YES 1
#endif // YES

#ifndef NO
#define NO 0
#endif // NO

#define MLGM_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MLGM_MAX(a, b) (((a) > (b)) ? (a) : (b))

////////////////////////////////////////////////////////////////////////////////

#endif // __mlgm_types_h__
