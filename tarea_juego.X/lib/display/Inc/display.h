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


#ifndef DISPLAY_H_
#define DISPLAY_H_

/* Includes --------------------------------------------------------------------*/
#include <stdint.h>
/* END Includes */

/* Defines ---------------------------------------------------------------------*/
#define _XTAL_FREQ 8000000
/* END Defines */

/* Typedef ---------------------------------------------------------------------*/
typedef enum {
    DISPLAY_P1,
    DISPLAY_P2,
    ENABLE_ALL
}display_t;
/* END Typedef */

/* Function prototypes ----------------------------------------------------------*/
void display_set_number(uint16_t number, display_t display);
void display_set_score(uint8_t score);
/* END Function prototypes */


#endif /* DISPLAY_H_ */
