/**
 * @copyright (c) 2023 Jose Noel Dominguez Miralrio.
 *
 * @brief	Display driver.
 * @file	display.h
 * @version 1.0.0
 * @date 20/09/23
 *
 * @author Jose Noel Dominguez Miralrio.
 */

/* Private includes ----------------------------------------------------------*/
#include "../Inc/display.h"
#include "../../hardware/Inc/hardware_deff.h"
#include "../../xprintf/src/xprintf.h"
#include <stdbool.h>
/*END Includes */

/* Private define ------------------------------------------------------------*/
#define NUMBER_OF_DISPLAYS      2
#define MAX_NUMER_TO_CONVERT    2
/*END define */


/* Private variables ---------------------------------------------------------*/
static uint8_t display_numbers[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67}; /* Numbers 0-9 */
/* END Private variables */

/* Variables ---------------------------------------------------------*/
uint16_t temp_score = 0;
uint8_t bcd_data[2];
/*END Variables */

/* Functions ---------------------------------------------------------*/

void update_display(void){
    
    static uint8_t display = 0;
   
    
    display_set_number(bcd_data[display],display);    
    display++;
    
    
    if ( display == NUMBER_OF_DISPLAYS ){
        display = 0;
    }
        
    
}

void display_set_number(uint16_t number, display_t display){

    LATD = 0x00;
    switch( display ){

        case DISPLAY_P1:
            DIS_1_ENABLE = 1;
            DIS_2_ENABLE = 0;
        break;

        case DISPLAY_P2:
            DIS_1_ENABLE = 0;
            DIS_2_ENABLE = 1;
        break;

        case ENABLE_ALL:
            DIS_1_ENABLE = 1;
            DIS_2_ENABLE = 1;
        break;
    }
    
    LATD = display_numbers[number];

}

void display_set_score(uint8_t score){
    
    for( uint8_t i = 0;  i < MAX_NUMER_TO_CONVERT; i++){   // llena el arreglo con los valores uni,dec,cen,mil,diezm
                             // despues de cada operacion se incrementa el indice
            bcd_data[i]=score%10;// mediante la operacion modulo se obtiene el, i digito decimal
            score=score/10;             // n dividido 10 para cada i y tomamos su valor entero:
    }  
    
}

/* END Functions*/

