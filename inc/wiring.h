#ifndef Wiring_h
#define Wiring_h

#include <stdlib.h>
#include "binary.h"
#include <inttypes.h>
#include <stdbool.h>
#include "wiring_digital.h"

#ifdef __cplusplus
extern "C"{
#endif

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define DEFAULT 1
#define EXTERNAL 0

/* undefine stdlib's abs if encountered */
#ifdef abs
#undef abs
#endif

#define interrupts()
#define noInterrupts()

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration);
void noTone(uint8_t _pin);
void toneNonBlocking(uint8_t _pin, unsigned int frequency, unsigned long duration);

typedef unsigned int word;
typedef uint8_t boolean;
typedef uint8_t byte;

void init(void);
void unexport_pin(uint8_t pin);

unsigned long millis(void);
unsigned long long micros(void);
void delay(unsigned long);
void delayMicroseconds(unsigned int us);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

void setup(void);
void loop(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
