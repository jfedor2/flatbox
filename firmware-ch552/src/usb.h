// ===================================================================================
// USB constant and structure define
// ===================================================================================

#pragma once
#include <stdint.h>

// USB PID
#ifndef USB_PID_SETUP
#define USB_PID_NULL            0x00  // reserved PID
#define USB_PID_SOF             0x05
#define USB_PID_SETUP           0x0D
#define USB_PID_IN              0x09
#define USB_PID_OUT             0x01
#define USB_PID_ACK             0x02
#define USB_PID_NAK             0x0A
#define USB_PID_STALL           0x0E
#define USB_PID_DATA0           0x03
#define USB_PID_DATA1           0x0B
#define USB_PID_PRE             0x0C
#endif

// USB standard device request code
#ifndef USB_GET_DESCRIPTOR
#define USB_GET_STATUS          0x00
#define USB_CLEAR_FEATURE       0x01
#define USB_SET_FEATURE         0x03
#define USB_SET_ADDRESS         0x05
#define USB_GET_DESCRIPTOR      0x06
#define USB_SET_DESCRIPTOR      0x07
#define USB_GET_CONFIGURATION   0x08
#define USB_SET_CONFIGURATION   0x09
#define USB_GET_INTERFACE       0x0A
#define USB_SET_INTERFACE       0x0B
#define USB_SYNCH_FRAME         0x0C
#endif

// USB hub class request code
#ifndef HUB_GET_DESCRIPTOR
#define HUB_GET_STATUS          0x00
#define HUB_CLEAR_FEATURE       0x01
#define HUB_GET_STATE           0x02
#define HUB_SET_FEATURE         0x03
#define HUB_GET_DESCRIPTOR      0x06
#define HUB_SET_DESCRIPTOR      0x07
#endif

// USB HID class request code
#ifndef HID_GET_REPORT
#define HID_GET_REPORT          0x01
#define HID_GET_IDLE            0x02
#define HID_GET_PROTOCOL        0x03
#define HID_SET_REPORT          0x09
#define HID_SET_IDLE            0x0A
#define HID_SET_PROTOCOL        0x0B
#endif

// Bit define for USB request type
#ifndef USB_REQ_TYP_MASK
#define USB_REQ_TYP_IN          0x80  // control IN, device to host
#define USB_REQ_TYP_OUT         0x00  // control OUT, host to device
#define USB_REQ_TYP_READ        0x80  // control read, device to host
#define USB_REQ_TYP_WRITE       0x00  // control write, host to device
#define USB_REQ_TYP_MASK        0x60  // bit mask of request type
#define USB_REQ_TYP_STANDARD    0x00
#define USB_REQ_TYP_CLASS       0x20
#define USB_REQ_TYP_VENDOR      0x40
#define USB_REQ_TYP_RESERVED    0x60
#define USB_REQ_RECIP_MASK      0x1F  // bit mask of request recipient
#define USB_REQ_RECIP_DEVICE    0x00
#define USB_REQ_RECIP_INTERF    0x01
#define USB_REQ_RECIP_ENDP      0x02
#define USB_REQ_RECIP_OTHER     0x03
#endif

// USB request type for hub class request
#ifndef HUB_GET_HUB_DESCRIPTOR
#define HUB_CLEAR_HUB_FEATURE   0x20
#define HUB_CLEAR_PORT_FEATURE  0x23
#define HUB_GET_BUS_STATE       0xA3
#define HUB_GET_HUB_DESCRIPTOR  0xA0
#define HUB_GET_HUB_STATUS      0xA0
#define HUB_GET_PORT_STATUS     0xA3
#define HUB_SET_HUB_DESCRIPTOR  0x20
#define HUB_SET_HUB_FEATURE     0x20
#define HUB_SET_PORT_FEATURE    0x23
#endif

// Hub class feature selectors
#ifndef HUB_PORT_RESET
#define HUB_C_HUB_LOCAL_POWER   0
#define HUB_C_HUB_OVER_CURRENT  1
#define HUB_PORT_CONNECTION     0
#define HUB_PORT_ENABLE         1
#define HUB_PORT_SUSPEND        2
#define HUB_PORT_OVER_CURRENT   3
#define HUB_PORT_RESET          4
#define HUB_PORT_POWER          8
#define HUB_PORT_LOW_SPEED      9
#define HUB_C_PORT_CONNECTION   16
#define HUB_C_PORT_ENABLE       17
#define HUB_C_PORT_SUSPEND      18
#define HUB_C_PORT_OVER_CURRENT 19
#define HUB_C_PORT_RESET        20
#endif

