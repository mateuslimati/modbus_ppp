/*
 * usb_driver.h
 *
 *  Created on: Jan 2, 2020
 *      Author: mateus
 */

#ifndef USB_DRIVER_H_
#define USB_DRIVER_H_

//Dependencies
#include "core/net.h"
#include "usb_device.h"

//C++ guard
#ifdef __cplusplus
   extern "C" {
#endif

//UART driver
extern const USBDriver usbDriver;

//External interrupt related functions
error_t usbInit(void);
void usbEnableIrq(void);
void usbDisableIrq(void);
void usbStartTx(void);

//C++ guard
#ifdef __cplusplus
   }
#endif

#endif /* USB_DRIVER_H_ */
