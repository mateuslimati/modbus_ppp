/**
 * @file uart_driver.c
 * @brief UART driver
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
#include <stdio.h>
#include "stm32l4xx.h"
#include "core/net.h"
#include "ppp/ppp_hdlc.h"
#include "uart_driver.h"
#include "debug.h"
#include "main.h"

//Enable hardware flow control
#define APP_UART_HW_FLOW_CTRL ENABLED

//Variable declaration
UART_HandleTypeDef hlpuart1;

/**
 * @brief UART driver
 **/

const UartDriver uartDriver = { uartInit, uartEnableIrq, uartDisableIrq,
		uartStartTx };

/**
 * @brief UART configuration
 * @return Error code
 **/

error_t uartInit(void) {
	GPIO_InitTypeDef GPIO_InitStruct;

	//Enable LPUART1 clock
	__HAL_RCC_LPUART1_CLK_ENABLE()
	;

	//Enable GPIOG clocks
	__HAL_RCC_GPIOG_CLK_ENABLE()
	;

	//Enable PWR clock
	HAL_PWREx_EnableVddIO2();

	/**LPUART1 GPIO Configuration
	 PG7     ------> LPUART1_TX
	 PG8     ------> LPUART1_RX
	 */
	GPIO_InitStruct.Pin = STLK_RX_Pin | STLK_TX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF8_LPUART1;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	//Configure LPUART1
	hlpuart1.Instance = LPUART1;
	hlpuart1.Init.BaudRate = 115200;
	hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
	hlpuart1.Init.StopBits = UART_STOPBITS_1;
	hlpuart1.Init.Parity = UART_PARITY_NONE;
	hlpuart1.Init.Mode = UART_MODE_TX_RX;
	hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&hlpuart1) != HAL_OK) {
		Error_Handler();
	}

	//Configure USART2 interrupts
	__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_TXE);
	__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_RXNE);

	//Set priority grouping (4 bits for pre-emption priority, no bits
	//for subpriority)
	NVIC_SetPriorityGrouping(3);

	//Configure Ethernet interrupt priority
	NVIC_SetPriority(LPUART1_IRQn, NVIC_EncodePriority(3, 12, 0));

	//Enable USART1
	__HAL_UART_ENABLE(&hlpuart1);

	//Successful processing
	return NO_ERROR;
}

/**
 * @brief Enable LPUART1 interrupts
 **/

void uartEnableIrq(void) {
	//Enable LPUART1 interrupts
	NVIC_EnableIRQ(LPUART1_IRQn);
}

/**
 * @brief Disable LPUART1 interrupts
 **/

void uartDisableIrq(void) {
	//Disable LPUART1 interrupt
	NVIC_DisableIRQ(LPUART1_IRQn);
}

/**
 * @brief Start transmission
 **/

void uartStartTx(void) {
	//Enable TXE interrupt
	__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_TXE);
}

/**
 * @brief UART interrupt handler
 **/

void LPUART1_IRQHandler(void) {
	int_t c;
	bool_t flag;
	NetInterface *interface;

	//Enter interrupt service routine
	osEnterIsr();

	//This flag will be set if a higher priority task must be woken
	flag = FALSE;

	//Point to the PPP network interface
	interface = &netInterface[0];

	//TXE interrupt?
	if (__HAL_UART_GET_FLAG(&hlpuart1, UART_FLAG_TXE) != RESET &&
	__HAL_UART_GET_IT_SOURCE(&hlpuart1, UART_IT_TXE) != RESET) {
		//Get next character
		flag |= pppHdlcDriverReadTxQueue(interface, &c);

		//Valid character read?
		if (c != EOF) {
			//Send data byte
			hlpuart1.Instance->TDR = c;
		} else {
			//Disable TXE interrupt
			__HAL_UART_DISABLE_IT(&hlpuart1, UART_IT_TXE);
		}
	}

	//RXNE interrupt?
	if (__HAL_UART_GET_FLAG(&hlpuart1, UART_FLAG_RXNE) != RESET &&
	__HAL_UART_GET_IT_SOURCE(&hlpuart1, UART_IT_RXNE) != RESET) {
		//Read data byte
		c = hlpuart1.Instance->RDR;
		//Process incoming character
		flag |= pppHdlcDriverWriteRxQueue(interface, c);
	}

	//ORE interrupt?
	if (__HAL_UART_GET_FLAG(&hlpuart1, UART_FLAG_ORE) != RESET &&
	__HAL_UART_GET_IT_SOURCE(&hlpuart1, UART_IT_RXNE) != RESET) {
		//Clear ORE interrupt flag
		__HAL_UART_CLEAR_OREFLAG(&hlpuart1);
	}

	//Leave interrupt service routine
	osExitIsr(flag);
}
