/**
 * @copyright (c) 2023 Jose Noel Dominguez Miralrio.
 *
 * @brief	Config and run game. 
 * @file	app.h
 * @version 1.0.0
 * @date 20/09/23
 *
 * @author Jose Noel Dominguez Miralrio
 */


#ifndef APP_H_
#define APP_H_
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
/* END Includes */

/* Defines --------------------------------------------------------------------*/

#define config_GAME_OVER_TH             5   
#define config_SPEED_GAME_TH            3   
#define config_SPEED_GAME_LEVELS_TH     5   
#define config_DEFAULT_GAME_SPEED_G1    6000 
#define config_SPEED_GAME_STEP          1000 
#define config_WAIT_TIME_MS             3000
#define config_SPEED_MIN                500
#define config_DEFAULT_GAME_SPEED_G2    2500
#define config_WAIT_TIME_MS_G2          4000
#define config_SPEED_GAME_STEP_G2       500
#define config_MAX_SCORE                99

/* END Defines */

/* Typedef ---------------------------------------------------------------------*/
typedef struct
{

    uint32_t game_speed;
    uint32_t game_min_speed;

} app_config_t;

typedef struct
{
    volatile int8_t button_pressed;
    volatile bool flag_pressed;
    uint8_t score;
    uint8_t fails;
    uint8_t hit;
    uint8_t current_speed;
    bool game_start;
    bool max_speed_reached;

} game_vars_t;
/* END Typedef */

/* Function prototypes ----------------------------------------------------------*/

/**
 * @brief Configure the peripherals necessary to run the game.
 *
 */
void app_setup(void);

/**
 * @brief Run game forever
 *
 */
void app_loop(void);

/**
 * @brief Detect button pressed
 * 
 * @param button Button value
 */
void user_press_button(int8_t button);
/* END Function prototypes */

#endif /* APP_H_ */
