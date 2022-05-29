#include <stdint.h>
#define NO_REM_MACROS
#include "megaParmList.h"

#include "megaStruct.h"

T_MEGA_VAR mVar;

void setMegaVar(int parm, T_DATA_UNION val);
void getMegaVar(int parm, P_DATA_UNION val);

void setMegaVar(int parm, T_DATA_UNION val)
{
 switch(parm)
 {
 case M_PARM_RPM:                /*  0 0x00 rpm value */
  mVar.mParmRpm = val.t_int;
  break;

 case M_PARM_VFD_ENA:            /*  1 0x01  */
  mVar.mParmVfdEna = val.t_char;
  break;

 case M_PARM_PWM_CFG:            /*  2 0x02  */
  mVar.mParmPwmCfg = val.t_char;
  break;

 case M_PARM_ENC_TEST:           /*  3 0x03  */
  mVar.mParmEncTest = val.t_char;
  break;

 case M_PARM_ENC_LINES:          /*  4 0x04  */
  mVar.mParmEncLines = val.t_int;
  break;

 case M_PARM_MAX_PARM:           /*  5 0x05 mega maximum parameter */
  mVar.mParmMaxParm = val.t_char;
  break;

 };
}

void getMegaVar(int parm, P_DATA_UNION val)
{
 switch(parm)
 {
 case M_PARM_RPM:                /*  0 0x00 rpm value */
  val->t_int = mVar.mParmRpm;
  break;

 case M_PARM_VFD_ENA:            /*  1 0x01  */
  val->t_char = mVar.mParmVfdEna;
  break;

 case M_PARM_PWM_CFG:            /*  2 0x02  */
  val->t_char = mVar.mParmPwmCfg;
  break;

 case M_PARM_ENC_TEST:           /*  3 0x03  */
  val->t_char = mVar.mParmEncTest;
  break;

 case M_PARM_ENC_LINES:          /*  4 0x04  */
  val->t_int = mVar.mParmEncLines;
  break;

 case M_PARM_MAX_PARM:           /*  5 0x05 mega maximum parameter */
  val->t_char = mVar.mParmMaxParm;
  break;

 };
}
