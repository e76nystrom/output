#if !defined(INCLUDE)

#include <Arduino.h>
#include <stdio.h>
#include "config.h"
#include "struct.h"
#include "serial.h"

#define EXT
#define EXTC
#endif

#ifdef TCCR2A

EXTC void initTimer2();
EXTC void showTimer2();
#if 0
EXTC void readTimer2();
EXTC void clrTimer2();
#endif

#if !defined(INCLUDE)

void initTimer2()
{
 // stop timer
 TCCR2B = 0;
 // mode 0 normal operation
 TCCR2A = 0;
#if 0				// mode 2
 // ctc operation top set by ocra
 TCCR2A = _BV(WGM21);
 TCNT2 = 0;
 // 1 ms per rollover 250 * 4 usec
 OCR2A = 250 - 1;
#endif
 // clear output compare a
 OCR2A = 0;
 // clear output compare b
 OCR2B = 0;
 // enable overflow interrupt
 TIMSK2 = _BV(TOIE2);
 // clear flag register
 TIFR2 =  _BV(TOV2);
 // clock from internal clock
 ASSR = 0;
 // start timer
 // prescale by 64 4 usec per count
 TCCR2B = _BV(CS22);
}

#if CONSOLE
void showTimer2()
{
 printf(F0("TCCR2A %02x TCCR2B %02x TCNT2 %02x TIMSK2 %02x TIFR2 %02x\n"),
	TCCR2A, TCCR2B, TCNT2, TIMSK2, TIFR2);
 printf(F0("OCR2A %02x OCR2B %02x\n"), OCR2A, OCR2B);
 printf(F0("ASSR %02x GTCCR %02x\n"), ASSR, GTCCR);
}
#endif

#endif

#endif
