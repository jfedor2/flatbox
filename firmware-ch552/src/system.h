// ===================================================================================
// Basic System Functions for CH551, CH552 and CH554                          * v1.3 *
// ===================================================================================
//
// Functions available:
// --------------------
// CLK_config()             set system clock frequency according to F_CPU
// CLK_external()           set external crystal as clock source
// CLK_internal()           set internal oscillator as clock source
//
// WDT_start()              start watchdog timer with full period
// WDT_stop()               stop watchdog timer
// WDT_reset()              reload watchdog timer with full period
// WDT_set(time)            reload watchdog timer with specified time in ms
// WDT_feed(value)          reload watchdog timer with specified value
//
// BOOT_now()               enter bootloader
// SLEEP_now()              put device into sleep
// RST_now()                perform software reset
//
// RST_keep(value)          keep this value after RESET
// RST_getKeep()            read the keeped value
// RST_wasWDT()             check if last RESET was caused by watchdog timer
// RST_wasPIN()             check if last RESET was caused by RST PIN
// RST_wasPWR()             check if last RESET was caused by power-on
// RST_wasSOFT()            check if last RESET was caused by software
//
// WAKE_enable(source)      enable wake-up from sleep source (sources see below)
// WAKE_disable(source)     disable wake-up from sleep source
// WAKE_all_disable()       disable all wake-up sources
//
// WAKE_USB_enable()        enable wake-up by USB event
// WAKE_RXD0_enable()       enable wake-up by RXD0 low level
// WAKE_RXD1_enable()       enable wake-up by RXD1 low level
// WAKE_P13_enable()        enable wake-up by pin P1.3 low level
// WAKE_P14_enable()        enable wake-up by pin P1.4 low level
// WAKE_P15_enable()        enable wake-up by pin P1.5 low level
// WAKE_RST_enable()        enable wake-up by pin RST high level
// WAKE_INT_enable()        enable wake-up by pin P3.2 edge or pin P3.3 low level
//
// WAKE_USB_disable()       disable wake-up by USB event
// WAKE_RXD0_disable()      disable wake-up by RXD0 low level
// WAKE_RXD1_disable()      disable wake-up by RXD1 low level
// WAKE_P13_disable()       disable wake-up by pin P1.3 low level
// WAKE_P14_disable()       disable wake-up by pin P1.4 low level
// WAKE_P15_disable()       disable wake-up by pin P1.5 low level
// WAKE_RST_disable()       disable wake-up by pin RST high level
// WAKE_INT_disable()       disable wake-up by pin P3.2 edge or pin P3.3 low level
//
// Wake-up from SLEEP sources:
// ---------------------------
// WAKE_USB                 wake-up by USB event
// WAKE_RXD0                wake-up by RXD0 low level
// WAKE_RXD1                wake-up by RXD1 low level
// WAKE_P13                 wake-up by pin P1.3 low level
// WAKE_P14                 wake-up by pin P1.4 low level
// WAKE_P15                 wake-up by pin P1.5 low level
// WAKE_RST                 wake-up by pin RST high level
// WAKE_INT                 wake-up by pin P3.2 edge or pin P3.3 low level
//
// 2023 by Stefan Wagner:   https://github.com/wagiminator

#pragma once
#include <stdint.h>
#include "ch554.h"

// ===================================================================================
// System Clock
// ===================================================================================
inline void CLK_config(void) {
  SAFE_MOD = 0x55;
  SAFE_MOD = 0xAA;                              // enter safe mode
  
  #if F_CPU == 32000000
    __asm__("orl _CLOCK_CFG, #0b00000111");     // 32MHz
  #elif F_CPU == 24000000
    __asm__("anl _CLOCK_CFG, #0b11111000");
    __asm__("orl _CLOCK_CFG, #0b00000110");     // 24MHz	
  #elif F_CPU == 16000000
    __asm__("anl _CLOCK_CFG, #0b11111000");
    __asm__("orl _CLOCK_CFG, #0b00000101");     // 16MHz	
  #elif F_CPU == 12000000
    __asm__("anl _CLOCK_CFG, #0b11111000");
    __asm__("orl _CLOCK_CFG, #0b00000100");     // 12MHz
  #elif F_CPU == 6000000
    __asm__("anl _CLOCK_CFG, #0b11111000");
    __asm__("orl _CLOCK_CFG, #0b00000011");     // 6MHz	
  #elif F_CPU == 3000000
    __asm__("anl _CLOCK_CFG, #0b11111000");
    __asm__("orl _CLOCK_CFG, #0b00000010");     // 3MHz	
  #elif F_CPU == 750000
    __asm__("anl _CLOCK_CFG, #0b11111000");
    __asm__("orl _CLOCK_CFG, #0b00000001");     // 750kHz	
  #elif F_CPU == 187500
    __asm__("anl _CLOCK_CFG, #0b11111000");     // 187.5kHz		
  #else
    #warning F_CPU invalid or not set
  #endif

  SAFE_MOD = 0x00;                              // terminate safe mode
}

