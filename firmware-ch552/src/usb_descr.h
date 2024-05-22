// ===================================================================================
// USB Descriptors and Definitions
// ===================================================================================
//
// Definition of USB descriptors and endpoint sizes and addresses.
//
// The following must be defined in config.h:
// USB_VENDOR_ID            - Vendor ID (16-bit word)
// USB_PRODUCT_ID           - Product ID (16-bit word)
// USB_DEVICE_VERSION       - Device version (16-bit BCD)
// USB_MAX_POWER_mA         - Device max power in mA
// All string descriptors.

#pragma once
#include <stdint.h>
#include "usb.h"

// ===================================================================================
// USB Endpoint Addresses and Sizes
// ===================================================================================
#define EP0_SIZE        8
#define EP1_SIZE        8
#define EP2_SIZE        8

#define EP0_ADDR        0
#define EP1_ADDR        (EP0_ADDR + EP0_BUF_SIZE)
#define EP2_ADDR        (EP1_ADDR + EP1_BUF_SIZE)

#define EP0_BUF_SIZE    EP_BUF_SIZE(EP0_SIZE)
#define EP1_BUF_SIZE    EP_BUF_SIZE(EP1_SIZE)
#define EP2_BUF_SIZE    EP_BUF_SIZE(EP2_SIZE)

#define EP_BUF_SIZE(x)  (x+2<64 ? x+2 : 64)

// ===================================================================================
// Device and Configuration Descriptors
// ===================================================================================
typedef struct _USB_CFG_DESCR_HID {
  USB_CFG_DESCR config;
  USB_ITF_DESCR interface0;
  USB_HID_DESCR hid0;
  USB_ENDP_DESCR ep1IN;
  USB_ENDP_DESCR ep2OUT;
} USB_CFG_DESCR_HID, *PUSB_CFG_DESCR_HID;
typedef USB_CFG_DESCR_HID __xdata *PXUSB_CFG_DESCR_HID;

extern __code USB_DEV_DESCR DevDescr;
extern __code USB_CFG_DESCR_HID CfgDescr;

// ===================================================================================
// HID Report Descriptors
// ===================================================================================
extern __code uint8_t ReportDescr[];
extern __code uint8_t ReportDescrLen;

#define USB_REPORT_DESCR      ReportDescr
#define USB_REPORT_DESCR_LEN  ReportDescrLen

// ===================================================================================
// String Descriptors
// ===================================================================================
extern __code uint16_t LangDescr[];
extern __code uint16_t ManufDescr[];
extern __code uint16_t ProdDescr[];

#define USB_STR_DESCR_i0    (uint8_t*)LangDescr
#define USB_STR_DESCR_i1    (uint8_t*)ManufDescr
#define USB_STR_DESCR_i2    (uint8_t*)ProdDescr
#define USB_STR_DESCR_ix    (uint8_t*)ProdDescr
