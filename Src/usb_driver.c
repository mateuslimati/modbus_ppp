/*
 * usb_driver.c
 *
 *  Created on: Jan 2, 2020
 *      Author: mateus
 */

//Dependencies
#include <stdio.h>
#include "stm32l4xx.h"
#include "core/net.h"
#include "ppp/ppp_hdlc.h"
#include "usb_driver.h"
#include "debug.h"

//Enable hardware flow control
#define APP_USB_HW_FLOW_CTRL ENABLED

/**
 * @brief USB driver
 **/

const USBDriver usbDriver = { usbInit, usbEnableIrq, usbDisableIrq, usbStartTx };

/**
 * @brief UART configuration
 * @return Error code
 **/

error_t usbInit(void) {
	//Successful processing
	return NO_ERROR;
}

/**
 * @brief Enable USB interrupts
 **/

void usbEnableIrq(void) {
	//Enable USB interrupts
}

/**
 * @brief Disable USB interrupts
 **/

void usbDisableIrq(void) {
	//Disable USB interrupt
}

/**
 * @brief Start transmission
 **/

void usbStartTx(void) {

	int_t c;
	bool_t flag;
	NetInterface *interface;

	//Enter interrupt service routine
	osEnterIsr();

	//This flag will be set if a higher priority task must be woken
	flag = FALSE;

	//Point to the PPP network interface
	interface = &netInterface[0];

	//Get next character
	flag |= pppHdlcDriverReadTxQueue(interface, &c);
	//Valid character read?
	while (c != EOF) {
		//Send data byte
		CDC_Transmit_FS(&c, 1);
		flag |= pppHdlcDriverReadTxQueue(interface, &c);
	}

	osExitIsr(flag);
}

