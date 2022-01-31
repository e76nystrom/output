extern void pinConfig();

#define DEBUG                1
#define CP_DEBUG             1
#define CONSOLE              1
#define FLASH_STRINGS        1
#define INPUT_TEST           0

#ifdef ARDUINO_AVR_MEGA2560

#define INPUT_LOOP           1
#define SPINDLE_PWM_TEST     1
#define CHARGE_PUMP_TEST     1
#define TMR2_PWM_TIMER       1
#define TMR3_PWM_TIMER       0

#define OC0A_Port PINB
#define OC0A_Mask _BV(PB7)

#define OC0B_Port PING
#define OC0B_Mask _BV(PG5)

#define OC1A_Port PINB
#define OC1A_Mask _BV(PB5)

#define OC1B_Port PINB
#define OC1B_Mask _BV(PB6)

#define OC1C_Port PINB
#define OC1C_Mask _BV(PB7)

#define OC2A_Port PINB
#define OC2A_Mask _BV(PB4)

#define OC2B_Port PINH
#define OC2B_Mask _BV(PH6)

#define OC3A_Port PINE
#define OC3A_Mask _BV(PE3)

#define OC3B_Port PINE
#define OC3B_Mask _BV(PE4)

#define OC3C_Port PINE
#define OC3C_Mask _BV(PE5)

#define OC4A_Port PINH
#define OC4A_Mask _BV(PH3)

#define OC4B_Port PINH
#define OC4B_Mask _BV(PH4)

#define OC4C_Port PINH
#define OC4C_Mask _BV(PH5)

#define OC5A_Port PINL
#define OC5A_Mask _BV(PL3)

#define OC5B_Port PINL
#define OC5B_Mask _BV(PL4)

#define OC5C_Port PINL
#define OC5C_Mask _BV(PL5)

#define A_Pin 68
#define A_Port PORTK
#define A_DDR DDRK
#define A_In PINK
#define A_Bit PK6
#define A_Mask _BV(A_Bit)
#define aRead() ((A_Port & A_Mask) != 0)
#define aSet() A_Port |= A_Mask
#define aClr() A_Port &= ~A_Mask

#define B_Pin 69
#define B_Port PORTK
#define B_DDR DDRK
#define B_In PINK
#define B_Bit PK7
#define B_Mask _BV(B_Bit)
#define bRead() ((B_Port & B_Mask) != 0)
#define bSet() B_Port |= B_Mask
#define bClr() B_Port &= ~B_Mask

#define INDEX_Pin 32
#define INDEX_Port PORTC
#define INDEX_DDR DDRC
#define INDEX_In PINC
#define INDEX_Bit PC5
#define INDEX_Mask _BV(INDEX_Bit)
#define indexRead() ((INDEX_Port & INDEX_Mask) != 0)
#define indexSet() INDEX_Port |= INDEX_Mask
#define indexClr() INDEX_Port &= ~INDEX_Mask

#define SYNC_Pin 33
#define SYNC_Port PORTC
#define SYNC_DDR DDRC
#define SYNC_In PINC
#define SYNC_Bit PC4
#define SYNC_Mask _BV(SYNC_Bit)
#define syncRead() ((SYNC_Port & SYNC_Mask) != 0)
#define syncSet() SYNC_Port |= SYNC_Mask
#define syncClr() SYNC_Port &= ~SYNC_Mask

#define T1_PWM_A_Pin 11
#define T1_PWM_A_Port PORTB
#define T1_PWM_A_DDR DDRB
#define T1_PWM_A_In PINB
#define T1_PWM_A_Bit PB5
#define T1_PWM_A_Mask _BV(T1_PWM_A_Bit)
#define t1PwmARead() ((T1_PWM_A_Port & T1_PWM_A_Mask) != 0)
#define t1PwmASet() T1_PWM_A_Port |= T1_PWM_A_Mask
#define t1PwmAClr() T1_PWM_A_Port &= ~T1_PWM_A_Mask

#define T3_PWM_A_Pin 5
#define T3_PWM_A_Port PORTE
#define T3_PWM_A_DDR DDRE
#define T3_PWM_A_In PINE
#define T3_PWM_A_Bit PE3
#define T3_PWM_A_Mask _BV(T3_PWM_A_Bit)
#define t3PwmARead() ((T3_PWM_A_Port & T3_PWM_A_Mask) != 0)
#define t3PwmASet() T3_PWM_A_Port |= T3_PWM_A_Mask
#define t3PwmAClr() T3_PWM_A_Port &= ~T3_PWM_A_Mask

#define T4_PWM_A_Pin 6
#define T4_PWM_A_Port PORTH
#define T4_PWM_A_DDR DDRH
#define T4_PWM_A_In PINH
#define T4_PWM_A_Bit PH3
#define T4_PWM_A_Mask _BV(T4_PWM_A_Bit)
#define t4PwmARead() ((T4_PWM_A_Port & T4_PWM_A_Mask) != 0)
#define t4PwmASet() T4_PWM_A_Port |= T4_PWM_A_Mask
#define t4PwmAClr() T4_PWM_A_Port &= ~T4_PWM_A_Mask

#define CHG_PUMP_Pin 20
#define CHG_PUMP_In PIND
#define CHG_PUMP_Bit PD1
#define CHG_PUMP_Mask _BV(CHG_PUMP_Bit)
#define chgPumpIn() ((CHG_PUMP_In & CHG_PUMP_Mask) != 0)
#define chgPumpSet() ((CHG_PUMP_In & CHG_PUMP_Mask) != 0)
#define chgPumpClr() ((CHG_PUMP_In & CHG_PUMP_Mask) == 0)
#define chgPumpIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 2);\
	EICRA |= (_BV(ISC01)|_BV(ISC00)) << 2;\
	EIMSK |= (_BV(INT0) << 1)

#define PWM_Pin 21
#define PWM_In PIND
#define PWM_Bit PD0
#define PWM_Mask _BV(PWM_Bit)
#define pwmIn() ((PWM_In & PWM_Mask) != 0)
#define pwmSet() ((PWM_In & PWM_Mask) != 0)
#define pwmClr() ((PWM_In & PWM_Mask) == 0)
#define pwmIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 0);\
	EICRA |= (_BV(ISC00)) << 0;\
	EIMSK |= (_BV(INT0) << 0)

#define PWM_SEL_Pin 39
#define PWM_SEL_Port PORTG
#define PWM_SEL_DDR DDRG
#define PWM_SEL_In PING
#define PWM_SEL_Bit PG2
#define PWM_SEL_Mask _BV(PWM_SEL_Bit)
#define pwmSelRead() ((PWM_SEL_Port & PWM_SEL_Mask) != 0)
#define pwmSelSet() PWM_SEL_Port |= PWM_SEL_Mask
#define pwmSelClr() PWM_SEL_Port &= ~PWM_SEL_Mask

#define SP_FWD_Pin 23
#define SP_FWD_In PINA
#define SP_FWD_Bit PA1
#define SP_FWD_Mask _BV(SP_FWD_Bit)
#define spFwdIn() ((SP_FWD_In & SP_FWD_Mask) != 0)
#define spFwdSet() ((SP_FWD_In & SP_FWD_Mask) != 0)
#define spFwdClr() ((SP_FWD_In & SP_FWD_Mask) == 0)

#define SP_REV_Pin 25
#define SP_REV_In PINA
#define SP_REV_Bit PA3
#define SP_REV_Mask _BV(SP_REV_Bit)
#define spRevIn() ((SP_REV_In & SP_REV_Mask) != 0)
#define spRevSet() ((SP_REV_In & SP_REV_Mask) != 0)
#define spRevClr() ((SP_REV_In & SP_REV_Mask) == 0)

