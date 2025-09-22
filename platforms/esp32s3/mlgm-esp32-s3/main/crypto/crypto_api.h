#ifndef __crypto_crypto_h__
#define __crypto_crypto_h__

#include "../mlgm_types.h"

////////////////////////////////////////////////////////////////////////////////

typedef enum t_mlgm_crypto_algorithm
{

    MLGM_CRYPTO_ALGORITHM_NONE,

    MLGM_HASH_ALGORITHM_MD5,
    MLGM_HASH_ALGORITHM_SHA1,
    MLGM_HASH_ALGORITHM_SHA256,
    MLGM_HASH_ALGORITHM_SHA512,

    MLGM_SECRET_KEY_ALGORITHM_AES,

    MLGM_PUBLIC_KEY_ALGORITHM_RSA,

} mlgm_crypto_algorithm;

////////////////////////////////////////////////////////////////////////////////

typedef struct t_crypto
{

    mlgm_int todo;

} crypto;

void crypto_init(crypto *self);

#endif //  __crypto_crypto_h__
