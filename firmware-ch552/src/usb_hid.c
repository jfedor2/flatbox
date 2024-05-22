// ===================================================================================
// USB HID Functions for CH551, CH552 and CH554
// ===================================================================================

#include "ch554.h"
#include "usb.h"
#include "usb_hid.h"
#include "usb_descr.h"
#include "usb_handler.h"

// ===================================================================================
// Variables and Defines
// ===================================================================================

volatile __bit HID_EP1_writeBusyFlag = 0;                   // upload pointer busy flag

// ===================================================================================
// Front End Functions
// ===================================================================================

// Setup USB HID
void HID_init(void) {
  USB_init();
  UEP1_T_LEN  = 0;
}

// Send HID report
void HID_sendReport(__xdata uint8_t* buf, uint8_t len) {
  uint8_t i;
  while(HID_EP1_writeBusyFlag);                             // wait for ready to write
  for(i=0; i<len; i++) EP1_buffer[i] = buf[i];              // copy report to EP1 buffer
  UEP1_T_LEN = len;                                         // set length to upload
  HID_EP1_writeBusyFlag = 1;                                // set busy flag
  UEP1_CTRL = UEP1_CTRL & ~MASK_UEP_T_RES | UEP_T_RES_ACK;  // upload data and respond ACK
}

// ===================================================================================
// HID-Specific USB Handler Functions
// ===================================================================================

// Setup HID endpoints
void HID_setup(void) {
  UEP1_DMA    = EP1_ADDR;                   // EP1 data transfer address
  UEP2_DMA    = EP2_ADDR;                   // EP2 data transfer address
  UEP1_CTRL   = bUEP_AUTO_TOG               // EP1 Auto flip sync flag
              | UEP_T_RES_NAK;              // EP1 IN transaction returns NAK
  UEP2_CTRL   = bUEP_AUTO_TOG               // EP2 Auto flip sync flag
              | UEP_R_RES_ACK;              // EP2 OUT transaction returns ACK
  UEP4_1_MOD  = bUEP1_TX_EN;                // EP1 TX enable
  UEP2_3_MOD  = bUEP2_RX_EN;                // EP2 RX_enable
}

// Reset HID parameters
void HID_reset(void) {
  UEP1_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK;
  UEP2_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK;
  HID_EP1_writeBusyFlag = 0;
}

// Endpoint 1 IN handler (HID report transfer to host)
void HID_EP1_IN(void) {
  UEP1_T_LEN = 0;                                           // no data to send anymore
  UEP1_CTRL = UEP1_CTRL & ~MASK_UEP_T_RES | UEP_T_RES_NAK;  // default NAK
  HID_EP1_writeBusyFlag = 0;                                // clear busy flag
}

// Endpoint 2 OUT handler
void HID_EP2_OUT(void) {                                    // auto response
}
