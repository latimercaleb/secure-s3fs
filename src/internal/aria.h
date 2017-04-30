/*
 * Copyright 2006-2017 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

/* ====================================================================
 * Copyright (c) 2017 Oracle and/or its affiliates.  All rights reserved.
 */

#ifndef HEADER_ARIA_H
# define HEADER_ARIA_H

# include <openssl/opensslconf.h>

# ifdef OPENSSL_NO_ARIA
#  error ARIA is disabled.
# endif

# include <stddef.h>

# define ARIA_ENCRYPT     1
# define ARIA_DECRYPT     0

# define ARIA_BLOCK_SIZE    16  /* Size of each encryption/decription block */
# define ARIA_MAX_KEYS      17  /* Number of keys needed in the worst case  */

# ifdef  __cplusplus
extern "C" {
# endif

typedef unsigned char ARIA_u128[ARIA_BLOCK_SIZE];

struct aria_key_st {
    unsigned int rounds;
    ARIA_u128 rd_key[ARIA_MAX_KEYS];
};
typedef struct aria_key_st ARIA_KEY;


int aria_set_encrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key);
int aria_set_decrypt_key(const unsigned char *userKey, const int bits,
                         ARIA_KEY *key);

void aria_encrypt(const unsigned char *in, unsigned char *out,
                  const ARIA_KEY *key);

# ifdef  __cplusplus
}
# endif

#endif
