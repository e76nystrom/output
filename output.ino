/******************************************************************************/
#include <Arduino.h>
#include "config.h"
#include "serial.h"
#include "struct.h"
#include "timer1.h"
#include "timer2.h"
#include "timer3.h"
#include "timer4.h"

#define RESET_DEBOUNCE_TIME 20
#define PWM_INACTIVITY_TIME 500
#define CHARGE_PUMP_TIMEOUT 20
#define LED_BLINK_TIME 500

unsigned int dutyCycle1;
T_TIMER_CTL tmr1;

#ifdef TCCR2A
#if DEBUG
unsigned int isr2Counter;
#endif
#endif

#ifdef TCCR3A

T_TIMER_CTL tmr3;
long int period3;
unsigned int dutyCycle3;
#if DEBUG
unsigned int pwm3Counter;
unsigned int isr3Counter;
#endif

#endif /* TCC3RA */

#if defined(TCCR4A) && !defined(TCCR4E)

T_TIMER_CTL tmr4;
long int period4;
unsigned int dutyCycle4;
#if DEBUG
unsigned int isr4Counter;
unsigned int pwm4Counter;
#endif

#endif /* defined(TCCR4A) && !defined(TCCR4E) */

void showTimer0();
void showTimer(P_TIMER_CTL tmr);
void showPort(P_PORT port, const char *name);

extern volatile unsigned long timer0_millis;

uint16_t ledTime;		/* last led update time */

char pwmActive;			/* pwm active flag */
char readPwm;			/* read pwm state */
uint16_t lastPwmTime;		/* time of last pwm reading */
T_SHORT_LONG fDutyCycle;	/* pwm duty cycle calculation */
uint16_t pwmDutyCycle;		/* current duty cycle */
uint8_t pwmTimerHigh;
CHAR_INT pwmTimerCount;
volatile CHAR_INT pulseEnd;	/* end of pwm pulse */
volatile CHAR_INT pulseTime;	/* pwm time interval */
uint16_t pwmInterrupts;

char cpActive;			/* charge pump active */
uint16_t cpFail;		/* charge pump failure */
volatile uint16_t cpTime;	/* last charge pump time */
char wdEna;			/* enable watchdog signal */
char eStop;			/* e stop flag */
uint16_t lastResetTime;		/* last reset button time */
uint16_t cpInterrupts;

uint16_t intMillis();		/* short integer milliseconds */
void procLoop();		/* processing loop */
void procChargePump();		/* charge pump control */
void procEStop();		/* e stop control */
void procPWM();			/* spindle pwm control */
void procSpindle();		/* spindle switch control */
void eStopAction();		/* actions when in e stop */
void eStopSet();		/* set e stop condition */
void eStopClr();		/* clear e stop condition */
void stopAll();			/* set all outputs to stop */
#if INPUT_LOOP
void inputLoop();		/* input loop */
#endif

#if CP_DEBUG
char dbgCpEnable;
#endif

#if CONSOLE
void cmdLoop();			/* command loop */
#endif
void ctlStatus();		/* control status */