inline void CLK_external(void) {
  SAFE_MOD = 0x55;
  SAFE_MOD = 0xAA;                              // enter safe mode
  CLOCK_CFG |=  bOSC_EN_XT;                     // enable external crystal
  CLOCK_CFG &= ~bOSC_EN_INT;                    // turn off internal oscillator
  SAFE_MOD = 0x00;                              // terminate safe mode
}

inline void CLK_inernal(void) {
  SAFE_MOD = 0x55;
  SAFE_MOD = 0xAA;                              // enter safe mode
  CLOCK_CFG |=  bOSC_EN_INT;                    // turn on internal oscillator
  CLOCK_CFG &= ~bOSC_EN_XT;                     // disable external crystal
  SAFE_MOD = 0x00;                              // terminate safe mode
}

// ===================================================================================
// Watchdog Timer
// ===================================================================================
#define WDT_reset()       WDOG_COUNT = 0
#define WDT_feed(value)   WDOG_COUNT = value
#define WDT_set(time)     WDOG_COUNT = (uint8_t)(256 - ((F_CPU / 1000) * time / 65536))

inline void WDT_start(void) {
  WDOG_COUNT  = 0;
  SAFE_MOD    = 0x55;
  SAFE_MOD    = 0xAA;
  GLOBAL_CFG |= bWDOG_EN;
  SAFE_MOD    = 0x00;
}

inline void WDT_stop(void) {
  SAFE_MOD    = 0x55;
  SAFE_MOD    = 0xAA; 
  GLOBAL_CFG &= ~bWDOG_EN;
  SAFE_MOD    = 0x00;
}

// ===================================================================================
// Reset
// ===================================================================================
#define RST_keep(value)   RESET_KEEP = value
#define RST_getKeep()     (RESET_KEEP)
#define RST_wasWDT()      ((PCON & MASK_RST_FLAG) == RST_FLAG_WDOG)
#define RST_wasPIN()      ((PCON & MASK_RST_FLAG) == RST_FLAG_PIN)
#define RST_wasPWR()      ((PCON & MASK_RST_FLAG) == RST_FLAG_POR)
#define RST_wasSOFT()     ((PCON & MASK_RST_FLAG) == RST_FLAG_SW)

inline void RST_now(void) {
  SAFE_MOD    = 0x55;
  SAFE_MOD    = 0xAA;
  GLOBAL_CFG |= bSW_RESET;
}

// ===================================================================================
// Bootloader
// ===================================================================================
inline void BOOT_now(void) {
  USB_CTRL = 0;
  EA       = 0;
  TMOD     = 0;
  __asm
    lcall #BOOT_LOAD_ADDR
  __endasm;
}

// ===================================================================================
// Sleep
// ===================================================================================
#define SLEEP_now()   PCON |= PD

#define WAKE_USB      bWAK_BY_USB     // wake-up by USB event
#define WAKE_RXD0     bWAK_RXD0_LO    // wake-up by RXD0 low level
#define WAKE_RXD1     bWAK_RXD1_LO    // wake-up by RXD1 low level
#define WAKE_P13      bWAK_P1_3_LO    // wake-up by pin P1.3 low level
#define WAKE_P14      bWAK_P1_4_LO    // wake-up by pin P1.4 low level
#define WAKE_P15      bWAK_P1_5_LO    // wake-up by pin P1.5 low level
#define WAKE_RST      bWAK_RST_HI     // wake-up by pin RST high level
#define WAKE_INT      bWAK_P3_2E_3L   // wake-up by pin P3.2 (INT0) edge or pin P3.3 (INT1) low level

#define WAKE_enable(source)     WAKE_CTRL |=  source
#define WAKE_disable(source)    WAKE_CTRL &= ~source
#define WAKE_all_disable()      WAKE_CTRL  =  0

#define WAKE_USB_enable()       WAKE_CTRL |=  bWAK_BY_USB
#define WAKE_RXD0_enable()      WAKE_CTRL |=  bWAK_RXD0_LO
#define WAKE_RXD1_enable()      WAKE_CTRL |=  bWAK_RXD1_LO
#define WAKE_P13_enable()       WAKE_CTRL |=  bWAK_P1_3_LO
#define WAKE_P14_enable()       WAKE_CTRL |=  bWAK_P1_4_LO
#define WAKE_P15_enable()       WAKE_CTRL |=  bWAK_P1_5_LO
#define WAKE_RST_enable()       WAKE_CTRL |=  bWAK_RST_HI
#define WAKE_INT_enable()       WAKE_CTRL |=  bWAK_P3_2E_3L

#define WAKE_USB_disable()      WAKE_CTRL &= ~bWAK_BY_USB
#define WAKE_RXD0_disable()     WAKE_CTRL &= ~bWAK_RXD0_LO
#define WAKE_RXD1_disable()     WAKE_CTRL &= ~bWAK_RXD1_LO
#define WAKE_P13_disable()      WAKE_CTRL &= ~bWAK_P1_3_LO
#define WAKE_P14_disable()      WAKE_CTRL &= ~bWAK_P1_4_LO
#define WAKE_P15_disable()      WAKE_CTRL &= ~bWAK_P1_5_LO
#define WAKE_RST_disable()      WAKE_CTRL &= ~bWAK_RST_HI
#define WAKE_INT_disable()      WAKE_CTRL &= ~bWAK_P3_2E_3L
