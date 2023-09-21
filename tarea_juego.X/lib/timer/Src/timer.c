/**
 * @copyright (c) 2023 Jose Noel Dominguez Miralrio.
 *
 * @brief	Timer Driver
 * @file	timer.c
 * @version 1.0.0
 * @date 20/09/23
 *
 * @author Jose Noel Dominguez Miralrio
 */

/* Private includes ----------------------------------------------------------*/
#include "../Inc/timer.h"
/*END Includes */

/* Variables ---------------------------------------------------------*/
volatile uint32_t tick;
/* END Variables */


/* Functions ---------------------------------------------------------*/

void timer_setup(void){

    GIE = 1; /* Enable Global Interrupt */
    PEIE = 1; /* Enable Peripheral Interrupt */


    // Display Timer
    TMR0IE = 1;     /* Enable Timer 0 Overflow Interrupt */
    TMR0IF = 0;     /* Clean Timer 0 Flag */
    T0CON = 0x80;   /* Config Timer 0 control register */
    TMR0 = 0xF856;	/* Load Count for generating delay of 1ms */
    TMR0ON = 1;		/* Turn ON Timer1 */

    // System Timer 
    TMR1IE = 1; /* Enable Timer1 Overflow Interrupt */
    TMR1IF = 0; /* Clean Flag */
    T1CON = 0x80;   /* Config Timer 1 control register */		
    TMR1 = 0xF856;	/* Load Count for generating delay of 1ms */
    TMR1ON = 1;		/* Turn ON Timer1 */
    tick = 0;       /* Reset tick */

    

}

uint32_t get_tick(void){

    return tick;
}


void reset_tick(void){
    
    tick = 0;
}

void timer_start(void){
    
    TMR1ON = 1;
    
}
void timer_stop(void){
    
    TMR1ON = 0;
    
}

/* END Functions*/