/**
 * @file sha256.h
 * @brief SHA-256 (Secure Hash Algorithm 256)
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2010-2019 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneCrypto Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.9.6
 **/

#ifndef _SHA256_H
#define _SHA256_H

//Dependencies
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/core/crypto.h"

//SHA-256 block size
#define SHA256_BLOCK_SIZE 64
//SHA-256 digest size
#define SHA256_DIGEST_SIZE 32
//Minimum length of the padding string
#define SHA256_MIN_PAD_SIZE 9
//SHA-256 algorithm object identifier
#define SHA256_OID sha256Oid
//Common interface for hash algorithms
#define SHA256_HASH_ALGO (&sha256HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief SHA-256 algorithm context
 **/

typedef struct
{
   union
   {
      uint32_t h[8];
      uint8_t digest[32];
   };
   union
   {
      uint32_t w[16];
      uint8_t buffer[64];
   };
   size_t size;
   uint64_t totalSize;
} Sha256Context;


//SHA-256 related constants
extern const uint8_t sha256Oid[9];
extern const HashAlgo sha256HashAlgo;

//SHA-256 related functions
error_t sha256Compute(const void *data, size_t length, uint8_t *digest);
void sha256Init(Sha256Context *context);
void sha256Update(Sha256Context *context, const void *data, size_t length);
void sha256Final(Sha256Context *context, uint8_t *digest);
void sha256FinalRaw(Sha256Context *context, uint8_t *digest);
void sha256ProcessBlock(Sha256Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
