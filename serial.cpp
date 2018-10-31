#if !defined(INCLUDE)

#include <Arduino.h>
#include <Print.h>
#include <HardwareSerial.h>
#include <stdio.h>
#include "config.h"

#define EXT
#endif

#define PRINTF 0		/* 0 clib printf, 1 printf.cpp */
#if PRINTF
#include "printf.h"
#endif

#if CONSOLE
#define DBGPORT Serial

#if FLASH_STRINGS
#define F0(format) F(format)
#define F1(format) F(format)
#else
#define F0(format) format
#define F1(format) format
#endif

EXT void initSerial(int baudRate);
EXT char getx();
EXT void putx0(char c);

#define newLine() printf("\n"); fflush(stdout) // use printf instead of puts

EXT int val;
EXT unsigned char getnum();

EXT long lVal;
EXT unsigned char getLong();

EXT char query(const char *format, ...);
EXT char query(unsigned char (*get)(), const char *format, ...);

#if FLASH_STRINGS
EXT const char *argConv(const __FlashStringHelper *s);
EXT int printf(const __FlashStringHelper *format, ...);
EXT int puts(const __FlashStringHelper *str);
EXT char query(const __FlashStringHelper *format, ...);
EXT char query(unsigned char (*get)(), const __FlashStringHelper *format, ...);
#endif

#if !defined(INCLUDE)

char query(const char *format, ...)
{
 va_list args;
 va_start(args, format);
 vprintf(format, args);
 va_end(args);
 fflush(stdout);
 char ch = getx();
 putx0(ch);
 newLine();
 return(ch);
}

char query(unsigned char (*get)(), const char *format, ...)
{
 va_list args;
 va_start(args, format);
 vprintf(format, args);
 va_end(args);
 fflush(stdout);
 char ch = get();
 newLine();
 return(ch);
}

#if FLASH_STRINGS

char stringBuffer[80];

const char *argConv(const __FlashStringHelper *s)
{
 PGM_P p = reinterpret_cast <PGM_P> (s);
 char *dst = stringBuffer;
 while (1)
 {
  unsigned char c = pgm_read_byte(p++);
  *dst++ = c;
  if (c == 0)
   break;
 }
 return((const char *) stringBuffer);
}

int printf(const __FlashStringHelper *format, ...)
{
 PGM_P p = reinterpret_cast <PGM_P> (format);
 char *dst = stringBuffer;
 while (1)
 {
  unsigned char c = pgm_read_byte(p++);
  *dst++ = c;
  if (c == 0)
   break;
 }
 va_list args;
 va_start(args, format);
 int rtn = vprintf((const char *) stringBuffer, args);
 va_end(args);
 return(rtn);
}

int puts(const __FlashStringHelper *str)
{
 fflush(stdout);
 PGM_P p = reinterpret_cast <PGM_P> (str);
 while (1)
 {
  unsigned char c = pgm_read_byte(p++);
  if (c == 0)
   break;
  if (c == '\n')
   DBGPORT.write('\r');
  DBGPORT.write(c);
 }
 return(1);
}

char query(const __FlashStringHelper *format, ...)
{
 PGM_P p = reinterpret_cast <PGM_P> (format);
 char *dst = stringBuffer;
 while (1)
 {
  unsigned char c = pgm_read_byte(p++);
  *dst++ = c;
  if (c == 0)
   break;
 }
 va_list args;
 va_start(args, format);
 vprintf((const char *) stringBuffer, args);
 va_end(args);
 fflush(stdout);
 char ch = getx();
 putx0(ch);
 newLine();
 return(ch);
}

char query(unsigned char (*get)(), const __FlashStringHelper *format, ...)
{
 PGM_P p = reinterpret_cast <PGM_P> (format);
 char *dst = stringBuffer;
 while (1)
 {
  unsigned char c = pgm_read_byte(p++);
  *dst++ = c;
  if (c == 0)
   break;
 }
 va_list args;
 va_start(args, format);
 vprintf((const char *) stringBuffer, args);
 va_end(args);
 fflush(stdout);
 char ch = get();
 newLine();
 return(ch);
}

#endif

EXT void procLoop();

#if PRINTF
void putx1(void *p, char c)
{
 if (c == '\n')
  DBGPORT.write('\r');
 DBGPORT.write(c);
}
#endif	/* PRINTF */

#if !PRINTF
static FILE uartout = {0};

static int putx(char c, FILE *stream)
{
 if (c == '\n')
  DBGPORT.write('\r');
 DBGPORT.write(c);
 return 0;
}

