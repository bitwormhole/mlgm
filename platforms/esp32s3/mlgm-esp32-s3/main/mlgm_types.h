#ifndef __mlgm_types_h__
#define __mlgm_types_h__

////////////////////////////////////////////////////////////////////////////////
// base types

typedef char mlgm_int8;
typedef short mlgm_int16;
typedef long mlgm_int32;
typedef long long mlgm_int64;

typedef unsigned char mlgm_uint8;
typedef unsigned short mlgm_uint16;
typedef unsigned long mlgm_uint32;
typedef unsigned long long mlgm_uint64;

typedef int mlgm_int;
typedef unsigned int mlgm_uint;

typedef mlgm_int8 mlgm_char;
typedef mlgm_uint8 mlgm_bool;
typedef mlgm_uint8 mlgm_byte;
typedef mlgm_int mlgm_size;

typedef const char *mlgm_string;

////////////////////////////////////////////////////////////////////////////////
// value range

// int

static const mlgm_int8 mlgm_int8_min = -128;
static const mlgm_int8 mlgm_int8_max = 127;

static const mlgm_int16 mlgm_int16_min = -32768;
static const mlgm_int16 mlgm_int16_max = 32767;

static const mlgm_int32 mlgm_int32_min = -2147483648;
static const mlgm_int32 mlgm_int32_max = 2147483647;

static const mlgm_int64 mlgm_int64_min = -9223372036854775807LL;
static const mlgm_int64 mlgm_int64_max = 9223372036854775807LL;

// uint

static const mlgm_uint8 mlgm_uint8_min = 0;
static const mlgm_uint8 mlgm_uint8_max = 0xff;

static const mlgm_uint16 mlgm_uint16_min = 0;
static const mlgm_uint16 mlgm_uint16_max = 0xffff;

static const mlgm_uint32 mlgm_uint32_min = 0;
static const mlgm_uint32 mlgm_uint32_max = 0xffffffff;

static const mlgm_uint64 mlgm_uint64_min = 0;
static const mlgm_uint64 mlgm_uint64_max = 0xffffffffffffffff;

// default

static const mlgm_int mlgm_int_min = mlgm_int32_min;
static const mlgm_int mlgm_int_max = mlgm_int32_max;

static const mlgm_uint mlgm_uint_min = mlgm_uint32_min;
static const mlgm_uint mlgm_uint_max = mlgm_uint32_max;

////////////////////////////////////////////////////////////////////////////////
// #define

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
