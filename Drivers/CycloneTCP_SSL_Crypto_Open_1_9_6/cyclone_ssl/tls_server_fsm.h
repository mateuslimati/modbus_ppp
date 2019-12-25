/**
 * @file tls_server_fsm.h
 * @brief TLS state machine (TLS server)
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2010-2019 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneSSL Open.
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

#ifndef _TLS_SERVER_FSM_H
#define _TLS_SERVER_FSM_H

//Dependencies
#include "../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_ssl/tls.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//TLS related functions
error_t tlsPerformServerHandshake(TlsContext *context);

error_t tlsParseClientHandshakeMessage(TlsContext *context, uint8_t msgType,
   const void *message, size_t length);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif