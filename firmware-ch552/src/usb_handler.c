// ===================================================================================
// USB Handler for CH551, CH552 and CH554
// ===================================================================================

#include "ch554.h"
#include "usb_handler.h"

uint16_t SetupLen;
uint8_t  SetupReq, UsbConfig;
__code uint8_t *pDescr;

// ===================================================================================
// Fast Copy Function
// ===================================================================================
// Copy descriptor *pDescr to Ep0 using double pointer
// (Thanks to Ralph Doncaster)
#pragma callee_saves USB_EP0_copyDescr
void USB_EP0_copyDescr(uint8_t len) {
  len;                          // stop unreferenced argument warning
  __asm
    push ar7                    ; r7 -> stack
    mov  r7, dpl                ; r7 <- len
    inc  _XBUS_AUX              ; select dptr1
    mov  dptr, #_EP0_buffer     ; dptr1 <- EP0_buffer
    dec  _XBUS_AUX              ; select dptr0
    mov  dpl, _pDescr           ; dptr0 <- *pDescr
    mov  dph, (_pDescr + 1)
    01$:
    clr  a                      ; acc <- #0
    movc a, @a+dptr             ; acc <- *pDescr[dptr0]
    inc  dptr                   ; inc dptr0
    .DB  0xA5                   ; acc -> EP0_buffer[dptr1] & inc dptr1
    djnz r7, 01$                ; repeat len times
    pop  ar7                    ; r7 <- stack
  __endasm;
}

// ===================================================================================
// Endpoint Handler
// ===================================================================================

