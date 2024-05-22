// ===================================================================================
// USB HID Functions for CH551, CH552 and CH554
// ===================================================================================

#pragma once
#include <stdint.h>

void HID_init(void);                                      // setup USB-HID
void HID_sendReport(__xdata uint8_t* buf, uint8_t len);   // send HID report