#define E_STOP_NO_Pin 29
#define E_STOP_NO_In PINA
#define E_STOP_NO_Bit PA7
#define E_STOP_NO_Mask _BV(E_STOP_NO_Bit)
#define eStopNoIn() ((E_STOP_NO_In & E_STOP_NO_Mask) != 0)
#define eStopNoSet() ((E_STOP_NO_In & E_STOP_NO_Mask) == 0)
#define eStopNoClr() ((E_STOP_NO_In & E_STOP_NO_Mask) != 0)

#define E_STOP_NC_Pin 31
#define E_STOP_NC_In PINC
#define E_STOP_NC_Bit PC6
#define E_STOP_NC_Mask _BV(E_STOP_NC_Bit)
#define eStopNcIn() ((E_STOP_NC_In & E_STOP_NC_Mask) != 0)
#define eStopNcSet() ((E_STOP_NC_In & E_STOP_NC_Mask) != 0)
#define eStopNcClr() ((E_STOP_NC_In & E_STOP_NC_Mask) == 0)

#define E_STOP_RST_Pin 27
#define E_STOP_RST_In PINA
#define E_STOP_RST_Bit PA5
#define E_STOP_RST_Mask _BV(E_STOP_RST_Bit)
#define eStopRstIn() ((E_STOP_RST_In & E_STOP_RST_Mask) != 0)
#define eStopRstSet() ((E_STOP_RST_In & E_STOP_RST_Mask) != 0)
#define eStopRstClr() ((E_STOP_RST_In & E_STOP_RST_Mask) == 0)

#define FAST_PWM_Pin 11
#define FAST_PWM_Port PORTB
#define FAST_PWM_DDR DDRB
#define FAST_PWM_In PINB
#define FAST_PWM_Bit PB5
#define FAST_PWM_Mask _BV(FAST_PWM_Bit)
#define fastPwmRead() ((FAST_PWM_Port & FAST_PWM_Mask) != 0)
#define fastPwmSet() FAST_PWM_Port |= FAST_PWM_Mask
#define fastPwmClr() FAST_PWM_Port &= ~FAST_PWM_Mask

#define VFD_FWD_Pin 28
#define VFD_FWD_Port PORTA
#define VFD_FWD_DDR DDRA
#define VFD_FWD_In PINA
#define VFD_FWD_Bit PA6
#define VFD_FWD_Mask _BV(VFD_FWD_Bit)
#define vfdFwdRead() ((VFD_FWD_Port & VFD_FWD_Mask) != 0)
#define vfdFwdSet() VFD_FWD_Port |= VFD_FWD_Mask
#define vfdFwdClr() VFD_FWD_Port &= ~VFD_FWD_Mask

#define VFD_REV_Pin 30
#define VFD_REV_Port PORTC
#define VFD_REV_DDR DDRC
#define VFD_REV_In PINC
#define VFD_REV_Bit PC7
#define VFD_REV_Mask _BV(VFD_REV_Bit)
#define vfdRevRead() ((VFD_REV_Port & VFD_REV_Mask) != 0)
#define vfdRevSet() VFD_REV_Port |= VFD_REV_Mask
#define vfdRevClr() VFD_REV_Port &= ~VFD_REV_Mask

#define SP_ENA_Pin 64
#define SP_ENA_Port PORTK
#define SP_ENA_DDR DDRK
#define SP_ENA_In PINK
#define SP_ENA_Bit PK2
#define SP_ENA_Mask _BV(SP_ENA_Bit)
#define spEnaRead() ((SP_ENA_Port & SP_ENA_Mask) != 0)
#define spEnaSet() SP_ENA_Port |= SP_ENA_Mask
#define spEnaClr() SP_ENA_Port &= ~SP_ENA_Mask

#define E_STOP_PC_Pin 65
#define E_STOP_PC_Port PORTK
#define E_STOP_PC_DDR DDRK
#define E_STOP_PC_In PINK
#define E_STOP_PC_Bit PK3
#define E_STOP_PC_Mask _BV(E_STOP_PC_Bit)
#define eStopPcRead() ((E_STOP_PC_Port & E_STOP_PC_Mask) != 0)
#define eStopPcSet() E_STOP_PC_Port |= E_STOP_PC_Mask
#define eStopPcClr() E_STOP_PC_Port &= ~E_STOP_PC_Mask

#define E_STOP_RLY_Pin 66
#define E_STOP_RLY_Port PORTK
#define E_STOP_RLY_DDR DDRK
#define E_STOP_RLY_In PINK
#define E_STOP_RLY_Bit PK4
#define E_STOP_RLY_Mask _BV(E_STOP_RLY_Bit)
#define eStopRlyRead() ((E_STOP_RLY_Port & E_STOP_RLY_Mask) != 0)
#define eStopRlySet() E_STOP_RLY_Port |= E_STOP_RLY_Mask
#define eStopRlyClr() E_STOP_RLY_Port &= ~E_STOP_RLY_Mask

#define STEP_DIS_Pin 67
#define STEP_DIS_Port PORTK
#define STEP_DIS_DDR DDRK
#define STEP_DIS_In PINK
#define STEP_DIS_Bit PK5
#define STEP_DIS_Mask _BV(STEP_DIS_Bit)
#define stepDisRead() ((STEP_DIS_Port & STEP_DIS_Mask) != 0)
#define stepDisSet() STEP_DIS_Port |= STEP_DIS_Mask
#define stepDisClr() STEP_DIS_Port &= ~STEP_DIS_Mask

#define W_DOG_Pin 44
#define W_DOG_Port PORTL
#define W_DOG_DDR DDRL
#define W_DOG_In PINL
#define W_DOG_Bit PL5
#define W_DOG_Mask _BV(W_DOG_Bit)
#define wDogRead() ((W_DOG_Port & W_DOG_Mask) != 0)
#define wDogSet() W_DOG_Port |= W_DOG_Mask
#define wDogClr() W_DOG_Port &= ~W_DOG_Mask

#define PILOT_Pin 46
#define PILOT_Port PORTL
#define PILOT_DDR DDRL
#define PILOT_In PINL
#define PILOT_Bit PL3
#define PILOT_Mask _BV(PILOT_Bit)
#define pilotRead() ((PILOT_Port & PILOT_Mask) != 0)
#define pilotSet() PILOT_Port |= PILOT_Mask
#define pilotClr() PILOT_Port &= ~PILOT_Mask

#define LED_Pin 13
#define LED_Port PORTB
#define LED_DDR DDRB
#define LED_In PINB
#define LED_Bit PB7
#define LED_Mask _BV(LED_Bit)
#define ledRead() ((LED_Port & LED_Mask) != 0)
#define ledSet() LED_Port |= LED_Mask
#define ledClr() LED_Port &= ~LED_Mask

#define T2_Pin 68
#define T2_Port PORTK
#define T2_DDR DDRK
#define T2_In PINK
#define T2_Bit PK6
#define T2_Mask _BV(T2_Bit)
#define t2Read() ((T2_Port & T2_Mask) != 0)
#define t2Set() T2_Port |= T2_Mask
#define t2Clr() T2_Port &= ~T2_Mask

#define DBG0_Pin 34
#define DBG0_Port PORTC
#define DBG0_DDR DDRC
#define DBG0_In PINC
#define DBG0_Bit PC3
#define DBG0_Mask _BV(DBG0_Bit)
#define dbg0Read() ((DBG0_Port & DBG0_Mask) != 0)
#define dbg0Set() DBG0_Port |= DBG0_Mask
#define dbg0Clr() DBG0_Port &= ~DBG0_Mask

