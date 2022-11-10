/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Jacek Fedorynski
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"

#include "hardware/gpio.h"

int stickMode = 0;              // 0 = dpad, 1 = left stick

// These IDs are bogus. If you want to distribute any hardware using this,
// you will have to get real ones.
#define USB_VID 0xCAFE
#define USB_PID 0xBABA

// Uncomment the appropriate line to match your board revision

#define REV4
//#define REV5

#ifdef REV4

#define PIN_UP        16
#define PIN_DOWN      10
#define PIN_LEFT      9
#define PIN_RIGHT     11
#define PIN_CROSS     19
#define PIN_CIRCLE    24
#define PIN_TRIANGLE  25
#define PIN_SQUARE    18
#define PIN_L1        29
#define PIN_L2        28
#define PIN_R1        27
#define PIN_R2        26
#define PIN_SELECT    3
#define PIN_START     1
#define PIN_L3        6
#define PIN_R3        4
#define PIN_PS        2

#endif

#ifdef REV5

#define PIN_UP        10
#define PIN_DOWN      12
#define PIN_LEFT      13
#define PIN_RIGHT     11
#define PIN_CROSS     9
#define PIN_CIRCLE    7
#define PIN_TRIANGLE  6
#define PIN_SQUARE    8
#define PIN_L1        2
#define PIN_L2        3
#define PIN_R1        4
#define PIN_R2        5
#define PIN_SELECT    27
#define PIN_START     29
#define PIN_L3        14
#define PIN_R3        26
#define PIN_PS        28

#endif

uint32_t pin_mask = 1 << PIN_UP | 1 << PIN_DOWN | 1 << PIN_LEFT | 1 << PIN_RIGHT | 1 << PIN_CROSS | 1 << PIN_CIRCLE | 1 << PIN_TRIANGLE | 1 << PIN_SQUARE | 1 << PIN_L1 | 1 << PIN_L2 | 1 << PIN_R1 | 1 << PIN_R2 | 1 << PIN_SELECT | 1 << PIN_START | 1 << PIN_L3 | 1 << PIN_R3 | 1 << PIN_PS;

tusb_desc_device_t const desc_device = {
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor = USB_VID,
    .idProduct = USB_PID,
    .bcdDevice = 0x0100,

    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x00,

    .bNumConfigurations = 0x01
};

// HID report descriptor taken from a HORI Fighting Stick V3
// with feature and output bits omitted
// works out of the box with PC and PS3
// as dumped by usbhid-dump and parsed by https://eleccelerator.com/usbdescreqparser/
uint8_t const desc_hid_report[] = {
    0x05, 0x01,                 // Usage Page (Generic Desktop Ctrls)
    0x09, 0x05,                 // Usage (Game Pad)
    0xA1, 0x01,                 // Collection (Application)
    0x15, 0x00,                 //   Logical Minimum (0)
    0x25, 0x01,                 //   Logical Maximum (1)
    0x35, 0x00,                 //   Physical Minimum (0)
    0x45, 0x01,                 //   Physical Maximum (1)
    0x75, 0x01,                 //   Report Size (1)
    0x95, 0x0D,                 //   Report Count (13)
    0x05, 0x09,                 //   Usage Page (Button)
    0x19, 0x01,                 //   Usage Minimum (0x01)
    0x29, 0x0D,                 //   Usage Maximum (0x0D)
    0x81, 0x02,                 //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x03,                 //   Report Count (3)
    0x81, 0x01,                 //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,                 //   Usage Page (Generic Desktop Ctrls)
    0x25, 0x07,                 //   Logical Maximum (7)
    0x46, 0x3B, 0x01,           //   Physical Maximum (315)
    0x75, 0x04,                 //   Report Size (4)
    0x95, 0x01,                 //   Report Count (1)
    0x65, 0x14,                 //   Unit (System: English Rotation, Length: Centimeter)
    0x09, 0x39,                 //   Usage (Hat switch)
    0x81, 0x42,                 //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
    0x65, 0x00,                 //   Unit (None)
    0x95, 0x01,                 //   Report Count (1)
    0x81, 0x01,                 //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x26, 0xFF, 0x00,           //   Logical Maximum (255)
    0x46, 0xFF, 0x00,           //   Physical Maximum (255)
    0x09, 0x30,                 //   Usage (X)
    0x09, 0x31,                 //   Usage (Y)
    0x09, 0x32,                 //   Usage (Z)
    0x09, 0x35,                 //   Usage (Rz)
    0x75, 0x08,                 //   Report Size (8)
    0x95, 0x04,                 //   Report Count (4)
    0x81, 0x02,                 //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x06, 0x00, 0xFF,           //   Usage Page (Vendor Defined 0xFF00)
    0x09, 0x20,                 //   Usage (0x20)
    0x09, 0x21,                 //   Usage (0x21)
    0x09, 0x22,                 //   Usage (0x22)
    0x09, 0x23,                 //   Usage (0x23)
    0x09, 0x24,                 //   Usage (0x24)
    0x09, 0x25,                 //   Usage (0x25)
    0x09, 0x26,                 //   Usage (0x26)
    0x09, 0x27,                 //   Usage (0x27)
    0x09, 0x28,                 //   Usage (0x28)
    0x09, 0x29,                 //   Usage (0x29)
    0x09, 0x2A,                 //   Usage (0x2A)
    0x09, 0x2B,                 //   Usage (0x2B)
    0x95, 0x0C,                 //   Report Count (12)
    0x81, 0x02,                 //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
/*
    0x0A, 0x21, 0x26,           //   Usage (0x2621)
    0x95, 0x08,                 //   Report Count (8)
    0xB1, 0x02,                 //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x0A, 0x21, 0x26,           //   Usage (0x2621)
    0x91, 0x02,                 //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
*/
    0x26, 0xFF, 0x03,           //   Logical Maximum (1023)
    0x46, 0xFF, 0x03,           //   Physical Maximum (1023)
    0x09, 0x2C,                 //   Usage (0x2C)
    0x09, 0x2D,                 //   Usage (0x2D)
    0x09, 0x2E,                 //   Usage (0x2E)
    0x09, 0x2F,                 //   Usage (0x2F)
    0x75, 0x10,                 //   Report Size (16)
    0x95, 0x04,                 //   Report Count (4)
    0x81, 0x02,                 //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,                       // End Collection
};

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)
#define EPNUM_HID 0x81