void setup()
{
#if CONSOLE
 initSerial(19200);
 puts(F0("\nstarting 0\n"));

#if DEBUG && defined(AVR_PROMICRO16)
 char delay = 10;
 uint16_t t0 = 0;
 while (1)
 {
  if ((intMillis() - t0) > 1000)
  {
   t0 = intMillis();
   printf(F0("\rstart in %2d "), delay);
   fflush(stdout);
   if (--delay <= 0)
    break;
  }
  if (DBGPORT.available())
  {
   delay = DBGPORT.read();
   break;
  }
 }
 newLine();
#endif /* DEBUG && defined(AVR_PROMICRO16) */
#endif /* CONSOLE */

 P_TIMER_CTL t = &tmr1;
 t->timer = (P_TMR) &TCCR1A;
 t->timsk = (uint8_t *) &TIMSK1;
 t->tifr = (uint8_t *) &TIFR1;
 t->aPort = (P_PORT) &OC1A_Port;
 t->aMask = OC1A_Mask;

#ifdef TCCR3A
 t = &tmr3;
 t->timer = (P_TMR) &TCCR3A;
 t->timsk = (uint8_t *) &TIMSK3;
 t->tifr = (uint8_t *) &TIFR3;
 t->aPort = (P_PORT) &OC3A_Port;
 t->aMask = OC3A_Mask;

#if SPINDLE_PWM_TEST
 period3 = 10000;
 dutyCycle3 = (1024 / 2) - 1;

 initTimer3(period3);
 pwm1Timer3(dutyCycle3);
#endif /* SPINDLE_PWM_TEST */

#if CONSOLE
 showTimer(&tmr3);
#endif
#endif /*TCCR3A */

#if defined(TCCR4A) && !defined(TCCR4E)
 t = &tmr4;
 t->timer = (P_TMR) &TCCR4A;
 t->timsk = (uint8_t *) &TIMSK4;
 t->tifr = (uint8_t *) &TIFR4;
 t->aPort = (P_PORT) &OC4A_Port;
 t->aMask = OC4A_Mask;

#if CHARGE_PUMP_TEST
 period4 = 500;
 dutyCycle4 = (1024 / 2) - 1;

 initTimer4(period4);		/* init charge pump */
 pwm1Timer4(dutyCycle4);	/* set duty cycle */
#endif /* CHARGE_PUMP_TEST */

#if CONSOLE
 showTimer(&tmr4);
#endif
#endif /* defined(TCCR4A) && !defined(TCCR4E) */

 pinConfig();

 dutyCycle1 = (1024 / 2) - 1;
 
 eStopSet();			/* put in e stop condition */

 cpActive = 0;			/* set charge pump to inactive */
 cpFail = 0;
 ledTime = 0;

 readPwm = 0;
 pwmActive = 0;

 pwmIntInit();			/* init pwm interrupt */
 chgPumpIntInit();		/* init charge pump interrupt */

#if TMR2_PWM_TIMER
 initTimer2();			/* init timer 2 pwm */
#if CONSOLE
 showTimer2();
#endif
#endif /* TMR2_PWM_TIMER */

#if TMR3_PWM_TIMER
 initTimer3();			/* init timer 3 pwm */
#if CONSOLE
 showTimer(&tmr3);
#endif
#endif /* TMR3_PWM_TIMER */

#if INPUT_TEST
 spFwdTClr();			/* clear simulated inputs */
 spRevTClr();
 eStopNcTClr();
 eStopNoTClr();
 eStopRstTClr();
#endif

 wDogClr();			/* clear watchdog output */
 stopAll();			/* stop everything */
 eStopSet();			/* start in e stop mode */
#ifdef PILOT_PIN
 pilotClr();			/* turn on pilot light */
#endif

#if CONSOLE
 puts(F0("C for command mode\n"));
 fflush(stdout);
#endif
}

void loop()
{
#if CONSOLE
 while (DBGPORT.available())
 {
  char ch = DBGPORT.read();
  if (ch == 'C')
  {
   while (DBGPORT.available())
    ch = DBGPORT.read();
   cmdLoop();
  }
 }
#endif /* CONSOLE */

#if INPUT_LOOP
 inputLoop();
#endif /* INPUT_LOOP */

 procLoop();

#if ledRead
 uint16_t curTime = intMillis();
 if ((curTime - ledTime) > LED_BLINK_TIME)
 {
  ledTime = curTime;
  if (ledRead())
   ledClr();
  else
   ledSet();
 }
#endif /* ledRead */
}

#if CONSOLE

#ifdef TCCR2A
void clrTimer2()
{
 TCCR2B = 0;			// stop timer
 pwmTimerHigh = 0;		// clear overflow
 TCNT2 = 0;			// clear counter
 TCCR2B = _BV(CS22);		// restart
}

void readTimer2()
{
 TCCR2B = 0;			// stop timer
 pwmTimerCount.hi = pwmTimerHigh; // read high part
 pwmTimerCount.lo = TCNT2;	// read low part
 TCCR2B = _BV(CS22);		// restart
}
#endif /* TCCR2A */

