/*
 * File:   Int_PWM_pic.c
 * Author: rbs
 *
 * Created on April 26, 2017, 9:29 PM
 */


#include <xc.h>
#include "170402_PSU.h"
#include "Int_PWM_pic.h"

//internal function declarations:
void Set_DC(float value, int type);

//internal functions
void Set_DC(float value, int type){
  
}

void PWM_init(void){
  __SET_TIMER_PWM3;
  __SET_TIMER_PWM4;
  __SET_PWM3_PPS;
  __SET_PWM4_PPS;
}

void PWM_enable(V_or_I_PWM V_or_I_PWM){
  
}

void PWM_disable(V_or_I_PWM V_or_I_PWM){
  
}