/* 
 * File:   Int_IVset_PWM.h
 * Author: rbs
 *
 * Created on April 27, 2017, 8:03 PM
 */

#ifndef INT_IVSET_PWM_H
#define	INT_IVSET_PWM_H

//external function declarations:
void I_set(float value);
void V_set(float value);

//external structure declarations:
typedef struct{
  
}I_set_config;

I_set_config I_set_configuration;

typedef struct{
  
}V_set_config;

V_set_config V_set_configuration;

//external enumerated type declarations
typedef enum{
  Voltage,
  Current
}V_or_I_set;

V_or_I_set Voltage_or_current_set;


#endif	/* INT_IVSET_PWM_H */