void cmdLoop()
{
 puts(F0("command loop\n"));
 while (1)
 {
  procLoop();
  if (DBGPORT.available())
  {
   char ch = DBGPORT.read();
   DBGPORT.write(ch);
   newLine();
   if (ch == 'x')		/* exit */
    break;
   else if (ch == 'P')		/* test pins */
   {
    if (query(&getnum, F1("pin number")))
    {
     pinMode(val, OUTPUT);
     char flag = 0;
     printf("testing...");
     fflush(stdout);
     while (1)
     {
      delay(10);
      digitalWrite(val, (flag == 0) ? LOW : HIGH);
      flag = !flag;
      if (DBGPORT.available())
      {
       ch = DBGPORT.read();
       if (ch == 3)
	break;
      }
     }
     newLine();
    }
   }
   else if (ch == 'i')		/* enable interrupts */
   {
    ch = query(F1("init charge pump: "));
    if (ch == 'y')
    {
     chgPumpIntInit();		/* init charge pump interrupt */
    }
    ch = query(F1("init pwm: "));
    if (ch == 'y')
    {
     pwmIntInit();		/* init pwm interrupt */
    }
#ifdef EICRB
    printf(F0("EICRA %02x EICRB %02X EIMSK %02x EIFR %02x\n"),
	   EICRA, EICRB, EIMSK, EIFR);
#else
    printf(F0("EICRA %02x EIMSK %02x EIFR %02x\n"),
	   EICRA, EIMSK, EIFR);
#endif
   }
   
#if INPUT_TEST			/* if testing inputs */
   else if (ch == 'e')		/* control e stop */
   {
    ch = query(F1("eStopNo [%d]: "), eStopNoIn());
    if (ch == '1')
     eStopNoTSet();
    else if (ch == '0')
     eStopNoTClr();
    ctlStatus();
   }
   else if (ch == 'r')		/* reset e stop */
   {
    ch = query(F1("eStopRst [%d]: "), eStopRstIn());
    if (ch == '1')
     eStopRstTSet();
    else if (ch == '0')
     eStopRstTClr();
    else if (ch == 'c')		/* autmotically clear e stop */
    {
     eStopNoTClr();
     eStopRstTSet();
     for (int i = 0; i < 5; i++)
     {
      procLoop();
      delay(RESET_DEBOUNCE_TIME + 1);
     }
     eStopRstTClr();
    }
    ctlStatus();
   }
   else if (ch == 'F')		/* spindle forward */
   {
    ch = query(F1("spFwd [%d]: "), spFwdIn());
    if (ch == '1')
     spFwdTSet();
    else if (ch == '0')
     spFwdTClr();
    ctlStatus();
   }
   else if (ch == 'R')		/* spindle reverse */
   {
    ch = query(F1("spRev [%d]: "), spRevIn());
    if (ch == '1')
     spRevTSet();
    else if (ch == '0')
     spRevTClr();
    ctlStatus();
   }
#endif /* INPUT_TEST */

   else if (ch == 't')		/* control bits, inputs, and outputs */
   {
    ctlStatus();
   }
   else if (ch == 'c')		/* charge pump status */
   {
    printf(F0("cpActive %d cpInterrupts %u cpFail %u cpTime %u\n"),
	   cpActive, cpInterrupts, cpFail, cpTime);
   }

#if CP_DEBUG
   else if (ch == 'C')
   {
    ch = query(F1("dbgCpEnable [%d]: "), dbgCpEnable);
    dbgCpEnable = (ch == '1');
    if (dbgCpEnable)
     cpTime = intMillis();
   }
#endif /* CP_DEBUG */

   else if (ch == '0')		/* timer 0 status */
   {
    showTimer0();
   }
   else if (ch == 'p')		/* pwm status */
   {
    printf(F0("pwmActive %d readPwm %d pulseEnd %u "
	      "pulseTime %u fDutyCycle %u fastPwm %d\n"),
	   pwmActive, readPwm, pulseEnd.w, pulseTime.w,
	   fDutyCycle.low, fastPwmRead());
    printf(F0("pwmInterrupts %u\n"), pwmInterrupts);
    if (pwmActive)
    {
     cli();
     unsigned int delta = ((P_SHORT_LONG) &timer0_millis)->low - lastPwmTime;
     sei();
     printf(F0("delta %u\n"), delta);
    }
   }
   else if (ch == '1')		/* control timer 1 fast pwm output */
   { 
    ch = query(F1("init: "));
    if (ch == 'y')
    {
     if (query(&getnum, F1("duty cycle [%d]: "), dutyCycle1))
     {
      dutyCycle1 = val;
     }
     initTimer1(dutyCycle1);
    }
    showTimer(&tmr1);
   }

#ifdef TCCR2A
   else if (ch == '2')		/* control timer 2 spindle pwm timer */
   {
    ch = query(F1("init: "));
    if (ch == 'y')
    {
#if 0
     if (query(&getnum, F1("duty cycle [%d]: "), dutyCycle))
     {
      dutyCycle = val;
     }
#endif
     initTimer2();
    }
    showTimer2();
#if DEBUG
    readTimer2();
    printf(F0("isrCounter %u pmwTimerCount %04x\n"),
	   isr2Counter, pwmTimerCount.w);
#endif
   }
#endif /* TCCR2A */

#ifdef TCCR3A
   else if (ch == '3')		/* control timer 3 spindle pwm test */
   {

#if TMR3_PWM_TIMER == 0		/* if timer 3 not used for spindle pwm */
    ch = query(F1("init: "));
    if (ch == 'y')
    {
     if (query(&getnum, F1("period [%ld] us: "), period3))
     {
      period3 = val;
     }
     if (period3 != 0)
     {
      if (query(&getnum, F1("duty cycle [%d]: "), dutyCycle3))
      {
       dutyCycle3 = val;
      }
      stopTimer3();
      isr3Counter = 0;
      pwm3Counter = 0;
      initTimer3(period3);
      pwm1Timer3(dutyCycle3);
     }
     else
     {
      pwm1Timer3(0);
      stopTimer3();
     }
    }
#endif /* TMR3_PWM_TIMER == 0 */
    
    showTimer(&tmr3);
#if DEBUG
    printf(F0("isrCounter %u pwmCounter %u\n"), isr3Counter, pwm3Counter);
#endif
   }
#endif /* TCCR3A */

#if defined(TCCR4A) && !defined(TCCR4E)
   else if (ch == '4')		/* control timer 4 charge pump test */
   {
    ch = query(F1("init: "));
    if (ch == 'y')
    {
     if (query(&getLong, F1("timer 4 period [%ld] us: "), period4))
     {
      period4 = lVal;
     }
     if (period4 > 0)
     {
      if (query(&getnum, F1("duty cycle [%d]: "), dutyCycle4))
      {
       dutyCycle4 = val;
      }
      printf(F0("period %ld\n"), period4);
      stopTimer4();
      isr4Counter = 0;
      pwm4Counter = 0;
      initTimer4(period4);
      pwm1Timer4(dutyCycle4);
     }
     else
     {
      stopTimer4();
     }
    }
    showTimer(&tmr4);
#if DEBUG
    printf(F0("isrCounter %u pwmCounter %u\n"), isr4Counter, pwm4Counter);
#endif
   }
#endif /* defined(TCCR4A) && !defined(TCCR4E) */

   else if (ch == '?')
   {
#ifdef PINA
    showPort((P_PORT) &PINA, "A");
#endif
    showPort((P_PORT) &PINB, "B");
    showPort((P_PORT) &PINC, "C");
    showPort((P_PORT) &PIND, "D");
#ifdef PINE
    showPort((P_PORT) &PINE, "E");
#endif
#ifdef PINF
    showPort((P_PORT) &PINF, "F");
#endif
#ifdef PING
    showPort((P_PORT) &PING, "G");
#endif
#ifdef PINH
    showPort((P_PORT) &PINH, "H");
#endif
#ifdef PINJ
    showPort((P_PORT) &PINJ, "J");
#endif
#ifdef PINK
    showPort((P_PORT) &PINK, "K");
#endif
#ifdef PINL
    showPort((P_PORT) &PINL, "L");
#endif
   }

#if INPUT_LOOP
   else if (ch == 's')
   {
    int tmp = 0;
    if (pin13Set())
     tmp |= 0x001;
    if (pin12Set())
     tmp |= 0x002;
    if (pin11Set())
     tmp |= 0x004;
    if (pin9Set())
     tmp |= 0x008;
    if (pin8Set())
     tmp |= 0x010;
    if (pin7Set())
     tmp |= 0x020;
    if (pin6Set())
     tmp |= 0x040;
    if (pin5Set())
     tmp |= 0x080;
    if (pin4Set())
     tmp |= 0x100;
    if (pin3Set())
     tmp |= 0x200;
    if (pin2Set())
     tmp |= 0x400;
    if (pin15Set())
     tmp |= 0x800;
    printf("portb %02x portc %02x portd %02x\n", PINB, PINC, PIND);
    printf("%03x\n", tmp);
    printf("13 12 11  9  8  7  6  5  4  3  2 15\n");
    printf("x+ ** x- pr y+ ** y- ** z+ ** z- **\n");
    int mask = 1;
    for (int i = 0; i < 12; i++)
    {
     printf("%2d ", (mask & tmp) ? 1 : 0);
     mask <<= 1;
    }
    printf("\n");
    printf("1 2 3 4\n");
    printf("%d %d %d %d\n", out1Read(), out2Read(), out3Read(), out4Read());
   }
#endif /* INPUT_LOOP */
  }
 }
}

