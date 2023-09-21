/**
 * @copyright (c) 2023 Jose Noel Dominguez Miralrio.
 *
 * @brief	USART Driver
 * @file	usart.c
 * @version 1.0.0
 * @date 20/09/23
 *
 * @author Jose Noel Dominguez Miralrio.
 */

/* Private includes ----------------------------------------------------------*/
#include "../Inc/usart.h"
/*END Includes */

/* Private define ------------------------------------------------------------*/
#define F_CPU 8000000/64
/*END define */

/* Functions ---------------------------------------------------------*/

void usart_init(uint32_t baud_rate){

    float temp;
    TRISC6 = 0;		// Make Tx pin as output
    TRISC7 = 1;     // Make Rx pin as input

    /* Baud rate=9600, SPBRG = (F_CPU /(64*9600))-1 */
    temp = (( (float) (F_CPU) / (float) baud_rate ) - 1);     
    SPBRG = (int) temp;	

    TXSTA = 0x20;  	// Enable Transmit(TX)  
    RCSTA = 0x90;  	// Enable Receive(RX) & Serial 

}

void usart_write_byte(unsigned char byte){


    while( TXIF == 0 );   // Wait for transmit interrupt flag
    TXREG = byte;         // Transmit data via TXREG register

}

char usart_read_byte_pol(void){

    while( RCIF==0 );       // Wait for receive interrupt flag    
    
    if( RCSTAbits.OERR ){

        CREN = 0;
        NOP(); // Wait 1 cycle
        CREN = 1;
    }

    return(RCREG);   // Receive data is stored in RCREG register and return 
}

/* END Functions*/