#if !defined(INCLUDE)

#include <Arduino.h>
#include <stdio.h>
#include "config.h"
#include "struct.h"
#include "serial.h"

#define EXTC
#define EXT
#endif

#if defined(TCCR5A) && !defined(TCCR5E)

EXTC void initTimer5(long uSec);
EXTC void pwm1Timer5(unsigned int duty);
EXTC void stopTimer5();

EXT unsigned char timer5Prescale;
EXT unsigned long timer5Period;

#if !defined(INCLUDE)

typedef struct
{
 unsigned char shift;
 unsigned char sel;
} T_TIMER, *P_TIMER;

T_TIMER tmr5Cfg[] =
{
 {0, _BV(CS50)},
 {3, _BV(CS51)},
 {3, _BV(CS51) | _BV(CS50)},
 {2, _BV(CS52)},
 {2, _BV(CS52) | _BV(CS50)}
};

#define T5_CFGLEN (sizeof(tmr5Cfg) / sizeof(T_TIMER))

void initTimer5(long uSec)
{
 T_SHORT_LONG cycles;
 cycles.l = (F_CPU * uSec) / 2000000;
 P_TIMER cfg = tmr5Cfg;
 unsigned char i;
 for (i = 0; i < T5_CFGLEN; i++)
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
 if (i == T5_CFGLEN)
 {
  timer5Period = 0xffff;
  timer5Prescale = _BV(CS52) | _BV(CS50);
 }
 else
 {
  timer5Period = cycles.low;
  timer5Prescale = cfg->sel;
 }

 // stop timer, clear wavefrom gen bits, clear input capture bits
 TCCR5B = 0;
 // disable all pwm output and clear waveform generator bits
 TCCR5A = 0;
 // clear counter
 TCNT5 = 0;
#if defined(T5_PWM_B_Pin)
 // set mode 8, phase and frequency correct pwm, top ICR5
 TCCR5B = _BV(WGM53);
#else
 // set mode 12, counter timer on compare match, top ICR5
 TCCR5B = _BV(WGM53) | _BV(WGM52);
#endif	/* T%_PWM_B_PIN */
 // set cycle length
 ICR5 = cycles.low;
 // clear interrupt flags
 TIFR5 = _BV(ICF5) | _BV(OCF5C) | _BV(OCF5B) | _BV(OCF5A) | _BV(TOV5);
 // enable overflow interrrupt
 TIMSK5 = _BV(TOIE5);
 // set clock divider and enable clock
 TCCR5B &= ~(_BV(CS50) | _BV(CS51) | _BV(CS52));
 TCCR5B |= timer5Prescale;
}

#ifdef T5_PWM_A_Pin

void pwm1Timer5(unsigned int duty)
{
 unsigned long dutyCycle = timer5Period;
 dutyCycle *= duty;
 dutyCycle >>= 10;
 // enable output on pin 5 pe3
 T5_PWM_A_DDR |= T5_PWM_A_Mask;
 // DDRH |= _BV(PH3);
 // set pwm value
 OCR5A = dutyCycle;
 // turn on pwm, clear on up count, set on down count
 TCCR5A |= _BV(COM5A1);
 TIMSK5 |= _BV(OCIE5A);
#if CONSOLE
 printf(F0("DDRE %02x TCCR5A %02x OCR5A %02x\n"), DDRE, TCCR5A, OCR5A);
#endif
}

#else

void pwm1Timer5(unsigned int duty)
{}

#endif

void stopTimer5()
{
 // disable clock
 TCCR5B &= ~(_BV(CS50) | _BV(CS51) | _BV(CS52));
}

#endif
#endif
