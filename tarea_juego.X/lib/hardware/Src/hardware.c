/**
 * @copyright (c) 2023 Jose Noel Dominguez Miralrio.
 *
 * @brief	Config hardware pheripherals like timer, interrupts, gpios, clock, etc. 
 * @file	hardware.h
 * @version 1.0.0
 * @date 20/09/23
 *
 * @author Jose Noel Dominguez Miralrio
 */

/* Private includes ----------------------------------------------------------*/
#include <stdbool.h>
#include "../Inc/hardware.h"
#include "../Inc/hardware_deff.h"
#include "../../timer/Inc/timer.h"
/*END Includes */


extern volatile uint32_t tick;

/* Private function prototypes -----------------------------------------------*/
static void external_interrupt_setup(void);
static void gpios_setup(void);
/*END Private function prototypes */

/* Extern function prototypes -----------------------------------------------*/
extern void user_press_button(int8_t button);
extern void display_set_score(uint8_t score);
extern void update_display(void);
/* END function prototypes */


/* Private functions ---------------------------------------------------------*/

/**
 * @brief Interrupt function handler. This function handle interrups from timers and buttons
 * 
 */
void __interrupt() isr(void){
    

    
    /* Timer Display Interrupt */
    if ( INTCONbits.TMR0IF ){
       
        INTCONbits.TMR0IF = 0; // Clean timer 0 interrupt flag
        TMR0 = 0xF856;         // Reload Timer 0 */
        update_display();      // Refres display

    }

    /* Timer Game Interrupt */
    if ( PIR1bits.TMR1IF ){
        
        PIR1bits.TMR1IF = 0;  // Clean timer 1 interrupt flag
        TMR1 = 0xF856; // Reload Timer 1 
        tick++;  // Increase tick 

    }
    

    /* Coint Interrupt */
    if ( INTCONbits.INT0IF ){

        INTCONbits.INT0IF = 0; // Clean Interrupt 0 flag
        user_press_button(0);
        
    }
    
    else if ( INTCON3bits.INT1F  ){
        
        user_press_button(1); // Clean Interrupt 1 flag
        INTCON3bits.INT1F = 0;
    }
    
    else if ( INTCON3bits.INT2F ){

        user_press_button(2);
        INTCON3bits.INT2F = 0; // Clean Interrupt 2 flag
    }

}

/**
 * @brief Configure and init ADC to generate random vals
 * 
 */
static void true_random_init(void){
    
    ADCON1bits.PCFG = 0b1110; //  Config ADC port
    ADCON1bits.VCFG = 0b00;   //  ADC reference voltage(5v-0v).
    ADCON0bits.CHS = 0b0000;  //  ADC channel selection.
    ADCON2bits.ACQT = 0b010;  //  Adquisition time 4Tad.
    ADCON2bits.ADCS = 0b001;  //  Conversion time Fosc/8.
    ADCON2bits.ADFM = 0;      //  Left justification(8bits-mode).
    ADCON0bits.ADON = 1;      //  Enable ADC module.   
}

/**
 * @brief Configure GPIOs and interrupts
 * 
 */
static void gpios_setup(void){

/* Setup GPIOS */
  TRISA = 0x01;
  TRISB = 0x1F;
  TRISD = 0x00;
  TRISE = 0x00;
  TRISCbits.RC6 = 0; // USART TX config
  TRISCbits.RC7 = 1; // USART RX config
/* Clean Ports */
  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;
  PORTE = 0x00;
/* Interrupt Setup */
  external_interrupt_setup();

/* True random setup */
  true_random_init();
  
}

/**
 * @brief Configure External interrupts as rising edge Button 1 to Button 3
 * 
 */
static void external_interrupt_setup(void){

  INTCON2 = 0xF0;		    // Interrupts config 
  
  INTCONbits.INT0IE = 1;	// Enable INT0 external interrupt
  INTCONbits.INT0IF = 0;	// Clear INT0IF flag*/
  
  INTCON3bits.INT1E = 1;    // Enable INT1 external interrupt
  INTCON3bits.INT1F = 0;    // Clear INT1IF flag*/
  
  INTCON3bits.INT2E = 1;    // Enable INT2 external interrupt
  INTCON3bits.INT2F = 0;    // Clear INT2IF flag*/
 
  INTCONbits.GIE = 1;		// Enable Global Interrupt
  
  
}


uint16_t get_true_random(void){
    
    uint16_t adc;
    ADCON0bits.GO_DONE = 1; // Start convertion
    while (ADCON0bits.GO_DONE); //  Wait ADC convertion 
    adc = ADRESH; //  get ADC high val
    adc = (adc << 8) + ADRESL; // get adc high + adc low vals
   
    return adc; // return adc 

}

void hw_setup(void){
    
    OSCCON = 0x72;  // HSI Config
    CCP1CON = 0x00; // Capure/Compare/PWM Disabled
    ADCON1 |= 0x0F; // Config pines to digital mode
    CMCON = 0x07; // Disable comparator from port A 
    UCON = 0x00; // USB Disabled
    ADCON0 = 0x00; // ADC Config clean
    gpios_setup();

}

