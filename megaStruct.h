#if !defined(MEGA_STRUCT)
#define MEGA_STRUCT

#include <stdint.h>

#if !defined(__DATA_UNION__)
#define __DATA_UNION__

typedef union uDataUnion
{
 float t_float;
 int t_int;
 unsigned int t_unsigned_int;
 int32_t t_int32_t;
 int16_t t_int16_t;
 uint16_t t_uint16_t;
 char t_char;
} T_DATA_UNION, *P_DATA_UNION;

#endif  /* __DATA_UNION__ */

void setMegaVar(int parm, T_DATA_UNION val);
void getMegaVar(int parm, P_DATA_UNION val);

typedef struct sMegaVar
{
 uint16_t mparmRpm;             /* 0x00 rpm value */
 char mparmVfdEna;              /* 0x01  */
 char mparmPwmCfg;              /* 0x02  */
 char mparmMaxParm;             /* 0x03 mega maximum parameter */
} T_MEGA_VAR, *P_MEGA_VAR;

extern T_MEGA_VAR mVar;

#endif /* MEGA_STRUCT */