// USB descriptor type
#ifndef USB_DESCR_TYP_DEVICE
#define USB_DESCR_TYP_DEVICE    0x01
#define USB_DESCR_TYP_CONFIG    0x02
#define USB_DESCR_TYP_STRING    0x03
#define USB_DESCR_TYP_INTERF    0x04
#define USB_DESCR_TYP_ENDP      0x05
#define USB_DESCR_TYP_QUALIF    0x06
#define USB_DESCR_TYP_SPEED     0x07
#define USB_DESCR_TYP_OTG       0x09
#define USB_DESCR_TYP_IAD       0x0B
#define USB_DESCR_TYP_HID       0x21
#define USB_DESCR_TYP_REPORT    0x22
#define USB_DESCR_TYP_PHYSIC    0x23
#define USB_DESCR_TYP_CS_INTF   0x24
#define USB_DESCR_TYP_CS_ENDP   0x25
#define USB_DESCR_TYP_HUB       0x29
#endif

// USB device class
#ifndef USB_DEV_CLASS_HUB
#define USB_DEV_CLASS_RESERVED  0x00
#define USB_DEV_CLASS_AUDIO     0x01
#define USB_DEV_CLASS_COMM      0x02
#define USB_DEV_CLASS_HID       0x03
#define USB_DEV_CLASS_MONITOR   0x04
#define USB_DEV_CLASS_PHYSIC_IF 0x05
#define USB_DEV_CLASS_POWER     0x06
#define USB_DEV_CLASS_PRINTER   0x07
#define USB_DEV_CLASS_STORAGE   0x08
#define USB_DEV_CLASS_HUB       0x09
#define USB_DEV_CLASS_DATA      0x0A
#define USB_DEV_CLASS_MISC      0xEF
#define USB_DEV_CLASS_VENDOR    0xFF
#endif

// USB endpoint type and attributes
#ifndef USB_ENDP_TYPE_MASK
#define USB_ENDP_DIR_MASK       0x80
#define USB_ENDP_ADDR_MASK      0x0F
#define USB_ENDP_TYPE_MASK      0x03
#define USB_ENDP_TYPE_CTRL      0x00
#define USB_ENDP_TYPE_ISOCH     0x01
#define USB_ENDP_TYPE_BULK      0x02
#define USB_ENDP_TYPE_INTER     0x03
#define USB_ENDP_ADDR_EP1_OUT   0x01
#define USB_ENDP_ADDR_EP1_IN    0x81
#define USB_ENDP_ADDR_EP2_OUT   0x02
#define USB_ENDP_ADDR_EP2_IN    0x82
#define USB_ENDP_ADDR_EP3_OUT   0x03
#define USB_ENDP_ADDR_EP3_IN    0x83
#define USB_ENDP_ADDR_EP4_OUT   0x04
#define USB_ENDP_ADDR_EP4_IN    0x84
#endif

#ifndef USB_DEVICE_ADDR
  #define USB_DEVICE_ADDR       0x02  // default USB device address
#endif
#ifndef DEFAULT_ENDP0_SIZE
  #define DEFAULT_ENDP0_SIZE    8     // default maximum packet size for endpoint 0
#endif
#ifndef DEFAULT_ENDP1_SIZE
  #define DEFAULT_ENDP1_SIZE    8     // default maximum packet size for endpoint 1
#endif
#ifndef MAX_PACKET_SIZE
  #define MAX_PACKET_SIZE       64    // maximum packet size
#endif
#ifndef USB_BO_CBW_SIZE
  #define USB_BO_CBW_SIZE       0x1F  // total length of command block CBW
  #define USB_BO_CSW_SIZE       0x0D  // total length of command status block CSW
#endif
#ifndef USB_BO_CBW_SIG0
  #define USB_BO_CBW_SIG0       0x55  // command block CBW identification flag 'USBC'
  #define USB_BO_CBW_SIG1       0x53
  #define USB_BO_CBW_SIG2       0x42
  #define USB_BO_CBW_SIG3       0x43
  #define USB_BO_CSW_SIG0       0x55  // command status block CSW identification flag 'USBS'
  #define USB_BO_CSW_SIG1       0x53
  #define USB_BO_CSW_SIG2       0x42
  #define USB_BO_CSW_SIG3       0x53
#endif

// USB descriptor type defines
typedef struct _USB_SETUP_REQ {
    uint8_t  bRequestType;
    uint8_t  bRequest;
    uint8_t  wValueL;
    uint8_t  wValueH;
    uint8_t  wIndexL;
    uint8_t  wIndexH;
    uint8_t  wLengthL;
    uint8_t  wLengthH;
} USB_SETUP_REQ, *PUSB_SETUP_REQ;
typedef USB_SETUP_REQ __xdata *PXUSB_SETUP_REQ;

typedef struct _USB_DEVICE_DESCR {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdUSB;
    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubClass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t  iManufacturer;
    uint8_t  iProduct;
    uint8_t  iSerialNumber;
    uint8_t  bNumConfigurations;
} USB_DEV_DESCR, *PUSB_DEV_DESCR;
typedef USB_DEV_DESCR __xdata *PXUSB_DEV_DESCR;