#define DBG1_Pin 35
#define DBG1_Port PORTC
#define DBG1_DDR DDRC
#define DBG1_In PINC
#define DBG1_Bit PC2
#define DBG1_Mask _BV(DBG1_Bit)
#define dbg1Read() ((DBG1_Port & DBG1_Mask) != 0)
#define dbg1Set() DBG1_Port |= DBG1_Mask
#define dbg1Clr() DBG1_Port &= ~DBG1_Mask

#define DBG2_Pin 36
#define DBG2_Port PORTC
#define DBG2_DDR DDRC
#define DBG2_In PINC
#define DBG2_Bit PC1
#define DBG2_Mask _BV(DBG2_Bit)
#define dbg2Read() ((DBG2_Port & DBG2_Mask) != 0)
#define dbg2Set() DBG2_Port |= DBG2_Mask
#define dbg2Clr() DBG2_Port &= ~DBG2_Mask

#define DBG3_Pin 37
#define DBG3_Port PORTC
#define DBG3_DDR DDRC
#define DBG3_In PINC
#define DBG3_Bit PC0
#define DBG3_Mask _BV(DBG3_Bit)
#define dbg3Read() ((DBG3_Port & DBG3_Mask) != 0)
#define dbg3Set() DBG3_Port |= DBG3_Mask
#define dbg3Clr() DBG3_Port &= ~DBG3_Mask

#define DBG4_Pin 38
#define DBG4_Port PORTD
#define DBG4_DDR DDRD
#define DBG4_In PIND
#define DBG4_Bit PD7
#define DBG4_Mask _BV(DBG4_Bit)
#define dbg4Read() ((DBG4_Port & DBG4_Mask) != 0)
#define dbg4Set() DBG4_Port |= DBG4_Mask
#define dbg4Clr() DBG4_Port &= ~DBG4_Mask

#define DBG5_Pin 40
#define DBG5_Port PORTG
#define DBG5_DDR DDRG
#define DBG5_In PING
#define DBG5_Bit PG1
#define DBG5_Mask _BV(DBG5_Bit)
#define dbg5Read() ((DBG5_Port & DBG5_Mask) != 0)
#define dbg5Set() DBG5_Port |= DBG5_Mask
#define dbg5Clr() DBG5_Port &= ~DBG5_Mask

#define PIN2_Pin 4
#define PIN2_In PING
#define PIN2_Bit PG5
#define PIN2_Mask _BV(PIN2_Bit)
#define pin2In() ((PIN2_In & PIN2_Mask) != 0)
#define pin2Set() ((PIN2_In & PIN2_Mask) != 0)
#define pin2Clr() ((PIN2_In & PIN2_Mask) == 0)

#define PIN3_Pin 10
#define PIN3_In PINB
#define PIN3_Bit PB4
#define PIN3_Mask _BV(PIN3_Bit)
#define pin3In() ((PIN3_In & PIN3_Mask) != 0)
#define pin3Set() ((PIN3_In & PIN3_Mask) != 0)
#define pin3Clr() ((PIN3_In & PIN3_Mask) == 0)

#define PIN4_Pin 12
#define PIN4_In PINB
#define PIN4_Bit PB6
#define PIN4_Mask _BV(PIN4_Bit)
#define pin4In() ((PIN4_In & PIN4_Mask) != 0)
#define pin4Set() ((PIN4_In & PIN4_Mask) != 0)
#define pin4Clr() ((PIN4_In & PIN4_Mask) == 0)

#define PIN5_Pin 15
#define PIN5_In PINJ
#define PIN5_Bit PJ0
#define PIN5_Mask _BV(PIN5_Bit)
#define pin5In() ((PIN5_In & PIN5_Mask) != 0)
#define pin5Set() ((PIN5_In & PIN5_Mask) != 0)
#define pin5Clr() ((PIN5_In & PIN5_Mask) == 0)

#define PIN6_Pin 14
#define PIN6_In PINJ
#define PIN6_Bit PJ1
#define PIN6_Mask _BV(PIN6_Bit)
#define pin6In() ((PIN6_In & PIN6_Mask) != 0)
#define pin6Set() ((PIN6_In & PIN6_Mask) != 0)
#define pin6Clr() ((PIN6_In & PIN6_Mask) == 0)

#define PIN7_Pin 17
#define PIN7_In PINH
#define PIN7_Bit PH0
#define PIN7_Mask _BV(PIN7_Bit)
#define pin7In() ((PIN7_In & PIN7_Mask) != 0)
#define pin7Set() ((PIN7_In & PIN7_Mask) != 0)
#define pin7Clr() ((PIN7_In & PIN7_Mask) == 0)

#define PIN8_Pin 16
#define PIN8_In PINH
#define PIN8_Bit PH1
#define PIN8_Mask _BV(PIN8_Bit)
#define pin8In() ((PIN8_In & PIN8_Mask) != 0)
#define pin8Set() ((PIN8_In & PIN8_Mask) != 0)
#define pin8Clr() ((PIN8_In & PIN8_Mask) == 0)

#define PIN9_Pin 22
#define PIN9_In PINA
#define PIN9_Bit PA0
#define PIN9_Mask _BV(PIN9_Bit)
#define pin9In() ((PIN9_In & PIN9_Mask) != 0)
#define pin9Set() ((PIN9_In & PIN9_Mask) != 0)
#define pin9Clr() ((PIN9_In & PIN9_Mask) == 0)

#define PIN10_Pin 24
#define PIN10_In PINA
#define PIN10_Bit PA2
#define PIN10_Mask _BV(PIN10_Bit)
#define pin10In() ((PIN10_In & PIN10_Mask) != 0)
#define pin10Set() ((PIN10_In & PIN10_Mask) != 0)
#define pin10Clr() ((PIN10_In & PIN10_Mask) == 0)

#define PIN11_Pin 26
#define PIN11_In PINA
#define PIN11_Bit PA4
#define PIN11_Mask _BV(PIN11_Bit)
#define pin11In() ((PIN11_In & PIN11_Mask) != 0)
#define pin11Set() ((PIN11_In & PIN11_Mask) != 0)
#define pin11Clr() ((PIN11_In & PIN11_Mask) == 0)

#define PIN12_Pin 63
#define PIN12_In PINK
#define PIN12_Bit PK1
#define PIN12_Mask _BV(PIN12_Bit)
#define pin12In() ((PIN12_In & PIN12_Mask) != 0)
#define pin12Set() ((PIN12_In & PIN12_Mask) != 0)
#define pin12Clr() ((PIN12_In & PIN12_Mask) == 0)

#define PIN13_Pin 62
#define PIN13_In PINK
#define PIN13_Bit PK0
#define PIN13_Mask _BV(PIN13_Bit)
#define pin13In() ((PIN13_In & PIN13_Mask) != 0)
#define pin13Set() ((PIN13_In & PIN13_Mask) != 0)
#define pin13Clr() ((PIN13_In & PIN13_Mask) == 0)

#define PIN15_Pin 2
#define PIN15_In PINE
#define PIN15_Bit PE4
#define PIN15_Mask _BV(PIN15_Bit)
#define pin15In() ((PIN15_In & PIN15_Mask) != 0)
#define pin15Set() ((PIN15_In & PIN15_Mask) != 0)
#define pin15Clr() ((PIN15_In & PIN15_Mask) == 0)

#define PIN1_Pin 3
#define PIN1_Port PORTE
#define PIN1_DDR DDRE
#define PIN1_In PINE
#define PIN1_Bit PE5
#define PIN1_Mask _BV(PIN1_Bit)
#define pin1Read() ((PIN1_Port & PIN1_Mask) != 0)
#define pin1Set() PIN1_Port |= PIN1_Mask
#define pin1Clr() PIN1_Port &= ~PIN1_Mask

