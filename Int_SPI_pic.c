/*
 * File:   Int_SPI_pic.c
 * Author: rbs
 *
 * Created on April 22, 2017, 9:57 PM
 */


#include <xc.h>
#include "Int_SPI_pic.h"
#include "170402_PSU.h"

//internal function declarations:
void Send_data(uint8_t data);

//internal functions

void Send_data(uint8_t data){
  
  return;
}

//external functions

void SPI_init(void){ 
  __SPI_IO_INITIALIZE;
  __SPI_PPS_INITIALIZE;
  __SPI_SET_CLOCK_POLARITY;
  __SPI_SET_CLOCK_FREQUENCY;
  __SPI_SET_TX_POLARITY; 
  return;
}
  
void SPI_enable(void){
  SSP1CON1bits.SSPEN = 0x1;
  return;
}

void SPI_disable(void){
  SSP1CON1bits.SSPEN = 0x0;
  return;
}
