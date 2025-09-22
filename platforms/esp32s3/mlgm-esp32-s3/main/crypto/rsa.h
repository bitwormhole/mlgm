#ifndef __crypto_rsa_h__
#define __crypto_rsa_h__

#include "../mlgm_types.h"

typedef struct t_rsa
{

    mlgm_int todo;

} rsa;

void rsa_init(rsa *self);

#endif //  __crypto_rsa_h__