void putx0(char c)
{
 if (c == '\n')
  DBGPORT.write('\r');
 DBGPORT.write(c);
}
#endif	/* ! PRINTF */

void initSerial(int baudRate)
{
 DBGPORT.begin(baudRate);

#if PRINTF
 init_printf(NULL, putx1);
#endif

#if !PRINTF
 fdev_setup_stream(&uartout, putx, NULL, _FDEV_SETUP_WRITE);
 stdout = &uartout;
#endif

 unsigned long timeout = millis() + 100;
 while (millis() < timeout)
 {
  while (DBGPORT.available())
  {
   DBGPORT.read();
  }
 }
}

#define MAXDIG 10		/* maximum input digits */
#define LONGDIG 16

char getx()
{
 while (1)
 {
  procLoop();
  if (DBGPORT.available())
  {
   char ch = DBGPORT.read();
   return(ch);
  }
 }
}

unsigned char getnum()
{
 char ch;			/* input character */
 char chbuf[MAXDIG];		/* input digit buffer */
 unsigned char chidx;		/* input character index */
 unsigned char count;		/* input character count */
 char neg;			/* negative flag */
 char hex;			/* hex flag */

 neg = 0;
 hex = 0;
 val = 0;
 chidx = 0;
 count = 0;
 while (1)
 {
  ch = getx();
  if ((ch >= '0')
  &&  (ch <= '9'))
  {
   if (chidx < MAXDIG)
   {
    putx0(ch);
    chbuf[chidx] = ch - '0';
    chidx++;
   }
  }
  else if ((ch >= 'a')
  &&       (ch <= 'f'))
  {
   if (chidx < MAXDIG)
   {
    hex = 1;
    putx0(ch);
    chbuf[chidx] = ch - 'a' + 10;
    chidx++;
   }
  }
  else if ((ch == 8)
       ||  (ch == 127))
  {
   if (chidx > 0)
   {
    --chidx;
    putx0(8);
    putx0(' ');
    putx0(8);
   }
  }
  else if ((ch == '\n')
       ||  (ch == '\r')
       ||  (ch == ' '))
  {
   if (hex)
   {
    while (count < chidx)
    {
     val = (val << 4) + chbuf[count];
     count++;
    }
   }
   else
   {
    while (count < chidx)
    {
     val = val * 10 + chbuf[count];
     count++;
    }
   }
   if (neg)
    val = -val;
   return(count);
  }
  else if (chidx == 0)
  {
   if (ch == '-')
   {
    putx0(ch);
    neg = 1;
   }
   else if (ch == 'x')
   {
    putx0(ch);
    hex = 1;
   }
  }
  else
   printf("%d ",ch);
 }
}

unsigned char getLong()
{
 char ch;			/* input character */
 char chbuf[LONGDIG];		/* input digit buffer */
 unsigned char chidx;		/* input character index */
 unsigned char count;		/* input character count */
 char neg;			/* negative flag */
 char hex;			/* hex flag */

 neg = 0;
 hex = 0;
 lVal = 0;
 chidx = 0;
 count = 0;
 while (1)
 {
  ch = getx();
  if ((ch >= '0')
  &&  (ch <= '9'))
  {
   if (chidx < MAXDIG)
   {
    putx0(ch);
    chbuf[chidx] = ch - '0';
    chidx++;
   }
  }
  else if ((ch >= 'a')
  &&       (ch <= 'f'))
  {
   if (chidx < MAXDIG)
   {
    hex = 1;
    putx0(ch);
    chbuf[chidx] = ch - 'a' + 10;
    chidx++;
   }
  }
  else if ((ch == 8)
       ||  (ch == 127))
  {
   if (chidx > 0)
   {
    --chidx;
    putx0(8);
    putx0(' ');
    putx0(8);
   }
  }
  else if ((ch == '\n')
       ||  (ch == '\r')
       ||  (ch == ' '))
  {
   if (hex)
   {
    while (count < chidx)
    {
     lVal = (lVal << 4) + chbuf[count];
     count++;
    }
   }
   else
   {
    while (count < chidx)
    {
     lVal = lVal * 10 + chbuf[count];
     count++;
    }
   }
   if (neg)
    lVal = -lVal;
   return(count);
  }
  else if (chidx == 0)
  {
   if (ch == '-')
   {
    putx0(ch);
    neg = 1;
   }
   else if (ch == 'x')
   {
    putx0(ch);
    hex = 1;
   }
  }
  else
   printf("%d ",ch);
 }
}

#endif /* !defined(INCLUDE) */
#endif /* CONSOLE */