typedef struct _USB_CONFIG_DESCR {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t wTotalLength;
    uint8_t  bNumInterfaces;
    uint8_t  bConfigurationValue;
    uint8_t  iConfiguration;
    uint8_t  bmAttributes;
    uint8_t  MaxPower;
} USB_CFG_DESCR, *PUSB_CFG_DESCR;
typedef USB_CFG_DESCR __xdata *PXUSB_CFG_DESCR;

typedef struct _USB_INTERF_DESCR {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bInterfaceNumber;
    uint8_t  bAlternateSetting;
    uint8_t  bNumEndpoints;
    uint8_t  bInterfaceClass;
    uint8_t  bInterfaceSubClass;
    uint8_t  bInterfaceProtocol;
    uint8_t  iInterface;
} USB_ITF_DESCR, *PUSB_ITF_DESCR;
typedef USB_ITF_DESCR __xdata *PXUSB_ITF_DESCR;

typedef struct _USB_ITF_ASS_DESCR {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bFirstInterface;
    uint8_t  bInterfaceCount;
    uint8_t  bFunctionClass;
    uint8_t  bFunctionSubClass;
    uint8_t  bFunctionProtocol;
    uint8_t  iFunction;
} USB_IAD_DESCR, *PUSB_IAD_DESCR;
typedef USB_IAD_DESCR __xdata *PXUSB_IAD_DESCR;

typedef struct _USB_ENDPOINT_DESCR {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bEndpointAddress;
    uint8_t  bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t  bInterval;
} USB_ENDP_DESCR, *PUSB_ENDP_DESCR;
typedef USB_ENDP_DESCR __xdata *PXUSB_ENDP_DESCR;

typedef struct _USB_CONFIG_DESCR_LONG {
    USB_CFG_DESCR   cfg_descr;
    USB_ITF_DESCR   itf_descr;
    USB_ENDP_DESCR  endp_descr[1];
} USB_CFG_DESCR_LONG, *PUSB_CFG_DESCR_LONG;
typedef USB_CFG_DESCR_LONG __xdata *PXUSB_CFG_DESCR_LONG;

typedef struct _USB_HUB_DESCR {
    uint8_t  bDescLength;
    uint8_t  bDescriptorType;
    uint8_t  bNbrPorts;
    uint16_t wHubCharacteristics;
    uint8_t  bPwrOn2PwrGood;
    uint8_t  bHubContrCurrent;
    uint8_t  DeviceRemovable;
    uint8_t  PortPwrCtrlMask;
} USB_HUB_DESCR, *PUSB_HUB_DESCR;
typedef USB_HUB_DESCR __xdata *PXUSB_HUB_DESCR;

typedef struct _USB_HID_DESCR {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdHID;
    uint8_t  bCountryCode;
    uint8_t  bNumDescriptors;
    uint8_t  bDescriptorTypeX;
    uint16_t wDescriptorLength;
} USB_HID_DESCR, *PUSB_HID_DESCR;
typedef USB_HID_DESCR __xdata *PXUSB_HID_DESCR;

typedef struct _UDISK_BOC_CBW {             // command of BulkOnly USB-FlashDisk
    uint8_t mCBW_Sig0;
    uint8_t mCBW_Sig1;
    uint8_t mCBW_Sig2;
    uint8_t mCBW_Sig3;
    uint8_t mCBW_Tag0;
    uint8_t mCBW_Tag1;
    uint8_t mCBW_Tag2;
    uint8_t mCBW_Tag3;
    uint8_t mCBW_DataLen0;
    uint8_t mCBW_DataLen1;
    uint8_t mCBW_DataLen2;
    uint8_t mCBW_DataLen3;                  // uppest byte of data length, always is 0
    uint8_t mCBW_Flag;                      // transfer direction and etc.
    uint8_t mCBW_LUN;
    uint8_t mCBW_CB_Len;                    // length of command block
    uint8_t mCBW_CB_Buf[16];                // command block buffer
} UDISK_BOC_CBW, *PUDISK_BOC_CBW;
typedef UDISK_BOC_CBW __xdata *PXUDISK_BOC_CBW;

typedef struct _UDISK_BOC_CSW {             // status of BulkOnly USB-FlashDisk
    uint8_t mCSW_Sig0;
    uint8_t mCSW_Sig1;
    uint8_t mCSW_Sig2;
    uint8_t mCSW_Sig3;
    uint8_t mCSW_Tag0;
    uint8_t mCSW_Tag1;
    uint8_t mCSW_Tag2;
    uint8_t mCSW_Tag3;
    uint8_t mCSW_Residue0;                  // return: remainder bytes
    uint8_t mCSW_Residue1;
    uint8_t mCSW_Residue2;
    uint8_t mCSW_Residue3;                  // uppest byte of remainder length, always is 0
    uint8_t mCSW_Status;                    // return: result status
} UDISK_BOC_CSW, *PUDISK_BOC_CSW;
typedef UDISK_BOC_CSW __xdata *PXUDISK_BOC_CSW;
