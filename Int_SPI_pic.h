
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef INT_SPI_PIC_H
#define	INT_SPI_PIC_H

#include "170402_PSU.h"
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

//external function declarations:
void SPI_init(void);
void SPI_enable(void);
void SPI_disable(void);

//void spi_init(void){
//    RC3PPS = 0x0D;               //Assign SPI SCK to pin C3 
//                                 //NOTE: data sheet indicates this should be 0x0F... 
//                                 //MCC indicates 0x0D which works
//    RC2PPS = 0x0E;               //Assign SPI SDO to pin C2
//                                 //NOTE: data sheet indicates this should be 0x10...
//                                 //MCC indicates 0x0E which works
//    SSP1CLKPPSbits.SSP1CLKPPS = 0x13;
//     SSP1CON1 = 0x20;             //Enable MSSP1 peripheral, SPI clock = FOSC/4
//}

/*Macros to be included in Project.h file:
  *****************************************
  ****Peripheral Pin Selections (PPS):
  * Set SCK output (RxyPPS register)
  * Set SDO output (RxyPPS register)
  * Set Clock input (SSP1CLKPPS register)
  * Set Data input (SSP1DATPPS register)
  * Set CS input (slave mode) (SSP1SSPPS register)
  ****GPIO designations:
  * CS -> digital output (master mode) or input (slave mode)
  * SCK -> digital output (master mode) or input (slave mode)
  * SDO -> digital output
  * SDI -> digital input
  ****Serial port configuration (SSPCONx) register:
  * disable SPI (SSPEN bit)
  * set clock polarity (CKP bit)
  * set clock frequency (SSPMx bits)
  ****Serial port status (SSPxSTAT) register:
  * set input data sample timing (SMP bit)
  * set bit transmit timing (CKE bit) 
*/


#endif	/* INT_SPI_PIC_H*/