void ctlStatus()
{
 procLoop();			/* run loop in case an input changed */

 printf(F0("eStopNo %d eStopNc %d eStopRst %d spFwd %d spRev %d\n"),
	eStopNoIn(), eStopNcIn(), eStopRstIn(), spFwdIn(), spRevIn());
 printf(F0("eStop %d wdEna %d cpActive %d\n"),
	eStop, wdEna, cpActive);
 printf(F0("eStopRly %d eStopPc %d stepDis %d spEna %d vfdFwd %d vfdRev %d\n"),
	eStopRlyRead(), eStopPcRead(), stepDisRead(),
	spEnaRead(), vfdFwdRead(), vfdRevRead());
}

#endif /* CONSOLE */

#if INPUT_LOOP

void inputLoop()
{
 if (out4Read())
 {
//  out1Clr();
//  out2Clr();
//  out3Clr();
  out4Clr();
 }
 else
 {
//  out1Set();
//  out2Set();
//  out3Set();
  out4Set();
 }

#if 1

 if (pin13Clr() || pin11Clr())	// x axis
  out1Set();
 else
  out1Clr();

 if (pin8Clr() || pin6Clr())	// y axis
  out2Set();
 else
  out2Clr();

 if (pin2Clr()	|| pin4Clr())	// z axis
  out3Set();
 else
  out3Clr();

#else
 
 if (pin11Clr() || pin6Clr() || pin4Clr()) // home
  out1Set();
 else
  out1Clr();

 if (pin13Clr() || pin11Clr() || pin8Clr() || 
     pin6Clr() || pin2Clr() || pin4Clr()) // limits
  out2Set();
 else
  out2Clr();

#endif

#if 0
 if (pin9Clr()) // || pin5Clr() || pin15Clr()) // probe
  out4Set();
 else
  out4Clr();
#endif
}

