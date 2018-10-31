#if !defined(INCLUDE)

#include <Arduino.h>
#include <stdio.h>
#include "config.h"
#include "struct.h"
#include "serial.h"

#define EXTC
#define EXT
#endif

#if defined(TCCR4A) && !defined(TCCR4E)

EXTC void initTimer4(long uSec);
EXTC void pwm1Timer4(unsigned int duty);
EXTC void stopTimer4();

EXT unsigned char timer4Prescale;
EXT unsigned long timer4Period;

#if !defined(INCLUDE)

typedef struct
{
 unsigned char shift;
 unsigned char sel;
} T_TIMER, *P_TIMER;

T_TIMER tmr4Cfg[] =
{
 {0, _BV(CS40)},
 {3, _BV(CS41)},
 {3, _BV(CS41) | _BV(CS40)},
 {2, _BV(CS42)},
 {2, _BV(CS42) | _BV(CS40)}
};

#define T4_CFGLEN (sizeof(tmr4Cfg) / sizeof(T_TIMER))

void initTimer4(long uSec)
{
 T_SHORT_LONG cycles;
 cycles.l = (F_CPU * uSec) / 2000000;
 P_TIMER cfg = tmr4Cfg;
 unsigned char i;
 for (i = 0; i < T4_CFGLEN; i++)
 {
  cycles.l >>= cfg->shift;
#if CONSOLE
  printf(F0("cycles %08lx high %04x low %04x\n"),
	 cycles.l, cycles.high, cycles.low);
#endif
  if (cycles.high == 0)
  {
   break;
  }
  cfg++;
 }
 if (i == T4_CFGLEN)
 {
  timer4Period = 0xffff;
  timer4Prescale = _BV(CS42) | _BV(CS40);
 }
 else
 {
  timer4Period = cycles.low;
  timer4Prescale = cfg->sel;
 }

 // stop timer, clear wavefrom gen bits, clear input capture bits
 TCCR4B = 0;
 // disable all pwm output and clear waveform generator bits
 TCCR4A = 0;
 // clear counter
 TCNT4 = 0;
#if defined(T4_PWM_A_Pin)
 // set mode 8, phase and frequency correct pwm, top ICR4
 TCCR4B = _BV(WGM43);
#else
 // set mode 12, counter timer on compare match, top ICR4
 TCCR4B = _BV(WGM43) | _BV(WGM42);
#endif
 // set cycle length
 ICR4 = cycles.low;
 // clear interrupt flags
 TIFR5 = _BV(ICF4) | _BV(OCF4C) | _BV(OCF4B) | _BV(OCF4A) | _BV(TOV4);
 // enable overflow interrrupt
 TIMSK4 = _BV(TOIE4);
 // set clock divider and enable clock
 TCCR4B &= ~(_BV(CS40) | _BV(CS41) | _BV(CS42));
 TCCR4B |= timer4Prescale;
}

#ifdef T4_PWM_A_Pin

void pwm1Timer4(unsigned int duty)
{
 unsigned long dutyCycle = timer4Period;
 dutyCycle *= duty;
 dutyCycle >>= 10;
 // enable output on pin 5 pe3
 T4_PWM_A_DDR |= T4_PWM_A_Mask;
 // DDRH |= _BV(PH3);
 // set pwm value
 OCR4A = dutyCycle;
 // turn on pwm, clear on up count, set on down count
 TCCR4A |= _BV(COM4A1);
 TIMSK4 |= _BV(OCIE4A);
#if CONSOLE
 printf(F0("DDRE %02x TCCR4A %02x OCR4A %02x\n"), DDRE, TCCR4A, OCR4A);
#endif
}

#else

void pwm1Timer4(unsigned int duty)
{}

#endif

void stopTimer4()
{
 // disable clock
 TCCR4B &= ~(_BV(CS40) | _BV(CS41) | _BV(CS42));
}

#endif
#endif
