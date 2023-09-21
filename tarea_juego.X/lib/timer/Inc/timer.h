/**
 * @copyright (c) 2023 Jose Noel Dominguez Miralrio.
 *
 * @brief	Timer Driver
 * @file	timer.h
 * @version 1.0.0
 * @date 20/09/23
 *
 * @author Jose Noel Dominguez Miralrio
 */

/* Includes ------------------------------------------------------------------*/
#include <xc.h>
#include <stdint.h>
/* END Includes */

/* Function prototypes ----------------------------------------------------------*/

/**
 * @brief Config game timers
 * 
 */
void timer_setup(void);

/**
 * @brief Get the current tick 
 * 
 * @return uint32_t 
 */
uint32_t get_tick(void);

/**
 * @brief Clean tick
 * 
 */
void reset_tick(void);

/**
 * @brief Start system timer
 * 
 */
void timer_start(void);

/**
 * @brief Stop system timer
 * 
 */
void timer_stop(void);

/* END Function prototypes */

extern volatile uint32_t tick;