void USB_EP0_SETUP(void) {
  uint8_t len = USB_RX_LEN;
  if(len == (sizeof(USB_SETUP_REQ))) {
    SetupLen = ((uint16_t)USB_setupBuf->wLengthH<<8) | (USB_setupBuf->wLengthL);
    len = 0;                                      // default is success and upload 0 length
    SetupReq = USB_setupBuf->bRequest;

    if( (USB_setupBuf->bRequestType & USB_REQ_TYP_MASK) != USB_REQ_TYP_STANDARD ) {
      #ifdef USB_CTRL_NS_handler
      len = USB_CTRL_NS_handler();                // non-standard request
      #else
      len = 0xFF;                                 // command not supported
      #endif
    }

    else {                                        // standard request
      switch(SetupReq) {                          // request ccfType
        case USB_GET_DESCRIPTOR:
          switch(USB_setupBuf->wValueH) {

            case USB_DESCR_TYP_DEVICE:            // Device Descriptor
              pDescr = (uint8_t*)&DevDescr;       // put descriptor into out buffer
              len = sizeof(DevDescr);             // descriptor length
              break;

            case USB_DESCR_TYP_CONFIG:            // Configuration Descriptor
              pDescr = (uint8_t*)&CfgDescr;       // put descriptor into out buffer
              len = sizeof(CfgDescr);             // descriptor length
              break;

            case USB_DESCR_TYP_STRING:
              switch(USB_setupBuf->wValueL) {      // String Descriptor Index
                case 0:   pDescr = USB_STR_DESCR_i0; break;
                case 1:   pDescr = USB_STR_DESCR_i1; break;
                case 2:   pDescr = USB_STR_DESCR_i2; break;
                #ifdef USB_STR_DESCR_i3
                case 3:   pDescr = USB_STR_DESCR_i3; break;
                #endif
                #ifdef USB_STR_DESCR_i4
                case 4:   pDescr = USB_STR_DESCR_i4; break;
                #endif
                #ifdef USB_STR_DESCR_i5
                case 5:   pDescr = USB_STR_DESCR_i5; break;
                #endif
                #ifdef USB_STR_DESCR_i6
                case 6:   pDescr = USB_STR_DESCR_i6; break;
                #endif
                #ifdef USB_STR_DESCR_i7
                case 7:   pDescr = USB_STR_DESCR_i7; break;
                #endif
                #ifdef USB_STR_DESCR_i8
                case 8:   pDescr = USB_STR_DESCR_i8; break;
                #endif
                #ifdef USB_STR_DESCR_i9
                case 9:   pDescr = USB_STR_DESCR_i9; break;
                #endif
                #ifdef USB_STR_DESCR_ixee
                case 0xee: pDescr = USB_STR_DESCR_ixee; break;
                #endif
                default:  pDescr = USB_STR_DESCR_ix; break;
              }
              len = pDescr[0];                    // descriptor length
              break;

            #ifdef USB_REPORT_DESCR
            case USB_DESCR_TYP_REPORT:
              if(USB_setupBuf->wValueL == 0) {
                pDescr = USB_REPORT_DESCR;
                len = USB_REPORT_DESCR_LEN;
              }
              else len = 0xff;
              break;
            #endif

            default:
              len = 0xff;                         // unsupported descriptors or error
              break;
          }

          if(len != 0xff) {
            if(SetupLen > len) SetupLen = len;    // limit length
            len = SetupLen >= EP0_SIZE ? EP0_SIZE : SetupLen;
            USB_EP0_copyDescr(len);               // copy descriptor to Ep0
            SetupLen -= len;
            pDescr += len;
          }
          break;

        case USB_SET_ADDRESS:
          SetupLen = USB_setupBuf->wValueL;        // save the assigned address
          break;

        case USB_GET_CONFIGURATION:
          EP0_buffer[0] = UsbConfig;
          if (SetupLen >= 1) len = 1;
          break;

        case USB_SET_CONFIGURATION:
          UsbConfig = USB_setupBuf->wValueL;
          break;

        case USB_GET_INTERFACE:
          break;

        case USB_SET_INTERFACE:
          break;

        case USB_CLEAR_FEATURE:
          if( (USB_setupBuf->bRequestType & 0x1F) == USB_REQ_RECIP_DEVICE ) {
            if( ( ( (uint16_t)USB_setupBuf->wValueH << 8 ) | USB_setupBuf->wValueL ) == 0x01 ) {
              if( ((uint8_t*)&CfgDescr)[7] & 0x20) {
                // wake up
              }
              else len = 0xFF;               // failed
            }
            else len = 0xFF;                 // failed
          }
          else if( (USB_setupBuf->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_ENDP ) {
            switch(USB_setupBuf->wIndexL) {
              #ifdef EP4_IN_callback
              case 0x84:
                UEP4_CTRL = UEP4_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
                break;
              #endif
              #ifdef EP4_OUT_callback
              case 0x04:
                UEP4_CTRL = UEP4_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
                break;
              #endif
              #ifdef EP3_IN_callback
              case 0x83:
                UEP3_CTRL = UEP3_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
                break;
              #endif
              #ifdef EP3_OUT_callback
              case 0x03:
                UEP3_CTRL = UEP3_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
                break;
              #endif
              #ifdef EP2_IN_callback
              case 0x82:
                UEP2_CTRL = UEP2_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
                break;
              #endif
              #ifdef EP2_OUT_callback
              case 0x02:
                UEP2_CTRL = UEP2_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
                break;
              #endif
              #ifdef EP1_IN_callback
              case 0x81:
                UEP1_CTRL = UEP1_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
                break;
              #endif
              #ifdef EP1_OUT_callback
              case 0x01:
                UEP1_CTRL = UEP1_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
                break;
              #endif
              default:
                len = 0xFF;                 // unsupported endpoint
                break;
            }
          }
          else len = 0xFF;                  // unsupported for non-endpoint
          break;

        case USB_SET_FEATURE:
          if( (USB_setupBuf->bRequestType & 0x1F) == USB_REQ_RECIP_DEVICE ) {
            if( ( ( (uint16_t)USB_setupBuf->wValueH << 8 ) | USB_setupBuf->wValueL ) == 0x01 ) {
              if( !(((uint8_t*)&CfgDescr)[7] & 0x20) ) len = 0xFF;  // failed
            }
            else len = 0xFF;                                        // failed
          }
          else if( (USB_setupBuf->bRequestType & 0x1F) == USB_REQ_RECIP_ENDP ) {
            if( ( ( (uint16_t)USB_setupBuf->wValueH << 8 ) | USB_setupBuf->wValueL ) == 0x00 ) {
              switch( ( (uint16_t)USB_setupBuf->wIndexH << 8 ) | USB_setupBuf->wIndexL ) {
                #ifdef EP4_IN_callback
                case 0x84:
                  UEP4_CTRL = UEP4_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;// Set EP4 IN STALL 
                  break;
                #endif
                #ifdef EP4_OUT_callback
                case 0x04:
                  UEP4_CTRL = UEP4_CTRL & (~bUEP_R_TOG) | UEP_R_RES_STALL;// Set EP4 OUT Stall 
                  break;
                #endif
                #ifdef EP3_IN_callback
                case 0x83:
                  UEP3_CTRL = UEP3_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;// Set EP3 IN STALL 
                  break;
                #endif
                #ifdef EP3_OUT_callback
                case 0x03:
                  UEP3_CTRL = UEP3_CTRL & (~bUEP_R_TOG) | UEP_R_RES_STALL;// Set EP3 OUT Stall 
                  break;
                #endif
                #ifdef EP2_IN_callback
                case 0x82:
                  UEP2_CTRL = UEP2_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;// Set EP2 IN STALL 
                  break;
                #endif
                #ifdef EP2_OUT_callback
                case 0x02:
                  UEP2_CTRL = UEP2_CTRL & (~bUEP_R_TOG) | UEP_R_RES_STALL;// Set EP2 OUT Stall 
                  break;
                #endif
                #ifdef EP1_IN_callback
                case 0x81:
                  UEP1_CTRL = UEP1_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;// Set EP1 IN STALL 
                  break;
                #endif
                #ifdef EP1_OUT_callback
                case 0x01:
                  UEP1_CTRL = UEP1_CTRL & (~bUEP_R_TOG) | UEP_R_RES_STALL;// Set EP1 OUT Stall
                  break;
                #endif
                default:
                  len = 0xFF;               // failed
                  break;
              }
            }
            else len = 0xFF;                // failed
          }
          else len = 0xFF;                  // failed
          break;

        case USB_GET_STATUS:
          EP0_buffer[0] = 0x00;
          EP0_buffer[1] = 0x00;
          if(SetupLen >= 2) len = 2;
          else len = SetupLen;
          break;

        default:
          len = 0xff;                       // failed
          break;
      }
    }
  }
  else len = 0xff;                          // wrong packet length

  if(len == 0xff) {
    SetupReq = 0xFF;
    UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL;//STALL
  }
  else if(len <= EP0_SIZE) {      // Tx data to host or send 0-length packet
    UEP0_T_LEN = len;
    UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;// Expect DATA1, Answer ACK
  }
  else {
    UEP0_T_LEN = 0;  // Tx data to host or send 0-length packet
    UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;// Expect DATA1, Answer ACK
  }
}

void USB_EP0_IN(void) {
  uint8_t len;
  switch(SetupReq) {

    case USB_GET_DESCRIPTOR:
      len = SetupLen >= EP0_SIZE ? EP0_SIZE : SetupLen;
      USB_EP0_copyDescr(len);                     // copy descriptor to Ep0                                
      SetupLen  -= len;
      pDescr    += len;
      UEP0_T_LEN = len;
      UEP0_CTRL ^= bUEP_T_TOG;                    // switch between DATA0 and DATA1
      break;

    case USB_SET_ADDRESS:
      USB_DEV_AD = USB_DEV_AD & bUDA_GP_BIT | SetupLen;
      UEP0_CTRL  = UEP_R_RES_ACK | UEP_T_RES_NAK;
      break;

    default:
      UEP0_T_LEN = 0;                             // end of transaction
      UEP0_CTRL  = UEP_R_RES_ACK | UEP_T_RES_NAK;
      break;
  }
}

void USB_EP0_OUT(void) {
  UEP0_T_LEN = 0;
  UEP0_CTRL |= UEP_R_RES_ACK | UEP_T_RES_NAK;     // respond Nak
}

// ===================================================================================
// USB Interrupt Service Routine
// ===================================================================================

#pragma save
#pragma nooverlay
void USB_interrupt(void) {   // inline not really working in multiple files in SDCC
  if(UIF_TRANSFER) {
    // Dispatch to service functions
    uint8_t callIndex = USB_INT_ST & MASK_UIS_ENDP;
    switch (USB_INT_ST & MASK_UIS_TOKEN) {
      case UIS_TOKEN_OUT:
        switch (callIndex) {
          case 0: EP0_OUT_callback(); break;
          #ifdef EP1_OUT_callback
          case 1: EP1_OUT_callback(); break;
          #endif
          #ifdef EP2_OUT_callback
          case 2: EP2_OUT_callback(); break;
          #endif
          #ifdef EP3_OUT_callback
          case 3: EP3_OUT_callback(); break;
          #endif
          #ifdef EP4_OUT_callback
          case 4: EP4_OUT_callback(); break;
          #endif
          default: break;
        }
        break;
      case UIS_TOKEN_SOF:
        switch (callIndex) {
          #ifdef EP0_SOF_callback
          case 0: EP0_SOF_callback(); break;
          #endif
          #ifdef EP1_SOF_callback
          case 1: EP1_SOF_callback(); break;
          #endif
          #ifdef EP2_SOF_callback
          case 2: EP2_SOF_callback(); break;
          #endif
          #ifdef EP3_SOF_callback
          case 3: EP3_SOF_callback(); break;
          #endif
          #ifdef EP4_SOF_callback
          case 4: EP4_SOF_callback(); break;
          #endif
          default: break;
        }
        break;
      case UIS_TOKEN_IN:
        switch (callIndex) {
          case 0: EP0_IN_callback(); break;
          #ifdef EP1_IN_callback
          case 1: EP1_IN_callback(); break;
          #endif
          #ifdef EP2_IN_callback
          case 2: EP2_IN_callback(); break;
          #endif
          #ifdef EP3_IN_callback
          case 3: EP3_IN_callback(); break;
          #endif
          #ifdef EP4_IN_callback
          case 4: EP4_IN_callback(); break;
          #endif
          default: break;
        }
        break;
      case UIS_TOKEN_SETUP:
        switch (callIndex) {
          case 0: EP0_SETUP_callback(); break;
          #ifdef EP1_SETUP_callback
          case 1: EP1_SETUP_callback(); break;
          #endif
          #ifdef EP2_SETUP_callback
          case 2: EP2_SETUP_callback(); break;
          #endif
          #ifdef EP3_SETUP_callback
          case 3: EP3_SETUP_callback(); break;
          #endif
          #ifdef EP4_SETUP_callback
          case 4: EP4_SETUP_callback(); break;
          #endif
          default: break;
        }
        break;
    }
    UIF_TRANSFER = 0;                       // clear interrupt flag
  }
    
  // Device mode USB bus reset
  if(UIF_BUS_RST) {
    UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;

    #ifdef USB_RESET_handler
    USB_RESET_handler();                    // custom reset handler
    #endif

    USB_DEV_AD   = 0x00;
    UIF_SUSPEND  = 0;
    UIF_TRANSFER = 0;
    UIF_BUS_RST  = 0;                       // clear interrupt flag
  }
    
  // USB bus suspend / wake up
  if (UIF_SUSPEND) {
    UIF_SUSPEND = 0;
    if ( !(USB_MIS_ST & bUMS_SUSPEND) ) USB_INT_FG = 0xFF;  // clear interrupt flag
  }
}
#pragma restore

// ===================================================================================
// USB Init Function
// ===================================================================================

void USB_init(void) {
  USB_CTRL    = bUC_DEV_PU_EN               // USB internal pull-up enable
              | bUC_INT_BUSY                // Return NAK if USB INT flag not clear
              | bUC_DMA_EN;                 // DMA enable
  UDEV_CTRL   = bUD_PD_DIS                  // Disable UDP/UDM pulldown resistor
              | bUD_PORT_EN;                // Enable port, full-speed

  #if F_CPU < 12000000                      // Set low-speed mode if SysFreq < 12 MHz
  USB_CTRL   |= bUC_LOW_SPEED;
  UDEV_CTRL  |= bUD_LOW_SPEED;
  #endif

  UEP0_DMA    = EP0_ADDR;                   // EP0 data transfer address
  UEP0_CTRL   = UEP_R_RES_ACK               // EP0 Manual flip, OUT transaction returns ACK
              | UEP_T_RES_NAK;              // EP0 IN transaction returns NAK

  #ifdef USB_INIT_handler
  USB_INIT_handler();                       // Custom EP init handler
  #endif

  USB_INT_EN |= bUIE_SUSPEND                // Enable device hang interrupt
              | bUIE_TRANSFER               // Enable USB transfer completion interrupt
              | bUIE_BUS_RST;               // Enable device mode USB bus reset interrupt

  USB_INT_FG |= 0x1F;                       // Clear interrupt flag
  IE_USB      = 1;                          // Enable USB interrupt
  EA          = 1;                          // Enable global interrupts

  UEP0_T_LEN  = 0;                          // Must be zero at start
}