#endif /* INPUT_LOOP */

void procLoop()
{
 if (DEBUG)
 {
  if (dbg1Read())
   dbg1Clr();
  else
   dbg1Set();
 }

 if (!eStop			/* if not in estop */
 &&  wdEna)			/* and pulsing watchdog */
  wDogClr();			/* set signal high */

 procChargePump();		/* charge pump */
 procEStop();			/* e stop control */

 wDogSet();			/* clear watchdog signal */

 if (!eStop)			/* if not e stop */
 {
  procPWM();			/* pwm control */
  procSpindle();		/* spindle control */
 }
 else				/* if e stop */
 {
  eStopAction();		/* e stop actions */
 }

 if (CP_DEBUG)
 {
  if (dbgCpEnable)
  {
   uint16_t curTime = intMillis();
   if ((curTime - cpTime) > 10)
   {
    cpTime = curTime;
   }
  }
 }
}

void procChargePump()
{
 cli();				/* disable interrupts */
 uint16_t curTime = ((P_SHORT_LONG) &timer0_millis)->low;
 uint16_t tmpTime = cpTime;
 sei();				/* enable interrupts */

 if ((curTime - tmpTime) > CHARGE_PUMP_TIMEOUT) /* if charge pump timed out */
 {
  if (cpActive)			/* if was active */
  {
   cpActive = 0;		/* set to inactive */
   cpFail++;			/* count a failure */
   stopAll();			/* stop everything */
   if (DEBUG)
    dbg0Clr();
#if CONSOLE
   if (DEBUG)
    printf(F0("charge pump failed curTime %u cpTime %u delta %u\n"),
	   curTime, tmpTime, curTime - tmpTime);
#endif
  }
  cpTime = curTime - 30;
 }
 else				/* if charge pump active */
 {
  if (!eStop			/* if not in e stop */
  &&  !cpActive)		/* charge pump was inactive */
  {
   cpActive = 1;		/* set to active */
   stepDisSet();		/* enable stepper drivers */
   if (DEBUG)
    dbg0Set();
  }
 }
}

