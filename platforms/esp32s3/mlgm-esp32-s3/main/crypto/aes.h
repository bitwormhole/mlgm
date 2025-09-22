#ifndef __crypto_aes_h__
#define __crypto_aes_h__

#include "../mlgm_types.h"

typedef struct t_aes
{

    mlgm_int todo;

} aes;

void aes_init(aes *self);

#endif //  __crypto_aes_h__
