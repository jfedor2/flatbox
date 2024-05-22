// Derived from https://github.com/wagiminator/CH552-MouseWiggler
// License: http://creativecommons.org/licenses/by-sa/3.0/

#include <string.h>

#include "src/delay.h"
#include "src/gpio.h"
#include "src/system.h"
#include "src/usb_hid.h"

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
    USB_interrupt();
}

struct report_t {
    uint16_t buttons;
    uint8_t dpad;
    uint8_t lx;
    uint8_t ly;
    uint8_t rx;
    uint8_t ry;
    uint8_t padding;
};

__xdata struct report_t report;
__xdata struct report_t prev_report;

uint8_t dpad_lut[] = { 0x0F, 0x06, 0x02, 0x0F, 0x00, 0x07, 0x01, 0x00, 0x04, 0x05, 0x03, 0x04, 0x0F, 0x06, 0x02, 0x0F };

void main(void) {
    CLK_config();  // configure system clock
    DLY_ms(10);    // wait for clock to settle
    HID_init();
    DLY_ms(500);
    WDT_start();  // watchdog

    PIN_input_PU(P11);
    PIN_input_PU(P31);
    PIN_input_PU(P30);
    PIN_input_PU(P33);
    PIN_input_PU(P12);
    PIN_input_PU(P35);
    PIN_input_PU(P13);
    PIN_input_PU(P34);
    PIN_input_PU(P14);
    PIN_input_PU(P32);
    PIN_input_PU(P15);
    PIN_input_PU(P17);
    PIN_input_PU(P10);
    PIN_input_PU(P16);

    memset(&report, 0, sizeof(report));
    report.dpad = 0x0F;
    report.lx = report.ly = report.rx = report.ry = 0x80;
    memcpy(&prev_report, &report, sizeof(report));
    while (1) {
        report.buttons = 0;
        report.buttons |= !PIN_read(P11) << 0;
        report.buttons |= !PIN_read(P31) << 1;
        report.buttons |= !PIN_read(P30) << 2;
        report.buttons |= !PIN_read(P33) << 3;
        report.buttons |= !PIN_read(P12) << 4;
        report.buttons |= !PIN_read(P35) << 5;
        report.buttons |= !PIN_read(P13) << 6;
        report.buttons |= !PIN_read(P34) << 7;
        report.buttons |= !PIN_read(P14) << 9;
        report.buttons |= !PIN_read(P32) << 12;
        uint8_t dpad = !PIN_read(P15) | (!PIN_read(P17) << 1) | (!PIN_read(P10) << 2) | (!PIN_read(P16) << 3);
        report.dpad = dpad_lut[dpad];
        if (memcmp(&report, &prev_report, sizeof(report)) != 0) {
            HID_sendReport((uint8_t*) &report, sizeof(report));
            memcpy(&prev_report, &report, sizeof(report));
        }
        WDT_reset();  // watchdog
    }
}
