/**
 * @file debug.c
 * @brief Debugging facilities
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2010-2019 Oryx Embedded SARL. All rights reserved.
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

//Dependencies
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "debug.h"

//Variable declaration
static UART_HandleTypeDef UART_Handle;


/**
 * @brief Debug UART initialization
 * @param[in] baudrate UART baudrate
 **/

void debugInit(uint32_t baudrate)
{
   GPIO_InitTypeDef GPIO_InitStructure;

   //Enable PWR clock
   __HAL_RCC_PWR_CLK_ENABLE();
   //Enable VDDIO2 power supply for pins PG[15:2]
   HAL_PWREx_EnableVddIO2();

   //Enable GPIOG clock
   __HAL_RCC_GPIOG_CLK_ENABLE();
   //Enable LPUART1 clock
   __HAL_RCC_LPUART1_CLK_ENABLE();

   //Configure LPUART1_TX (PG7)
   GPIO_InitStructure.Pin = GPIO_PIN_7;
   GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStructure.Pull = GPIO_PULLUP;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
   GPIO_InitStructure.Alternate = GPIO_AF8_LPUART1;
   HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

   //Configure LPUART1_RX (PG8)
   GPIO_InitStructure.Pin = GPIO_PIN_8;
   GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStructure.Pull = GPIO_PULLUP;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
   GPIO_InitStructure.Alternate = GPIO_AF8_LPUART1;
   HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

   //Configure LPUART1
   UART_Handle.Instance = LPUART1;
   UART_Handle.Init.BaudRate = baudrate;
   UART_Handle.Init.WordLength = UART_WORDLENGTH_8B;
   UART_Handle.Init.StopBits = UART_STOPBITS_1;
   UART_Handle.Init.Parity = UART_PARITY_NONE;
   UART_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
   UART_Handle.Init.Mode = UART_MODE_TX_RX;
   UART_Handle.Init.OverSampling = UART_OVERSAMPLING_16;
   UART_Handle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
   HAL_UART_Init(&UART_Handle);
}


/**
 * @brief Display the contents of an array
 * @param[in] stream Pointer to a FILE object that identifies an output stream
 * @param[in] prepend String to prepend to the left of each line
 * @param[in] data Pointer to the data array
 * @param[in] length Number of bytes to display
 **/

void debugDisplayArray(FILE *stream,
   const char_t *prepend, const void *data, size_t length)
{
   uint_t i;

   for(i = 0; i < length; i++)
   {
      //Beginning of a new line?
      if((i % 16) == 0)
         fprintf(stream, "%s", prepend);
      //Display current data byte
      fprintf(stream, "%02" PRIX8 " ", *((uint8_t *) data + i));
      //End of current line?
      if((i % 16) == 15 || i == (length - 1))
         fprintf(stream, "\r\n");
   }
}


/**
 * @brief Write character to stream
 * @param[in] c The character to be written
 * @param[in] stream Pointer to a FILE object that identifies an output stream
 * @return On success, the character written is returned. If a writing
 *   error occurs, EOF is returned
 **/

int_t fputc(int_t c, FILE *stream)
{
   //Standard output or error output?
   if(stream == stdout || stream == stderr)
   {
      //Character to be written
      uint8_t ch = c;

      //Transmit data
      HAL_UART_Transmit(&UART_Handle, &ch, 1, HAL_MAX_DELAY);

      //On success, the character written is returned
      return c;
   }
   //Unknown output?
   else
   {
      //If a writing error occurs, EOF is returned
      return EOF;
   }
}
