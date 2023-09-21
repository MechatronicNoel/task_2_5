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

#ifndef HARDWARE_H_
#define HARDWARE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* END Includes */

/* Defines --------------------------------------------------------------------*/
#define _XTAL_FREQ 8000000
/* END Defines */

/* Function prototypes ----------------------------------------------------------*/

/**
 * @brief Configure microcontroller hardware
 * 
 */
void hw_setup(void);
/**
 * @brief Generate a random value using ADC
 * 
 * @return random val 
 */
uint16_t get_true_random(void);

/* END Function prototypes */

#endif /* HARDWARE_H_ */
