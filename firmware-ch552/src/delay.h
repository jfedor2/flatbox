// ===================================================================================
// Delay Functions for CH551, CH552 and CH554
// ===================================================================================

#pragma once
#include <stdint.h>

void DLY_us(uint16_t n);   // delay in units of us
void DLY_ms(uint16_t n);   // delay in units of ms

// Delay clock cycles (max. 1039)
// (need to find a smarter way...)
#define DLY_cycles(n)               \
  (n ==  1 ? (_delay_cycles_1())  : \
  (n ==  2 ? (_delay_cycles_2())  : \
  (n ==  3 ? (_delay_cycles_3())  : \
  (n ==  4 ? (_delay_cycles_4())  : \
  (n ==  5 ? (_delay_cycles_5())  : \
  (n ==  6 ? (_delay_cycles_6())  : \
  (n ==  7 ? (_delay_cycles_7())  : \
  (n ==  8 ? (_delay_cycles_8())  : \
  (n ==  9 ? (_delay_cycles_9())  : \
  (n == 10 ? (_delay_cycles_10()) : \
  (n == 11 ? (_delay_cycles_11()) : \
  (n == 12 ? (_delay_cycles_12()) : \
  (n == 13 ? (_delay_cycles_13()) : \
  (n == 14 ? (_delay_cycles_14()) : \
  (n == 15 ? (_delay_cycles_15()) : \
  (n == 16 ? (_delay_cycles_16()) : \
  (n == 17 ? (_delay_cycles_17()) : \
  (n == 18 ? (_delay_cycles_18()) : \
  (n == 19 ? (_delay_cycles_19()) : \
  ((n-20)%4 == 0 ? _delay_more_cycles(((n-20)/4)+1)   : \
  ((n-20)%4 == 1 ? _delay_more_cycles_1(((n-20)/4)+1) : \
  ((n-20)%4 == 2 ? _delay_more_cycles_2(((n-20)/4)+1) : \
  ((n-20)%4 == 3 ? _delay_more_cycles_3(((n-20)/4)+1) : \
(0))))))))))))))))))))))))

#define _delay_less_cycles(n) _delay_cycles_##n()

void _delay_more_cycles(uint8_t n);

inline void _delay_cycles_1(void) {
  __asm__("nop");
}

inline void _delay_cycles_2(void) {
  _delay_cycles_1();
  _delay_cycles_1();
}

inline void _delay_cycles_3(void) {
  _delay_cycles_2();
  _delay_cycles_1();
}

inline void _delay_cycles_4(void) {
  _delay_cycles_3();
  _delay_cycles_1();
}

inline void _delay_cycles_5(void) {
  _delay_cycles_4();
  _delay_cycles_1();
}

inline void _delay_cycles_6(void) {
  _delay_cycles_5();
  _delay_cycles_1();
}

inline void _delay_cycles_7(void) {
  _delay_cycles_6();
  _delay_cycles_1();
}

inline void _delay_cycles_8(void) {
  _delay_cycles_7();
  _delay_cycles_1();
}

inline void _delay_cycles_9(void) {
  _delay_cycles_8();
  _delay_cycles_1();
}

inline void _delay_cycles_10(void) {
  _delay_cycles_9();
  _delay_cycles_1();
}

inline void _delay_cycles_11(void) {
  _delay_cycles_10();
  _delay_cycles_1();
}

inline void _delay_cycles_12(void) {
  __asm
    push a
    push b
    div  ab
    pop  b
    pop  a
  __endasm;
}

inline void _delay_cycles_13(void) {
  _delay_cycles_12();
  _delay_cycles_1();
}

inline void _delay_cycles_14(void) {
  _delay_cycles_12();
  _delay_cycles_2();
}

inline void _delay_cycles_15(void) {
  _delay_cycles_12();
  _delay_cycles_3();
}

inline void _delay_cycles_16(void) {
  __asm
    push a
    push b
    div  ab
    div  ab
    pop  b
    pop  a
  __endasm;
}

inline void _delay_cycles_17(void) {
  _delay_cycles_16();
  _delay_cycles_1();
}

inline void _delay_cycles_18(void) {
  _delay_cycles_16();
  _delay_cycles_2();
}

inline void _delay_cycles_19(void) {
  _delay_cycles_16();
  _delay_cycles_3();
}

inline void _delay_more_cycles_1(uint8_t n) {
  _delay_more_cycles(n);
  _delay_cycles_1();
}

inline void _delay_more_cycles_2(uint8_t n) {
  _delay_more_cycles(n);
  _delay_cycles_2();
}

inline void _delay_more_cycles_3(uint8_t n) {
  _delay_more_cycles(n);
  _delay_cycles_3();
}
