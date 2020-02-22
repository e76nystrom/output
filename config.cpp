#include <Arduino.h>
#include "config.h"

void pinConfig()
{

#ifdef ARDUINO_AVR_MEGA2560

 pinMode(A_Pin, OUTPUT);
 pinMode(B_Pin, OUTPUT);
 pinMode(INDEX_Pin, OUTPUT);
 pinMode(SYNC_Pin, OUTPUT);
 pinMode(T1_PWM_A_Pin, OUTPUT);
 pinMode(T3_PWM_A_Pin, OUTPUT);
 pinMode(T4_PWM_A_Pin, OUTPUT);
 pinMode(CHG_PUMP_Pin, INPUT);
 pinMode(PWM_Pin, INPUT);
 pinMode(SP_FWD_Pin, OUTPUT);
 pinMode(SP_REV_Pin, OUTPUT);
 pinMode(E_STOP_NO_Pin, OUTPUT);
 pinMode(E_STOP_NC_Pin, OUTPUT);
 pinMode(E_STOP_RST_Pin, OUTPUT);
 pinMode(FAST_PWM_Pin, OUTPUT);
 pinMode(VFD_FWD_Pin, OUTPUT);
 pinMode(VFD_REV_Pin, OUTPUT);
 pinMode(SP_ENA_Pin, OUTPUT);
 pinMode(E_STOP_PC_Pin, OUTPUT);
 pinMode(E_STOP_RLY_Pin, OUTPUT);
 pinMode(STEP_DIS_Pin, OUTPUT);
 pinMode(W_DOG_Pin, OUTPUT);
 pinMode(PILOT_Pin, OUTPUT);
 pinMode(LED_Pin, OUTPUT);
 pinMode(T2_Pin, OUTPUT);
 pinMode(DBG0_Pin, OUTPUT);
 pinMode(DBG1_Pin, OUTPUT);
 pinMode(DBG2_Pin, OUTPUT);
 pinMode(DBG3_Pin, OUTPUT);
 pinMode(DBG4_Pin, OUTPUT);
 pinMode(DBG5_Pin, OUTPUT);
 pinMode(PIN2_Pin, INPUT);
 pinMode(PIN3_Pin, INPUT);
 pinMode(PIN4_Pin, INPUT);
 pinMode(PIN5_Pin, INPUT);
 pinMode(PIN6_Pin, INPUT);
 pinMode(PIN7_Pin, INPUT);
 pinMode(PIN8_Pin, INPUT);
 pinMode(PIN9_Pin, INPUT);
 pinMode(PIN10_Pin, INPUT);
 pinMode(PIN11_Pin, INPUT);
 pinMode(PIN12_Pin, INPUT);
 pinMode(PIN13_Pin, INPUT);
 pinMode(PIN15_Pin, INPUT);
 pinMode(PIN1_Pin, OUTPUT);
 pinMode(PIN14_Pin, OUTPUT);
 pinMode(PIN16_Pin, OUTPUT);
 pinMode(PIN17_Pin, OUTPUT);
 pinMode(OUT1_Pin, OUTPUT);
 pinMode(OUT2_Pin, OUTPUT);
 pinMode(OUT3_Pin, OUTPUT);
 pinMode(OUT4_Pin, OUTPUT);
 pinMode(SW12_V1_Pin, OUTPUT);
 pinMode(SW12_V2_Pin, OUTPUT);
 pinMode(EXTCTL0_Pin, OUTPUT);
 pinMode(EXTCTL1_Pin, OUTPUT);
 pinMode(EXTCTL2_Pin, OUTPUT);
 pinMode(EXTCTL3_Pin, OUTPUT);
 pinMode(PWMSEL_Pin, OUTPUT);

#endif

#ifdef ARDUINO_AVR_PROMICRO

 pinMode(T1_PWM_A_Pin, OUTPUT);
 pinMode(CHG_PUMP_Pin, INPUT);
 pinMode(PWM_Pin, INPUT);
 pinMode(SP_FWD_Pin, OUTPUT);
 pinMode(SP_REV_Pin, OUTPUT);
 pinMode(E_STOP_NO_Pin, OUTPUT);
 pinMode(E_STOP_NC_Pin, OUTPUT);
 pinMode(E_STOP_RST_Pin, OUTPUT);
 pinMode(FAST_PWM_Pin, OUTPUT);
 pinMode(VFD_FWD_Pin, OUTPUT);
 pinMode(VFD_REV_Pin, OUTPUT);
 pinMode(SP_ENA_Pin, OUTPUT);
 pinMode(STEP_DIS_Pin, OUTPUT);
 pinMode(E_STOP_RLY_Pin, OUTPUT);
 pinMode(E_STOP_PC_Pin, OUTPUT);
 pinMode(W_DOG_Pin, OUTPUT);

#endif

#ifdef ARDUINO_AVR_PROMICRO16

 pinMode(T1_PWM_A_Pin, OUTPUT);
 pinMode(CHG_PUMP_Pin, INPUT);
 pinMode(PWM_Pin, INPUT);
 pinMode(SP_FWD_Pin, OUTPUT);
 pinMode(SP_REV_Pin, OUTPUT);
 pinMode(E_STOP_NC_Pin, OUTPUT);
 pinMode(E_STOP_NO_Pin, OUTPUT);
 pinMode(E_STOP_RST_Pin, OUTPUT);
 pinMode(FAST_PWM_Pin, OUTPUT);
 pinMode(VFD_FWD_Pin, OUTPUT);
 pinMode(VFD_REV_Pin, OUTPUT);
 pinMode(STEP_DIS_Pin, OUTPUT);
 pinMode(E_STOP_RLY_Pin, OUTPUT);
 pinMode(SP_ENA_Pin, OUTPUT);
 pinMode(E_STOP_PC_Pin, OUTPUT);
 pinMode(SWITCH_Pin, OUTPUT);
 pinMode(W_DOG_Pin, OUTPUT);
 pinMode(LED_Pin, OUTPUT);

#endif

#ifdef ARDUINO_AVR_LEONARDO

 pinMode(T1_PWM_A_Pin, OUTPUT);
 pinMode(CHG_PUMP_Pin, INPUT);
 pinMode(PWM_Pin, INPUT);
 pinMode(SP_FWD_Pin, OUTPUT);
 pinMode(SP_REV_Pin, OUTPUT);
 pinMode(E_STOP_NC_Pin, OUTPUT);
 pinMode(E_STOP_NO_Pin, OUTPUT);
 pinMode(E_STOP_RST_Pin, OUTPUT);
 pinMode(FAST_PWM_Pin, OUTPUT);
 pinMode(VFD_FWD_Pin, OUTPUT);
 pinMode(VFD_REV_Pin, OUTPUT);
 pinMode(STEP_DIS_Pin, OUTPUT);
 pinMode(E_STOP_RLY_Pin, OUTPUT);
 pinMode(SP_ENA_Pin, OUTPUT);
 pinMode(E_STOP_PC_Pin, OUTPUT);
 pinMode(SWITCH_Pin, OUTPUT);
 pinMode(W_DOG_Pin, OUTPUT);
 pinMode(LED_Pin, OUTPUT);

#endif
}
