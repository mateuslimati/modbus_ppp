/**
 * @file present.h
 * @brief PRESENT encryption algorithm
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

#ifndef _PRESENT_H
#define _PRESENT_H

//Dependencies
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/core/crypto.h"

//PRESENT block size
#define PRESENT_BLOCK_SIZE 8
//Common interface for encryption algorithms
#define PRESENT_CIPHER_ALGO (&presentCipherAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief PRESENT algorithm context
 **/

typedef struct
{
   uint64_t ks[32];
} PresentContext;


//PRESENT related constants
extern const CipherAlgo presentCipherAlgo;

//PRESENT related functions
error_t presentInit(PresentContext *context, const uint8_t *key, size_t keyLen);
void presentEncryptBlock(PresentContext *context, const uint8_t *input, uint8_t *output);
void presentDecryptBlock(PresentContext *context, const uint8_t *input, uint8_t *output);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif