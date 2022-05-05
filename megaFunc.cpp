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
 case MPARM_RPM:                 /*  0 0x00 rpm value */
  mVar.mparmRpm = val.t_uint16_t;
  break;

 case MPARM_VFD_ENA:             /*  1 0x01  */
  mVar.mparmVfdEna = val.t_char;
  break;

 case MPARM_PWM_CFG:             /*  2 0x02  */
  mVar.mparmPwmCfg = val.t_char;
  break;

 case MPARM_MAX_PARM:            /*  3 0x03 mega maximum parameter */
  mVar.mparmMaxParm = val.t_char;
  break;

 };
}

void getMegaVar(int parm, P_DATA_UNION val)
{
 switch(parm)
 {
 case MPARM_RPM:                 /*  0 0x00 rpm value */
  val->t_uint16_t = mVar.mparmRpm;
  break;

 case MPARM_VFD_ENA:             /*  1 0x01  */
  val->t_char = mVar.mparmVfdEna;
  break;

 case MPARM_PWM_CFG:             /*  2 0x02  */
  val->t_char = mVar.mparmPwmCfg;
  break;

 case MPARM_MAX_PARM:            /*  3 0x03 mega maximum parameter */
  val->t_char = mVar.mparmMaxParm;
  break;

 };
}