#define PIN14_Pin 7
#define PIN14_Port PORTH
#define PIN14_DDR DDRH
#define PIN14_In PINH
#define PIN14_Bit PH4
#define PIN14_Mask _BV(PIN14_Bit)
#define pin14Read() ((PIN14_Port & PIN14_Mask) != 0)
#define pin14Set() PIN14_Port |= PIN14_Mask
#define pin14Clr() PIN14_Port &= ~PIN14_Mask

#define PIN16_Pin 8
#define PIN16_Port PORTH
#define PIN16_DDR DDRH
#define PIN16_In PINH
#define PIN16_Bit PH5
#define PIN16_Mask _BV(PIN16_Bit)
#define pin16Read() ((PIN16_Port & PIN16_Mask) != 0)
#define pin16Set() PIN16_Port |= PIN16_Mask
#define pin16Clr() PIN16_Port &= ~PIN16_Mask

#define PIN17_Pin 9
#define PIN17_Port PORTH
#define PIN17_DDR DDRH
#define PIN17_In PINH
#define PIN17_Bit PH6
#define PIN17_Mask _BV(PIN17_Bit)
#define pin17Read() ((PIN17_Port & PIN17_Mask) != 0)
#define pin17Set() PIN17_Port |= PIN17_Mask
#define pin17Clr() PIN17_Port &= ~PIN17_Mask

#define OUT1_Pin 57
#define OUT1_Port PORTF
#define OUT1_DDR DDRF
#define OUT1_In PINF
#define OUT1_Bit PF3
#define OUT1_Mask _BV(OUT1_Bit)
#define out1Read() ((OUT1_Port & OUT1_Mask) != 0)
#define out1Set() OUT1_Port |= OUT1_Mask
#define out1Clr() OUT1_Port &= ~OUT1_Mask

#define OUT2_Pin 55
#define OUT2_Port PORTF
#define OUT2_DDR DDRF
#define OUT2_In PINF
#define OUT2_Bit PF1
#define OUT2_Mask _BV(OUT2_Bit)
#define out2Read() ((OUT2_Port & OUT2_Mask) != 0)
#define out2Set() OUT2_Port |= OUT2_Mask
#define out2Clr() OUT2_Port &= ~OUT2_Mask

#define OUT3_Pin 54
#define OUT3_Port PORTF
#define OUT3_DDR DDRF
#define OUT3_In PINF
#define OUT3_Bit PF0
#define OUT3_Mask _BV(OUT3_Bit)
#define out3Read() ((OUT3_Port & OUT3_Mask) != 0)
#define out3Set() OUT3_Port |= OUT3_Mask
#define out3Clr() OUT3_Port &= ~OUT3_Mask

#define OUT4_Pin 56
#define OUT4_Port PORTF
#define OUT4_DDR DDRF
#define OUT4_In PINF
#define OUT4_Bit PF2
#define OUT4_Mask _BV(OUT4_Bit)
#define out4Read() ((OUT4_Port & OUT4_Mask) != 0)
#define out4Set() OUT4_Port |= OUT4_Mask
#define out4Clr() OUT4_Port &= ~OUT4_Mask

#define SW12_V1_Pin 41
#define SW12_V1_Port PORTG
#define SW12_V1_DDR DDRG
#define SW12_V1_In PING
#define SW12_V1_Bit PG0
#define SW12_V1_Mask _BV(SW12_V1_Bit)
#define sw12V1Read() ((SW12_V1_Port & SW12_V1_Mask) != 0)
#define sw12V1Set() SW12_V1_Port |= SW12_V1_Mask
#define sw12V1Clr() SW12_V1_Port &= ~SW12_V1_Mask

#define SW12_V2_Pin 43
#define SW12_V2_Port PORTL
#define SW12_V2_DDR DDRL
#define SW12_V2_In PINL
#define SW12_V2_Bit PL6
#define SW12_V2_Mask _BV(SW12_V2_Bit)
#define sw12V2Read() ((SW12_V2_Port & SW12_V2_Mask) != 0)
#define sw12V2Set() SW12_V2_Port |= SW12_V2_Mask
#define sw12V2Clr() SW12_V2_Port &= ~SW12_V2_Mask

#define EXTCTL0_Pin 52
#define EXTCTL0_Port PORTB
#define EXTCTL0_DDR DDRB
#define EXTCTL0_In PINB
#define EXTCTL0_Bit PB1
#define EXTCTL0_Mask _BV(EXTCTL0_Bit)
#define extctl0Read() ((EXTCTL0_Port & EXTCTL0_Mask) != 0)
#define extctl0Set() EXTCTL0_Port |= EXTCTL0_Mask
#define extctl0Clr() EXTCTL0_Port &= ~EXTCTL0_Mask

#define EXTCTL1_Pin 53
#define EXTCTL1_Port PORTB
#define EXTCTL1_DDR DDRB
#define EXTCTL1_In PINB
#define EXTCTL1_Bit PB0
#define EXTCTL1_Mask _BV(EXTCTL1_Bit)
#define extctl1Read() ((EXTCTL1_Port & EXTCTL1_Mask) != 0)
#define extctl1Set() EXTCTL1_Port |= EXTCTL1_Mask
#define extctl1Clr() EXTCTL1_Port &= ~EXTCTL1_Mask

#define EXTCTL2_Pin 50
#define EXTCTL2_Port PORTB
#define EXTCTL2_DDR DDRB
#define EXTCTL2_In PINB
#define EXTCTL2_Bit PB3
#define EXTCTL2_Mask _BV(EXTCTL2_Bit)
#define extctl2Read() ((EXTCTL2_Port & EXTCTL2_Mask) != 0)
#define extctl2Set() EXTCTL2_Port |= EXTCTL2_Mask
#define extctl2Clr() EXTCTL2_Port &= ~EXTCTL2_Mask

#define EXTCTL3_Pin 51
#define EXTCTL3_Port PORTB
#define EXTCTL3_DDR DDRB
#define EXTCTL3_In PINB
#define EXTCTL3_Bit PB2
#define EXTCTL3_Mask _BV(EXTCTL3_Bit)
#define extctl3Read() ((EXTCTL3_Port & EXTCTL3_Mask) != 0)
#define extctl3Set() EXTCTL3_Port |= EXTCTL3_Mask
#define extctl3Clr() EXTCTL3_Port &= ~EXTCTL3_Mask

#endif
#ifdef ARDUINO_AVR_PROMICRO

#define SPINDLE_PWM_TEST     0
#define CHARGE_PUMP_TEST     0
#define TMR2_PWM_TIMER       1
#define TMR3_PWM_TIMER       0

#define OC0A_Port PIND
#define OC0A_Mask _BV(PD6)

#define OC0B_Port PIND
#define OC0B_Mask _BV(PD5)

#define OC1A_Port PINB
#define OC1A_Mask _BV(PB1)

#define OC1B_Port PINB
#define OC1B_Mask _BV(PB2)

#define OC2A_Port PINB
#define OC2A_Mask _BV(PB3)

#define OC2B_Port PIND
#define OC2B_Mask _BV(PD3)

#define T1_PWM_A_Pin 9
#define T1_PWM_A_Port PORTB
#define T1_PWM_A_DDR DDRB
#define T1_PWM_A_In PINB
#define T1_PWM_A_Bit PB1
#define T1_PWM_A_Mask _BV(T1_PWM_A_Bit)
#define t1PwmARead() ((T1_PWM_A_Port & T1_PWM_A_Mask) != 0)
#define t1PwmASet() T1_PWM_A_Port |= T1_PWM_A_Mask
#define t1PwmAClr() T1_PWM_A_Port &= ~T1_PWM_A_Mask