void procEStop()
{
 if (eStopNoIn() || eStopNcIn()) /* if either e stop condition */
  eStopSet();			/* set e stop condition */
 else				/* if e stop button released */
 {
  if (eStopRstIn())		/* if estop reset */
  {
   if (eStop)			/* if in e stop state */
   {
    if (lastResetTime == 0)	/* if timer not active */
     lastResetTime = intMillis(); /* set debounce timer */
    else if ((intMillis() - lastResetTime) > RESET_DEBOUNCE_TIME) /* if tmo */
     eStopClr();		/* clear e stop condition */
   }
  }
  else				/* if reset button not pushed */
   lastResetTime = 0;		/* reset timer */
 }
}

void procPWM()
{
 if (readPwm == 3)		/* if pwm reading done */
 {
  if (dbg3Read())
   dbg3Clr();
  else
   dbg3Set();
  fDutyCycle.l = (uint32_t) pulseEnd.w; /* get pulse width */
  fDutyCycle.l *= TMR1_PWM_MAX;	/* multiply by TMR1_PWM_MAX */
  fDutyCycle.l /= pulseTime.w;	/* divided by pulse interval */
  int diff = (int) fDutyCycle.low - (int) pwmDutyCycle; /* calc change */
  if (diff < 0)			/* if negative */
   diff = -diff;		/* make positive */
  if (diff > 3)			/* if greater than threshold */
  {
   if (pwmActive > 0)		/* if pwm active */
   {
    OCR1A = fDutyCycle.low;	/* set duty cycle */
   }
   else				/* if not active */
   {
    initTimer1(fDutyCycle.low); /* start timer */
   }
   pwmDutyCycle = fDutyCycle.low; /* save new value */
  }
  pwmActive = 1;		/* set to fast pwm active */
  lastPwmTime = intMillis();	/* save update time */
  readPwm = 0;			/* take another reading */
 }
 
 if (pwmActive)			/* if pwm active */
 {
  uint16_t t0 = intMillis();	/* read time */
  if ((t0 - lastPwmTime) > PWM_INACTIVITY_TIME) /* if no pwm int */
  {
   if (pwmIn())			/* if signal high */
   {
    pwmActive = -1;		/* active but fast pwm not running */
    lastPwmTime = t0;		/* update last pwm time */
    initTimer1(TMR1_PWM_MAX);	/* set to full speed */
   }
   else				/* if signal low */
   {
    pwmActive = 0;		/* set to inactive */
    lastPwmTime = 0;		/* clear last time */
    stopTimer1();		/* turn off pwm */
   }
  }
 }
 else				/* if pwm not active */
 {
  if (pwmIn())			/* if pwm in set */
  {
   pwmActive = -1;		/* set to active but fast pwm not running */
   lastPwmTime = intMillis();	/* update last pwm time */
   initTimer1(TMR1_PWM_MAX);	/* set to full speed */
  }
 }
}

