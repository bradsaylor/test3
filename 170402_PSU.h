/* 
 * File:   170402_PSU.h
 * Author: rbs
 * Target: PIC18F25k40
 * Created on April 22, 2017, 11:17 PM
 */

#ifndef _170402_PSU_H
#define	_170402_PSU_H

#include <xc.h> 
#include <stdint.h>

#define _XTAL_FREQ 1000000

/*Pin Allocation Map:
 * RA0-                   RC4-
 * RA1-                   RC5-
 * RA2- PWM3              RC6-
 * RA3- PWM4              RC7-
 * RA4-                   RB0-
 * RA5-                   RB1-
 * RA6-                   RB2-
 * RA7-                   RB3-
 * RC0-                   RB4-
 * RC1- SPI_CS            RB5-
 * RC2- SPI_SDO           RB6-
 * RC3- SPI_SCK           RB7-
 */

//********SPI CONFIGURATION***********
//************************************
// SPI IO, SCK SDO CS = digital outputs SDI not used
#define __SPI_IO_INITIALIZE  TRISC3 = TRISC2 = TRISC1 = 0

//SPI PPS setup: RC3=CLK OUT, RC2=SDO OUT, RC3=MSSP CLK IN (pg332 of datasheet)
#define __SPI_PPS_INITIALIZE RC3PPS = 0x0D;\
                             RC2PPS = 0x0E;\
                             SSP1CLKPPS = 0x13  
                             
//Alias for Chip Select Pin
#define __CS RC3

//SSPCON1 register configuration
#define __SPI_SET_CLOCK_POLARITY SSP1CON1bits.CKP = 0
#define __SPI_SET_CLOCK_FREQUENCY SSP1CON1 |= 0x00
//SSP1STAT register configuration
#define __SPI_SET_TX_POLARITY SSP1STATbits.CKE = 0
 

//********PWM CONFIGURATION***********
//************************************

//PWM timer configuration
#define __SET_TIMER_PWM3 CCPTMRSbits.P3TSEL = 0x01    //PWM3 -> TMR2
#define __SET_TIMER_PWM4 CCPTMRSbits.P4TSEL = 0x01    //PWM4 -> TMR2

//PWM PPS configuration
#define __SET_PWM3_PPS RA2PPS = 0x07                  //Pin A2 -> PWM3
#define __SET_PWM4_PPS RA3PPS = 0x08                  //Pin A3 -> PWM4


#endif	/* _170402_PSU_H */