uint8_t const desc_configuration[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, CONFIG_TOTAL_LEN, 0, 100),

    // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
    TUD_HID_DESCRIPTOR(0, 0, HID_ITF_PROTOCOL_NONE, sizeof(desc_hid_report), EPNUM_HID, CFG_TUD_HID_EP_BUFSIZE, 1)
};

char const *string_desc_arr[] = {
    (const char[]) {0x09, 0x04},        // 0: is supported language is English (0x0409)
    "Flatbox",                          // 1: Manufacturer
#ifdef REV4
    "Flatbox rev4",                     // 2: Product
#endif
#ifdef REV5
    "Flatbox rev5",                     // 2: Product
#endif
};

// HID report
typedef struct __attribute__ ((packed)) {
    uint16_t buttons;           // bits: 0 = square, 1 = cross, 2 = circle, 3 = triangle,
                                // 4 = L1, 5 = R1, 6 = L2, 7 = R2, 8 = select, 9 = start,
                                // 10 = L3, 11 = R3, 12 = PS
    uint8_t dpadHat;            // 0 = up, 1 = up/right, 2 = right etc., 0x0f = neutral
    uint8_t leftStickXAxis;
    uint8_t leftStickYAxis;
    uint8_t rightStickXAxis;
    uint8_t rightStickYAxis;
    uint8_t dpadRightAxis;
    uint8_t dpadLeftAxis;
    uint8_t dpadUpAxis;
    uint8_t dpadDownAxis;
    uint8_t triangleAxis;
    uint8_t circleAxis;
    uint8_t crossAxis;
    uint8_t squareAxis;
    uint8_t L1Axis;
    uint8_t L2Axis;
    uint8_t R1Axis;
    uint8_t R2Axis;
    uint16_t accelerometerXAxis;        // 10 bits (these are guesses BTW)
    uint16_t accelerometerYAxis;        // 10 bits
    uint16_t accelerometerZAxis;        // 10 bits
    uint16_t gyroscopeAxis;             // 10 bits
} hid_report_t;

hid_report_t report;
hid_report_t prevReport;

void dpad(bool up, bool down, bool left, bool right) {
    // SOCD: up+down=up, left+right=neutral seems to be the standard
    if (up && down) {
        down = false;
        // uncomment this instead if you want up+down=neutral:
        //up = down = false;
    }
    if (left && right) {
        left = right = false;
    }

    switch (stickMode) {
    case 0:
        if (up && !right && !left)
            report.dpadHat = 0;
        else if (up && right)
            report.dpadHat = 1;
        else if (right && !up && !down)
            report.dpadHat = 2;
        else if (right && down)
            report.dpadHat = 3;
        else if (down && !right && !left)
            report.dpadHat = 4;
        else if (down && left)
            report.dpadHat = 5;
        else if (left && !down && !up)
            report.dpadHat = 6;
        else if (left && up)
            report.dpadHat = 7;
        else
            report.dpadHat = 0x0f;

        report.dpadRightAxis = right ? 0xff : 0x00;
        report.dpadLeftAxis = left ? 0xff : 0x00;
        report.dpadUpAxis = up ? 0xff : 0x00;
        report.dpadDownAxis = down ? 0xff : 0x00;
        break;
    case 1:
        report.leftStickXAxis = left ? 0x00 : (right ? 0xFF : 0x80);
        report.leftStickYAxis = up ? 0x00 : (down ? 0xFF : 0x80);
        break;
    }
}

void send_hid_report() {
    if (!tud_hid_ready()) {
        return;
    }

    if (memcmp(&prevReport, &report, sizeof(report))) {
        tud_hid_report(0, &report, sizeof(report));
        memcpy(&prevReport, &report, sizeof(report));
    }
}