#define CHG_PUMP_Pin 2
#define CHG_PUMP_In PIND
#define CHG_PUMP_Bit PD2
#define CHG_PUMP_Mask _BV(CHG_PUMP_Bit)
#define chgPumpIn() ((CHG_PUMP_In & CHG_PUMP_Mask) != 0)
#define chgPumpSet() ((CHG_PUMP_In & CHG_PUMP_Mask) != 0)
#define chgPumpClr() ((CHG_PUMP_In & CHG_PUMP_Mask) == 0)
#define chgPumpIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 0);\
	EICRA |= (_BV(ISC01)|_BV(ISC00)) << 0;\
	EIMSK |= (_BV(INT0) << 0)

#define PWM_Pin 3
#define PWM_In PIND
#define PWM_Bit PD3
#define PWM_Mask _BV(PWM_Bit)
#define pwmIn() ((PWM_In & PWM_Mask) != 0)
#define pwmSet() ((PWM_In & PWM_Mask) != 0)
#define pwmClr() ((PWM_In & PWM_Mask) == 0)
#define pwmIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 2);\
	EICRA |= (_BV(ISC00)) << 2;\
	EIMSK |= (_BV(INT0) << 1)

#define SP_FWD_Pin 4
#define SP_FWD_In PIND
#define SP_FWD_Bit PD4
#define SP_FWD_Mask _BV(SP_FWD_Bit)
#define spFwdIn() ((SP_FWD_In & SP_FWD_Mask) != 0)
#define spFwdSet() ((SP_FWD_In & SP_FWD_Mask) != 0)
#define spFwdClr() ((SP_FWD_In & SP_FWD_Mask) == 0)

#define SP_REV_Pin 5
#define SP_REV_In PIND
#define SP_REV_Bit PD5
#define SP_REV_Mask _BV(SP_REV_Bit)
#define spRevIn() ((SP_REV_In & SP_REV_Mask) != 0)
#define spRevSet() ((SP_REV_In & SP_REV_Mask) != 0)
#define spRevClr() ((SP_REV_In & SP_REV_Mask) == 0)

#define E_STOP_NO_Pin 18
#define E_STOP_NO_In PINC
#define E_STOP_NO_Bit PC4
#define E_STOP_NO_Mask _BV(E_STOP_NO_Bit)
#define eStopNoIn() ((E_STOP_NO_In & E_STOP_NO_Mask) != 0)
#define eStopNoSet() ((E_STOP_NO_In & E_STOP_NO_Mask) == 0)
#define eStopNoClr() ((E_STOP_NO_In & E_STOP_NO_Mask) != 0)

#define E_STOP_NC_Pin 19
#define E_STOP_NC_In PINC
#define E_STOP_NC_Bit PC5
#define E_STOP_NC_Mask _BV(E_STOP_NC_Bit)
#define eStopNcIn() ((E_STOP_NC_In & E_STOP_NC_Mask) != 0)
#define eStopNcSet() ((E_STOP_NC_In & E_STOP_NC_Mask) != 0)
#define eStopNcClr() ((E_STOP_NC_In & E_STOP_NC_Mask) == 0)

#define E_STOP_RST_Pin 8
#define E_STOP_RST_In PINB
#define E_STOP_RST_Bit PB0
#define E_STOP_RST_Mask _BV(E_STOP_RST_Bit)
#define eStopRstIn() ((E_STOP_RST_In & E_STOP_RST_Mask) != 0)
#define eStopRstSet() ((E_STOP_RST_In & E_STOP_RST_Mask) == 0)
#define eStopRstClr() ((E_STOP_RST_In & E_STOP_RST_Mask) != 0)

#define FAST_PWM_Pin 9
#define FAST_PWM_Port PORTB
#define FAST_PWM_DDR DDRB
#define FAST_PWM_In PINB
#define FAST_PWM_Bit PB1
#define FAST_PWM_Mask _BV(FAST_PWM_Bit)
#define fastPwmRead() ((FAST_PWM_Port & FAST_PWM_Mask) != 0)
#define fastPwmSet() FAST_PWM_Port |= FAST_PWM_Mask
#define fastPwmClr() FAST_PWM_Port &= ~FAST_PWM_Mask

#define VFD_FWD_Pin 6
#define VFD_FWD_Port PORTD
#define VFD_FWD_DDR DDRD
#define VFD_FWD_In PIND
#define VFD_FWD_Bit PD6
#define VFD_FWD_Mask _BV(VFD_FWD_Bit)
#define vfdFwdRead() ((VFD_FWD_Port & VFD_FWD_Mask) != 0)
#define vfdFwdSet() VFD_FWD_Port |= VFD_FWD_Mask
#define vfdFwdClr() VFD_FWD_Port &= ~VFD_FWD_Mask

#define VFD_REV_Pin 7
#define VFD_REV_Port PORTD
#define VFD_REV_DDR DDRD
#define VFD_REV_In PIND
#define VFD_REV_Bit PD7
#define VFD_REV_Mask _BV(VFD_REV_Bit)
#define vfdRevRead() ((VFD_REV_Port & VFD_REV_Mask) != 0)
#define vfdRevSet() VFD_REV_Port |= VFD_REV_Mask
#define vfdRevClr() VFD_REV_Port &= ~VFD_REV_Mask

#define SP_ENA_Pin 14
#define SP_ENA_Port PORTC
#define SP_ENA_DDR DDRC
#define SP_ENA_In PINC
#define SP_ENA_Bit PC0
#define SP_ENA_Mask _BV(SP_ENA_Bit)
#define spEnaRead() ((SP_ENA_Port & SP_ENA_Mask) != 0)
#define spEnaSet() SP_ENA_Port |= SP_ENA_Mask
#define spEnaClr() SP_ENA_Port &= ~SP_ENA_Mask

#define STEP_DIS_Pin 15
#define STEP_DIS_Port PORTC
#define STEP_DIS_DDR DDRC
#define STEP_DIS_In PINC
#define STEP_DIS_Bit PC1
#define STEP_DIS_Mask _BV(STEP_DIS_Bit)
#define stepDisRead() ((STEP_DIS_Port & STEP_DIS_Mask) != 0)
#define stepDisSet() STEP_DIS_Port |= STEP_DIS_Mask
#define stepDisClr() STEP_DIS_Port &= ~STEP_DIS_Mask

#define E_STOP_RLY_Pin 17
#define E_STOP_RLY_Port PORTC
#define E_STOP_RLY_DDR DDRC
#define E_STOP_RLY_In PINC
#define E_STOP_RLY_Bit PC3
#define E_STOP_RLY_Mask _BV(E_STOP_RLY_Bit)
#define eStopRlyRead() ((E_STOP_RLY_Port & E_STOP_RLY_Mask) != 0)
#define eStopRlySet() E_STOP_RLY_Port |= E_STOP_RLY_Mask
#define eStopRlyClr() E_STOP_RLY_Port &= ~E_STOP_RLY_Mask

#define E_STOP_PC_Pin 16
#define E_STOP_PC_Port PORTC
#define E_STOP_PC_DDR DDRC
#define E_STOP_PC_In PINC
#define E_STOP_PC_Bit PC2
#define E_STOP_PC_Mask _BV(E_STOP_PC_Bit)
#define eStopPcRead() ((E_STOP_PC_Port & E_STOP_PC_Mask) != 0)
#define eStopPcSet() E_STOP_PC_Port |= E_STOP_PC_Mask
#define eStopPcClr() E_STOP_PC_Port &= ~E_STOP_PC_Mask