void procSpindle()
{
 if (spFwdIn())			/* if forward */
 {
  if (!spRevIn())		/* if reverse not set */
  {
   if (vfdRevRead())		/* if reverse set */
   {
    vfdRevClr();		/* disable reverse */
    if (CONSOLE && DEBUG)
     putx0('r');
   }
   if (!vfdFwdRead())		/* if forward not set */
   {
    vfdFwdSet();		/* run forward */
    if (CONSOLE && DEBUG)
     putx0('F');
   }
  }
  else				/* if reverse also set */
  {
   vfdFwdClr();			/* stop forward */
   vfdRevClr();			/* and reverse */
  }
 }
 else if (spRevIn())		/* if reverse */
 {
  if (vfdFwdRead())		/* if forward set */
  {
   vfdFwdClr();			/* disable forward */
   if (CONSOLE && DEBUG)
    putx0('f');
  }
  if (!vfdRevRead())		/* if reverse not set */
  {
   vfdRevSet();			/* run reverse */
   if (CONSOLE && DEBUG)
    putx0('R');
  }
 }
 else				/* if neither forward or reverse */
 {
  if (vfdFwdRead())
  {
   vfdFwdClr();			/* disable forward */
   if (CONSOLE && DEBUG)
    putx0('f');
  }
  if (vfdRevRead())
  {
   vfdRevClr();			/* disable reverse */
   if (CONSOLE && DEBUG)
    putx0('r');
  }
 }
}

void eStopAction()
{
 if (pwmActive)			/* if pwm active */
 {
  pwmActive = 0;		/* set to inactive */
  stopTimer1();			/* turn off pwm */
 }

 if (vfdFwdRead())		/* if forward set */
 {
  vfdFwdClr();			/* disable forward */
  if (CONSOLE && DEBUG)
   putx0('f');
 }
 if (vfdRevRead())		/* if reverse set */
 {
  vfdRevClr();			/* disable reverse */
  if (CONSOLE && DEBUG)
   putx0('r');
 }
}

void eStopSet()
{
 eStop = 1;			/* start in e stop */
 wdEna = 0;			/* start with watchdog disabled */
 cpActive = 0;			/* set charge pump to inactive */
 pwmActive = 0;			/* set pwm to inactive */
 eStopRlyClr();
 eStopPcClr();
 stopAll();
}

void eStopClr()
{
 eStop = 0;			/* start in e stop */
 wdEna = 1;			/* start with watchdog disabled */
 eStopRlySet();			/* enable e stop relay */
 eStopPcSet();			/* enable pc e stop */
 stepDisSet();			/* disable stepper motors */
}

void stopAll()
{
 stepDisClr();			/* disable stepper motors */
 spEnaClr();			/* stop spindle */
 vfdFwdClr();			/* stop vfd forward */
 vfdRevClr();			/* and reverse */
}

ISR(TIMER1_OVF_vect)
{
}

#if TMR2_PWM_TIMER

/* timer 2 pwm counter interrupt */

ISR(TIMER2_OVF_vect)
{
 if (DEBUG)
 {
  if (t2Read())
   t2Clr();
  else
   t2Set();
 }
 pwmTimerHigh++;			// update overflow counter
#if DEBUG
 isr2Counter++;
#endif
}

/* interrupt 0 pwm signal */

ISR(INT0_vect)
{
 if (!eStop)			// if e stop not set
 {
  unsigned char pwm = PWM_In;
  TCCR2B = 0;			// stop timer
  if (pwm & PWM_Mask)		// low to high transition
  {
   if (readPwm == 0)		// clear counter
   {
    pwmTimerHigh = 0;		// clear overflow
    TCNT2 = 0;			// clear counter
    readPwm = 1;
   }
   else				// read pwm period
   {
    pulseTime.hi = pwmTimerHigh;
    pulseTime.lo = TCNT2;
    readPwm = 3;
   }
  }
  else				// high to low transition
  {
   if (readPwm == 1)		// read pulse start
   {
    pulseEnd.hi = pwmTimerHigh;
    pulseEnd.lo = TCNT2;
    readPwm = 2;
   }
  }
  TCCR2B = _BV(CS22);		// restart
 }
 pwmInterrupts++;		// count interrupts
}

