/**
 * @copyright (c) 2023 Jose Noel Dominguez Miralrio.
 *
 * @brief	Hardware Definitions.
 * @file	hardware_deff.h
 * @version 1.0.0
 * @date 20/09/23
 *
 * @author Jose Noel Dominguez Miralrio.
 */

#ifndef HARDWARE_DEFF_H_
#define HARDWARE_DEFF_H_
#include <xc.h>
/* Defines --------------------------------------------------------------------*/
#define BTN_1           PORTBbits.RB0   
#define BTN_2           PORTBbits.RB1
#define BTN_3           PORTBbits.RB2
#define BTN_4           PORTBbits.RB3
#define BTN_START       PORTBbits.RB4    
#define DIS_A           LATDbits.LATD0     
#define DIS_B           LATDbits.LATD1
#define DIS_C           LATDbits.LATD2
#define DIS_D           LATDbits.LATD3
#define DIS_E           LATDbits.LATD4
#define DIS_F           LATDbits.LATD5
#define DIS_G           LATDbits.LATD6
#define DIS_DP          LATDbits.LATD7
#define DIS_1_ENABLE    LATEbits.LATE1
#define DIS_2_ENABLE    LATEbits.LATE0
#define LED_1           LATAbits.LATA1           
#define LED_2           LATAbits.LATA2
#define LED_3           LATAbits.LATA3
#define LED_4           LATAbits.LATA4
/* END Defines */
#endif /* HARDWARE_DEFF_H_ */