#define W_DOG_Pin 10
#define W_DOG_Port PORTB
#define W_DOG_DDR DDRB
#define W_DOG_In PINB
#define W_DOG_Bit PB2
#define W_DOG_Mask _BV(W_DOG_Bit)
#define wDogRead() ((W_DOG_Port & W_DOG_Mask) != 0)
#define wDogSet() W_DOG_Port |= W_DOG_Mask
#define wDogClr() W_DOG_Port &= ~W_DOG_Mask

#define ledRead() 0
#define ledSet()
#define ledClr()

#define t2Read() 0
#define t2Set()
#define t2Clr()

#define dbg0Read() 0
#define dbg0Set()
#define dbg0Clr()

#define dbg1Read() 0
#define dbg1Set()
#define dbg1Clr()

#define dbg2Read() 0
#define dbg2Set()
#define dbg2Clr()

#define dbg3Read() 0
#define dbg3Set()
#define dbg3Clr()

#endif
#ifdef ARDUINO_AVR_PROMICRO16

#define SPINDLE_PWM_TEST     0
#define CHARGE_PUMP_TEST     0
#define TMR2_PWM_TIMER       0
#define TMR3_PWM_TIMER       1

#define OC0A_Port PINB
#define OC0A_Mask _BV(PB7)

#define OC0B_Port PIND
#define OC0B_Mask _BV(PD0)

#define OC1A_Port PINB
#define OC1A_Mask _BV(PB5)

#define OC1B_Port PINB
#define OC1B_Mask _BV(PB6)

#define OC1C_Port PINB
#define OC1C_Mask _BV(PB7)

#define OC3A_Port PINC
#define OC3A_Mask _BV(PC6)

#define OC4A_Port PINC
#define OC4A_Mask _BV(PC7)

#define OC4AN_Port PINC
#define OC4AN_Mask _BV(PC6)

#define OC4B_Port PINB
#define OC4B_Mask _BV(PB6)

#define OC4BN_Port PINB
#define OC4BN_Mask _BV(PB5)

#define OC4D_Port PIND
#define OC4D_Mask _BV(PD7)

#define OC4DN_Port PIND
#define OC4DN_Mask _BV(PD6)

#define T1_PWM_A_Pin 9
#define T1_PWM_A_Port PORTB
#define T1_PWM_A_DDR DDRB
#define T1_PWM_A_In PINB
#define T1_PWM_A_Bit PB5
#define T1_PWM_A_Mask _BV(T1_PWM_A_Bit)
#define t1PwmARead() ((T1_PWM_A_Port & T1_PWM_A_Mask) != 0)
#define t1PwmASet() T1_PWM_A_Port |= T1_PWM_A_Mask
#define t1PwmAClr() T1_PWM_A_Port &= ~T1_PWM_A_Mask

#define CHG_PUMP_Pin 2
#define CHG_PUMP_In PIND
#define CHG_PUMP_Bit PD1
#define CHG_PUMP_Mask _BV(CHG_PUMP_Bit)
#define chgPumpIn() ((CHG_PUMP_In & CHG_PUMP_Mask) != 0)
#define chgPumpSet() ((CHG_PUMP_In & CHG_PUMP_Mask) != 0)
#define chgPumpClr() ((CHG_PUMP_In & CHG_PUMP_Mask) == 0)
#define chgPumpIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 2);\
	EICRA |= (_BV(ISC01)|_BV(ISC00)) << 2;\
	EIMSK |= (_BV(INT0) << 1)

#define PWM_Pin 3
#define PWM_In PIND
#define PWM_Bit PD0
#define PWM_Mask _BV(PWM_Bit)
#define pwmIn() ((PWM_In & PWM_Mask) != 0)
#define pwmSet() ((PWM_In & PWM_Mask) != 0)
#define pwmClr() ((PWM_In & PWM_Mask) == 0)
#define pwmIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 0);\
	EICRA |= (_BV(ISC00)) << 0;\
	EIMSK |= (_BV(INT0) << 0)

#define SP_FWD_Pin 4
#define SP_FWD_In PIND
#define SP_FWD_Bit PD4
#define SP_FWD_Mask _BV(SP_FWD_Bit)
#define spFwdIn() ((SP_FWD_In & SP_FWD_Mask) != 0)
#define spFwdSet() ((SP_FWD_In & SP_FWD_Mask) != 0)
#define spFwdClr() ((SP_FWD_In & SP_FWD_Mask) == 0)

#define SP_REV_Pin 5
#define SP_REV_In PINC
#define SP_REV_Bit PC6
#define SP_REV_Mask _BV(SP_REV_Bit)
#define spRevIn() ((SP_REV_In & SP_REV_Mask) != 0)
#define spRevSet() ((SP_REV_In & SP_REV_Mask) != 0)
#define spRevClr() ((SP_REV_In & SP_REV_Mask) == 0)

#define E_STOP_NO_Pin 14
#define E_STOP_NO_In PINB
#define E_STOP_NO_Bit PB3
#define E_STOP_NO_Mask _BV(E_STOP_NO_Bit)
#define eStopNoIn() ((E_STOP_NO_In & E_STOP_NO_Mask) != 0)
#define eStopNoSet() ((E_STOP_NO_In & E_STOP_NO_Mask) == 0)
#define eStopNoClr() ((E_STOP_NO_In & E_STOP_NO_Mask) != 0)

#define E_STOP_NC_Pin 15
#define E_STOP_NC_In PINB
#define E_STOP_NC_Bit PB1
#define E_STOP_NC_Mask _BV(E_STOP_NC_Bit)
#define eStopNcIn() ((E_STOP_NC_In & E_STOP_NC_Mask) != 0)
#define eStopNcSet() ((E_STOP_NC_In & E_STOP_NC_Mask) != 0)
#define eStopNcClr() ((E_STOP_NC_In & E_STOP_NC_Mask) == 0)

#define E_STOP_RST_Pin 6
#define E_STOP_RST_In PIND
#define E_STOP_RST_Bit PD7
#define E_STOP_RST_Mask _BV(E_STOP_RST_Bit)
#define eStopRstIn() ((E_STOP_RST_In & E_STOP_RST_Mask) != 0)
#define eStopRstSet() ((E_STOP_RST_In & E_STOP_RST_Mask) != 0)
#define eStopRstClr() ((E_STOP_RST_In & E_STOP_RST_Mask) == 0)

#define FAST_PWM_Pin 9
#define FAST_PWM_Port PORTB
#define FAST_PWM_DDR DDRB
#define FAST_PWM_In PINB
#define FAST_PWM_Bit PB5
#define FAST_PWM_Mask _BV(FAST_PWM_Bit)
#define fastPwmRead() ((FAST_PWM_Port & FAST_PWM_Mask) != 0)
#define fastPwmSet() FAST_PWM_Port |= FAST_PWM_Mask
#define fastPwmClr() FAST_PWM_Port &= ~FAST_PWM_Mask

#define VFD_FWD_Pin 7
#define VFD_FWD_Port PORTE
#define VFD_FWD_DDR DDRE
#define VFD_FWD_In PINE
#define VFD_FWD_Bit PE6
#define VFD_FWD_Mask _BV(VFD_FWD_Bit)
#define vfdFwdRead() ((VFD_FWD_Port & VFD_FWD_Mask) != 0)
#define vfdFwdSet() VFD_FWD_Port |= VFD_FWD_Mask
#define vfdFwdClr() VFD_FWD_Port &= ~VFD_FWD_Mask