#endif

#if TMR3_PWM_TIMER

/* interrupt 0 pwm signal */

ISR(INT0_vect)
{
 if (!eStop)			// if e stop not set
 {
  unsigned char pwm = PWM_In;
  if (pwm & PWM_Mask)		// low to high transition
  {
   if (readPwm == 0)		// clear counter
   {
    TCCR3B = 0;			// stop timer
    TCNT3 = 0;			// clear counter
    TCCR3B = _BV(CS31) | _BV(CS30); // load divider to start
    readPwm = 1;
   }
   else				// read pwm period
   {
    pulseTime.w = TCNT3;		// set pulse width time
    readPwm = 3;
   }
  }
  else				// high to low transition
  {
   if (readPwm == 1)		// read pulse start
   {
    pulseEnd.w = TCNT3;		// set pulse period time
    readPwm = 2;
   }
  }
 }
 pwmInterrupts++;		// count interrupts
}

#endif

/* interrupt 1 charge pump */

ISR(INT1_vect)
{
 if (DEBUG)
 {
  if (dbg2Read())
   dbg2Clr();
  else
   dbg2Set();
 }
 if (!eStop)			// if e stop not active
 {
  cpTime = ((P_SHORT_LONG) &timer0_millis)->low;
 }
 cpInterrupts++;
}

#ifdef TCCR3A

/* interrupt for spindle pwm test */

ISR(TIMER3_COMPA_vect)
{
#if DEBUG
 pwm3Counter++;
#endif
}

ISR(TIMER3_OVF_vect)
{
#if DEBUG
 isr3Counter++;
#endif
}

#endif /* TCCR3A */

#if defined(TCCR4A) && !defined(TCCR4E)

/* interrupt for charge pump test */

ISR(TIMER4_OVF_vect)
{
#if DEBUG
 isr4Counter++;
#endif
}

ISR(TIMER4_COMPA_vect)
{
#if DEBUG
 pwm4Counter++;
#endif
}

#endif /* defined(TCCR4A) && !defined(TCCR4E) */

uint16_t intMillis()
{
 uint16_t m;
 uint8_t oldSREG = SREG;	// save interrupt flag
 cli();				// disable interrupts
 m = ((P_SHORT_LONG) &timer0_millis)->low; // read low part of millis
 SREG = oldSREG;		// enable interrupts
 return(m);			// return value
}

#if CONSOLE

void showTimer0()
{
 printf(F0("TCCR0A %02x TCCR0B %02x TCNT0 %02x TIMSK0 %02x TIFR0 %02x\n"),
	TCCR0A, TCCR0B, TCNT0, TIMSK0, TIFR0);
 printf(F0("OCR0A %02x OCR0b %02x\n"),
	OCR0A, OCR0B);
}

void showTimer(P_TIMER_CTL tmr)
{
 P_TMR t = tmr->timer;
 P_PORT p = tmr->aPort;
 printf(F0("a port %02x ddr %02x mask %02x "
	   "tccra %02x tccrb %02x tccrc %02x\n"),
	p->port, p->ddr, tmr->aMask,
	t->tccra, t->tccrb, t->tccrc);
 printf(F0("tctn %04x ocra %04x ocrb %04x ocrc %04x icr %04X\n"),
	t->tcnt, t->ocra, t->ocrb, t->ocrc, t->icr);
 printf(F0("timsk %02x tifr %02x\n"),
	*tmr->timsk, *tmr->tifr);
}

void showPort(P_PORT port, const char *name)
{
 printf(F0("%s port %02x ddr %02x pinc %0x\n"),
	name, port->port, port->ddr, port->pin);
}

#endif /* CONSOLE */
