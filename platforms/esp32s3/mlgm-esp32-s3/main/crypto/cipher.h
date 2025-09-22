#ifndef __crypto_cipher_h__
#define __crypto_cipher_h__

#include "../mlgm_types.h"

typedef struct t_cipher
{

    mlgm_int todo;

} cipher;

void cipher_init(cipher *self);

#endif //  __crypto_cipher_h__