#define VFD_REV_Pin 8
#define VFD_REV_Port PORTB
#define VFD_REV_DDR DDRB
#define VFD_REV_In PINB
#define VFD_REV_Bit PB4
#define VFD_REV_Mask _BV(VFD_REV_Bit)
#define vfdRevRead() ((VFD_REV_Port & VFD_REV_Mask) != 0)
#define vfdRevSet() VFD_REV_Port |= VFD_REV_Mask
#define vfdRevClr() VFD_REV_Port &= ~VFD_REV_Mask

#define STEP_DIS_Pin 21
#define STEP_DIS_Port PORTF
#define STEP_DIS_DDR DDRF
#define STEP_DIS_In PINF
#define STEP_DIS_Bit PF4
#define STEP_DIS_Mask _BV(STEP_DIS_Bit)
#define stepDisRead() ((STEP_DIS_Port & STEP_DIS_Mask) != 0)
#define stepDisSet() STEP_DIS_Port |= STEP_DIS_Mask
#define stepDisClr() STEP_DIS_Port &= ~STEP_DIS_Mask

#define E_STOP_RLY_Pin 20
#define E_STOP_RLY_Port PORTF
#define E_STOP_RLY_DDR DDRF
#define E_STOP_RLY_In PINF
#define E_STOP_RLY_Bit PF5
#define E_STOP_RLY_Mask _BV(E_STOP_RLY_Bit)
#define eStopRlyRead() ((E_STOP_RLY_Port & E_STOP_RLY_Mask) != 0)
#define eStopRlySet() E_STOP_RLY_Port |= E_STOP_RLY_Mask
#define eStopRlyClr() E_STOP_RLY_Port &= ~E_STOP_RLY_Mask

#define SP_ENA_Pin 19
#define SP_ENA_Port PORTF
#define SP_ENA_DDR DDRF
#define SP_ENA_In PINF
#define SP_ENA_Bit PF6
#define SP_ENA_Mask _BV(SP_ENA_Bit)
#define spEnaRead() ((SP_ENA_Port & SP_ENA_Mask) != 0)
#define spEnaSet() SP_ENA_Port |= SP_ENA_Mask
#define spEnaClr() SP_ENA_Port &= ~SP_ENA_Mask

#define E_STOP_PC_Pin 18
#define E_STOP_PC_Port PORTF
#define E_STOP_PC_DDR DDRF
#define E_STOP_PC_In PINF
#define E_STOP_PC_Bit PF7
#define E_STOP_PC_Mask _BV(E_STOP_PC_Bit)
#define eStopPcRead() ((E_STOP_PC_Port & E_STOP_PC_Mask) != 0)
#define eStopPcSet() E_STOP_PC_Port |= E_STOP_PC_Mask
#define eStopPcClr() E_STOP_PC_Port &= ~E_STOP_PC_Mask

#define SWITCH_Pin 16
#define SWITCH_Port PORTB
#define SWITCH_DDR DDRB
#define SWITCH_In PINB
#define SWITCH_Bit PB2
#define SWITCH_Mask _BV(SWITCH_Bit)
#define switchRead() ((SWITCH_Port & SWITCH_Mask) != 0)
#define switchSet() SWITCH_Port |= SWITCH_Mask
#define switchClr() SWITCH_Port &= ~SWITCH_Mask

#define W_DOG_Pin 10
#define W_DOG_Port PORTB
#define W_DOG_DDR DDRB
#define W_DOG_In PINB
#define W_DOG_Bit PB6
#define W_DOG_Mask _BV(W_DOG_Bit)
#define wDogRead() ((W_DOG_Port & W_DOG_Mask) != 0)
#define wDogSet() W_DOG_Port |= W_DOG_Mask
#define wDogClr() W_DOG_Port &= ~W_DOG_Mask

#define LED_Pin 30
#define LED_Port PORTD
#define LED_DDR DDRD
#define LED_In PIND
#define LED_Bit PD5
#define LED_Mask _BV(LED_Bit)
#define ledRead() ((LED_Port & LED_Mask) != 0)
#define ledSet() LED_Port |= LED_Mask
#define ledClr() LED_Port &= ~LED_Mask

#define t2Read() 0
#define t2Set()
#define t2Clr()

#define dbg0Read() 0
#define dbg0Set()
#define dbg0Clr()

#define dbg1Read() 0
#define dbg1Set()
#define dbg1Clr()

#define dbg2Read() 0
#define dbg2Set()
#define dbg2Clr()

#define dbg3Read() 0
#define dbg3Set()
#define dbg3Clr()

#endif
#ifdef ARDUINO_AVR_LEONARDO

#define SPINDLE_PWM_TEST     0
#define CHARGE_PUMP_TEST     0
#define TMR2_PWM_TIMER       0
#define TMR3_PWM_TIMER       1

#define OC0A_Port PINB
#define OC0A_Mask _BV(PB7)

#define OC0B_Port PIND
#define OC0B_Mask _BV(PD0)

#define OC1A_Port PINB
#define OC1A_Mask _BV(PB5)

#define OC1B_Port PINB
#define OC1B_Mask _BV(PB6)

#define OC1C_Port PINB
#define OC1C_Mask _BV(PB7)

#define OC3A_Port PINC
#define OC3A_Mask _BV(PC6)

#define OC4A_Port PINC
#define OC4A_Mask _BV(PC7)

#define OC4AN_Port PINC
#define OC4AN_Mask _BV(PC6)

#define OC4B_Port PINB
#define OC4B_Mask _BV(PB6)

#define OC4BN_Port PINB
#define OC4BN_Mask _BV(PB5)

#define OC4D_Port PIND
#define OC4D_Mask _BV(PD7)

#define OC4DN_Port PIND
#define OC4DN_Mask _BV(PD6)

#define T1_PWM_A_Pin 9
#define T1_PWM_A_Port PORTB
#define T1_PWM_A_DDR DDRB
#define T1_PWM_A_In PINB
#define T1_PWM_A_Bit PB5
#define T1_PWM_A_Mask _BV(T1_PWM_A_Bit)
#define t1PwmARead() ((T1_PWM_A_Port & T1_PWM_A_Mask) != 0)
#define t1PwmASet() T1_PWM_A_Port |= T1_PWM_A_Mask
#define t1PwmAClr() T1_PWM_A_Port &= ~T1_PWM_A_Mask

#define CHG_PUMP_Pin 2
#define CHG_PUMP_In PIND
#define CHG_PUMP_Bit PD1
#define CHG_PUMP_Mask _BV(CHG_PUMP_Bit)
#define chgPumpIn() ((CHG_PUMP_In & CHG_PUMP_Mask) != 0)
#define chgPumpSet() ((CHG_PUMP_In & CHG_PUMP_Mask) != 0)
#define chgPumpClr() ((CHG_PUMP_In & CHG_PUMP_Mask) == 0)
#define chgPumpIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 2);\
	EICRA |= (_BV(ISC01)|_BV(ISC00)) << 2;\
	EIMSK |= (_BV(INT0) << 1)

#define PWM_Pin 3
#define PWM_In PIND
#define PWM_Bit PD0
#define PWM_Mask _BV(PWM_Bit)
#define pwmIn() ((PWM_In & PWM_Mask) != 0)
#define pwmSet() ((PWM_In & PWM_Mask) != 0)
#define pwmClr() ((PWM_In & PWM_Mask) == 0)
#define pwmIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 0);\
	EICRA |= (_BV(ISC00)) << 0;\
	EIMSK |= (_BV(INT0) << 0)

#define SP_FWD_Pin 4
#define SP_FWD_In PIND
#define SP_FWD_Bit PD4
#define SP_FWD_Mask _BV(SP_FWD_Bit)
#define spFwdIn() ((SP_FWD_In & SP_FWD_Mask) != 0)
#define spFwdSet() ((SP_FWD_In & SP_FWD_Mask) != 0)
#define spFwdClr() ((SP_FWD_In & SP_FWD_Mask) == 0)