void hid_task(void) {
    uint32_t pins = ~gpio_get_all() & pin_mask;

    report.buttons = 0x00;
    report.triangleAxis = 0x00;
    report.circleAxis = 0x00;
    report.crossAxis = 0x00;
    report.squareAxis = 0x00;
    report.L1Axis = 0x00;
    report.L2Axis = 0x00;
    report.R1Axis = 0x00;
    report.R2Axis = 0x00;

    dpad(pins & (1 << PIN_UP),
         pins & (1 << PIN_DOWN),
         pins & (1 << PIN_LEFT),
         pins & (1 << PIN_RIGHT));

    if (pins & (1 << PIN_SQUARE)) {
        report.buttons |= 1 << 0;
        report.squareAxis = 0xff;
    }
    if (pins & (1 << PIN_CROSS)) {
        report.buttons |= 1 << 1;
        report.crossAxis = 0xff;
    }
    if (pins & (1 << PIN_CIRCLE)) {
        report.buttons |= 1 << 2;
        report.circleAxis = 0xff;
    }
    if (pins & (1 << PIN_TRIANGLE)) {
        report.buttons |= 1 << 3;
        report.triangleAxis = 0xff;
    }
    if (pins & (1 << PIN_L1)) {
        report.buttons |= 1 << 4;
        report.L1Axis = 0xff;
    }
    if (pins & (1 << PIN_R1)) {
        report.buttons |= 1 << 5;
        report.R1Axis = 0xff;
    }
    if (pins & (1 << PIN_L2)) {
        report.buttons |= 1 << 6;
        report.L2Axis = 0xff;
    }
    if (pins & (1 << PIN_R2)) {
        report.buttons |= 1 << 7;
        report.R2Axis = 0xff;
    }
    if (pins & (1 << PIN_SELECT)) {
        report.buttons |= 1 << 8;
    }
    if (pins & (1 << PIN_START)) {
        report.buttons |= 1 << 9;
    }
    if (pins & (1 << PIN_L3)) {
        report.buttons |= 1 << 10;
    }
    if (pins & (1 << PIN_R3)) {
        report.buttons |= 1 << 11;
    }
    if (pins & (1 << PIN_PS)) {
        report.buttons |= 1 << 12;
    }

    send_hid_report();
}

void pin_init(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
}

void pins_init(void) {
    pin_init(PIN_UP);
    pin_init(PIN_DOWN);
    pin_init(PIN_LEFT);
    pin_init(PIN_RIGHT);
    pin_init(PIN_CROSS);
    pin_init(PIN_CIRCLE);
    pin_init(PIN_TRIANGLE);
    pin_init(PIN_SQUARE);
    pin_init(PIN_L1);
    pin_init(PIN_L2);
    pin_init(PIN_R1);
    pin_init(PIN_R2);
    pin_init(PIN_SELECT);
    pin_init(PIN_START);
    pin_init(PIN_L3);
    pin_init(PIN_R3);
    pin_init(PIN_PS);

    // if left is held when plugged in, switch to left stick emulation mode
    if (!gpio_get(PIN_LEFT)) {
        stickMode = 1;
    }
}

void report_init(void) {
    memset(&report, 0, sizeof(report));
    report.dpadHat = 0x0f;
    report.leftStickXAxis = 0x80;
    report.leftStickYAxis = 0x80;
    report.rightStickXAxis = 0x80;
    report.rightStickYAxis = 0x80;
    report.accelerometerXAxis = 0x0200; // not sure why 0x02, but that's what HORI Fighting Stick V3 sends
    report.accelerometerYAxis = 0x0200;
    report.accelerometerZAxis = 0x0200;
    memcpy(&prevReport, &report, sizeof(report));
}

int main(void) {
    board_init();
    pins_init();
    report_init();
    tusb_init();

    while (1) {
        tud_task();             // tinyusb device task
        hid_task();
    }

    return 0;
}

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const *tud_descriptor_device_cb(void) {
    return (uint8_t const *) &desc_device;
}

// Invoked when received GET HID REPORT DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const *tud_hid_descriptor_report_cb(uint8_t itf) {
    return desc_hid_report;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t * buffer, uint16_t reqlen) {
    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
}

// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const *tud_descriptor_configuration_cb(uint8_t index) {
    return desc_configuration;
}

static uint16_t _desc_str[32];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    uint8_t chr_count;

    if (index == 0) {
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
    } else {
        // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

        if (!(index < sizeof(string_desc_arr) / sizeof(string_desc_arr[0])))
            return NULL;

        const char *str = string_desc_arr[index];

        // Cap at max char
        chr_count = strlen(str);
        if (chr_count > 31)
            chr_count = 31;

        // Convert ASCII string into UTF-16
        for (uint8_t i = 0; i < chr_count; i++) {
            _desc_str[1 + i] = str[i];
        }
    }

    // first byte is length (including header), second byte is string type
    _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);

    return _desc_str;
}
