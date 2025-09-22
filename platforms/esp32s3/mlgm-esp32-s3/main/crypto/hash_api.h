#ifndef __crypto_hash_h__
#define __crypto_hash_h__

#include "../mlgm_types.h"

typedef struct t_hash
{

    mlgm_int todo;

} hash;

void hash_init(hash *self);

#endif //  __crypto_hash_h__