#define SP_REV_Pin 5
#define SP_REV_In PINC
#define SP_REV_Bit PC6
#define SP_REV_Mask _BV(SP_REV_Bit)
#define spRevIn() ((SP_REV_In & SP_REV_Mask) != 0)
#define spRevSet() ((SP_REV_In & SP_REV_Mask) != 0)
#define spRevClr() ((SP_REV_In & SP_REV_Mask) == 0)

#define E_STOP_NO_Pin 14
#define E_STOP_NO_In PINB
#define E_STOP_NO_Bit PB3
#define E_STOP_NO_Mask _BV(E_STOP_NO_Bit)
#define eStopNoIn() ((E_STOP_NO_In & E_STOP_NO_Mask) != 0)
#define eStopNoSet() ((E_STOP_NO_In & E_STOP_NO_Mask) == 0)
#define eStopNoClr() ((E_STOP_NO_In & E_STOP_NO_Mask) != 0)

#define E_STOP_NC_Pin 15
#define E_STOP_NC_In PINB
#define E_STOP_NC_Bit PB1
#define E_STOP_NC_Mask _BV(E_STOP_NC_Bit)
#define eStopNcIn() ((E_STOP_NC_In & E_STOP_NC_Mask) != 0)
#define eStopNcSet() ((E_STOP_NC_In & E_STOP_NC_Mask) != 0)
#define eStopNcClr() ((E_STOP_NC_In & E_STOP_NC_Mask) == 0)

#define E_STOP_RST_Pin 6
#define E_STOP_RST_In PIND
#define E_STOP_RST_Bit PD7
#define E_STOP_RST_Mask _BV(E_STOP_RST_Bit)
#define eStopRstIn() ((E_STOP_RST_In & E_STOP_RST_Mask) != 0)
#define eStopRstSet() ((E_STOP_RST_In & E_STOP_RST_Mask) != 0)
#define eStopRstClr() ((E_STOP_RST_In & E_STOP_RST_Mask) == 0)

#define FAST_PWM_Pin 9
#define FAST_PWM_Port PORTB
#define FAST_PWM_DDR DDRB
#define FAST_PWM_In PINB
#define FAST_PWM_Bit PB5
#define FAST_PWM_Mask _BV(FAST_PWM_Bit)
#define fastPwmRead() ((FAST_PWM_Port & FAST_PWM_Mask) != 0)
#define fastPwmSet() FAST_PWM_Port |= FAST_PWM_Mask
#define fastPwmClr() FAST_PWM_Port &= ~FAST_PWM_Mask

#define VFD_FWD_Pin 7
#define VFD_FWD_Port PORTE
#define VFD_FWD_DDR DDRE
#define VFD_FWD_In PINE
#define VFD_FWD_Bit PE6
#define VFD_FWD_Mask _BV(VFD_FWD_Bit)
#define vfdFwdRead() ((VFD_FWD_Port & VFD_FWD_Mask) != 0)
#define vfdFwdSet() VFD_FWD_Port |= VFD_FWD_Mask
#define vfdFwdClr() VFD_FWD_Port &= ~VFD_FWD_Mask

#define VFD_REV_Pin 8
#define VFD_REV_Port PORTB
#define VFD_REV_DDR DDRB
#define VFD_REV_In PINB
#define VFD_REV_Bit PB4
#define VFD_REV_Mask _BV(VFD_REV_Bit)
#define vfdRevRead() ((VFD_REV_Port & VFD_REV_Mask) != 0)
#define vfdRevSet() VFD_REV_Port |= VFD_REV_Mask
#define vfdRevClr() VFD_REV_Port &= ~VFD_REV_Mask

#define STEP_DIS_Pin 21
#define STEP_DIS_Port PORTF
#define STEP_DIS_DDR DDRF
#define STEP_DIS_In PINF
#define STEP_DIS_Bit PF4
#define STEP_DIS_Mask _BV(STEP_DIS_Bit)
#define stepDisRead() ((STEP_DIS_Port & STEP_DIS_Mask) != 0)
#define stepDisSet() STEP_DIS_Port |= STEP_DIS_Mask
#define stepDisClr() STEP_DIS_Port &= ~STEP_DIS_Mask

#define E_STOP_RLY_Pin 20
#define E_STOP_RLY_Port PORTF
#define E_STOP_RLY_DDR DDRF
#define E_STOP_RLY_In PINF
#define E_STOP_RLY_Bit PF5
#define E_STOP_RLY_Mask _BV(E_STOP_RLY_Bit)
#define eStopRlyRead() ((E_STOP_RLY_Port & E_STOP_RLY_Mask) != 0)
#define eStopRlySet() E_STOP_RLY_Port |= E_STOP_RLY_Mask
#define eStopRlyClr() E_STOP_RLY_Port &= ~E_STOP_RLY_Mask

#define SP_ENA_Pin 19
#define SP_ENA_Port PORTF
#define SP_ENA_DDR DDRF
#define SP_ENA_In PINF
#define SP_ENA_Bit PF6
#define SP_ENA_Mask _BV(SP_ENA_Bit)
#define spEnaRead() ((SP_ENA_Port & SP_ENA_Mask) != 0)
#define spEnaSet() SP_ENA_Port |= SP_ENA_Mask
#define spEnaClr() SP_ENA_Port &= ~SP_ENA_Mask

#define E_STOP_PC_Pin 18
#define E_STOP_PC_Port PORTF
#define E_STOP_PC_DDR DDRF
#define E_STOP_PC_In PINF
#define E_STOP_PC_Bit PF7
#define E_STOP_PC_Mask _BV(E_STOP_PC_Bit)
#define eStopPcRead() ((E_STOP_PC_Port & E_STOP_PC_Mask) != 0)
#define eStopPcSet() E_STOP_PC_Port |= E_STOP_PC_Mask
#define eStopPcClr() E_STOP_PC_Port &= ~E_STOP_PC_Mask

#define SWITCH_Pin 16
#define SWITCH_Port PORTB
#define SWITCH_DDR DDRB
#define SWITCH_In PINB
#define SWITCH_Bit PB2
#define SWITCH_Mask _BV(SWITCH_Bit)
#define switchRead() ((SWITCH_Port & SWITCH_Mask) != 0)
#define switchSet() SWITCH_Port |= SWITCH_Mask
#define switchClr() SWITCH_Port &= ~SWITCH_Mask

#define W_DOG_Pin 10
#define W_DOG_Port PORTB
#define W_DOG_DDR DDRB
#define W_DOG_In PINB
#define W_DOG_Bit PB6
#define W_DOG_Mask _BV(W_DOG_Bit)
#define wDogRead() ((W_DOG_Port & W_DOG_Mask) != 0)
#define wDogSet() W_DOG_Port |= W_DOG_Mask
#define wDogClr() W_DOG_Port &= ~W_DOG_Mask

#define LED_Pin 30
#define LED_Port PORTD
#define LED_DDR DDRD
#define LED_In PIND
#define LED_Bit PD5
#define LED_Mask _BV(LED_Bit)
#define ledRead() ((LED_Port & LED_Mask) != 0)
#define ledSet() LED_Port |= LED_Mask
#define ledClr() LED_Port &= ~LED_Mask

#define t2Read() 0
#define t2Set()
#define t2Clr()

#define dbg0Read() 0
#define dbg0Set()
#define dbg0Clr()

#define dbg1Read() 0
#define dbg1Set()
#define dbg1Clr()

#define dbg2Read() 0
#define dbg2Set()
#define dbg2Clr()

#define dbg3Read() 0
#define dbg3Set()
#define dbg3Clr()

#endif
