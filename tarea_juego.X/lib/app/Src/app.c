/**
 * @copyright (c) 2023 Jose Noel Dominguez Miralrio.
 *
 * @brief	Config and run the game.
 * @file	app.c
 * @version 1.0.0
 * @date 20/09/23
 *
 * @author Jose Noel Dominguez Miralrio.
 */

/* Private includes ----------------------------------------------------------*/
#include "../Inc/app.h"
#include "../../hardware/Inc/hardware.h"
#include "../../hardware/Inc/hardware_deff.h"
#include "../../timer/Inc/timer.h"
#include "../../xprintf/src/xprintf.h"
#include "../../usart/Inc/usart.h"
#include "../../display/Inc/display.h"
#include "../../timer/Inc/timer.h"
/*END Includes */

/* Private define ------------------------------------------------------------*/
#define GAME_MODE 1
/*END define */

/* Private variables ---------------------------------------------------------*/
static app_config_t game_config = {
#if !GAME_MODE
    .game_speed = congig_DEFAULT_GAME_SPEED_G1
#else
    .game_speed = config_DEFAULT_GAME_SPEED_G2,
    .game_min_speed = config_SPEED_MIN
#endif
};

static game_vars_t game = {
    .button_pressed = -1,
    .flag_pressed = 0,
    .score = 0,
    .fails = 0,
    .hit = 0,
    .current_speed = 0,
    .game_start = false,
    .max_speed_reached = false

};

static const uint8_t game_led[4] = {0x02, 0x04, 0x08, 0x10};
/*END Private variables */

/* Private function prototypes -----------------------------------------------*/
static void temp_delay(uint32_t delay);
/*END Private function prototypes */

/* Private functions ---------------------------------------------------------*/

/**
 * @brief Clean game variables
 *
 */
static void set_default_variables(void)
{

    game.score = 0;
    game.fails = 0;
    game.hit = 0;
    game.current_speed = 0;
    game.game_start = false;

#if !GAME_MODE
    game_config.game_speed = config_DEFAULT_GAME_SPEED_G1;
#else
    game_config.game_speed = config_DEFAULT_GAME_SPEED_G2;
#endif
}

/**
 * @brief Blink game leds without block main program it uses timer to get time
 *
 * @param blink_time_ms
 */
static void blink_no_block(uint32_t blink_time_ms)
{

    static uint32_t previus_time = 0;
    uint32_t current_time = get_tick();

    if (((current_time - previus_time) >= blink_time_ms))
    {

        LED_1 = !LED_1;
        LED_4 = !LED_4;
        previus_time = current_time;
    }
}

/**
 * @brief Stanby mode function
 *
 */
static void stanby(void)
{

    blink_no_block(500);

    if (BTN_START)
    {

        game.game_start = true;
        LED_1 = 0;
        LED_4 = 0;
        reset_tick();
    }
}

/**
 * @brief Game over function
 *
 */
static void game_over(void)
{

    display_set_score(60); // Set Game Over to displays (GO,6O)
    xputs("Game Over!\n");
    set_default_variables(); // Clean variables and set default game speed

    /* Togle game leds */
    for (uint8_t i = 0; i < 10; i++)
    {

        LED_1 = !LED_1;
        LED_2 = !LED_2;
        LED_3 = !LED_3;
        LED_4 = !LED_4;
        __delay_ms(50);
    }
}

#if !GAME_MODE

/**
 * @brief Game mode 1
 * 
 */
static void game_1(void)
{

    if (game.game_start)
    {

        uint32_t current_time;

        current_time = get_tick();

        read_btn_4();

#if 1
        if (((current_time - previus_time) >= game_config.game_speed))
        {

            // uint16_t s_rand = get_true_random();
            // srand(s_rand);
            uint8_t random_led = rand() % 4;
            xprintf("random val: %d\n", random_led);
            xprintf("Button val: %d\n", game.button_pressed);
            xprintf("Current Speed: %d\n", game_config.game_speed);

            LATA |= game_led[random_led];

            if (random_led == game.button_pressed)
            {

                xputs("Hit!\n");
                game.score++;
                game.hit++;
            }

            else
            {

                game.fails++;
                xputs("Losser\n");
            }

            timer_stop();

            __delay_ms(config_WAIT_TIME_MS);
            LATA = 0x00;
            timer_start();
            game.flag_pressed = 0;

            xprintf("Score: %d\n", game.score);
            xprintf("Fails %d\n", game.fails);
            xprintf("Hits: %d\n", game.hit);

            if (game.fails == config_GAME_OVER_TH)
            {

                display_set_score(60);
                xputs("Game Over!\n");
                game_over();
                set_default_variables();
            }

            if ((game.hit == config_SPEED_GAME_TH) && (game.current_speed < config_SPEED_GAME_LEVELS_TH))
            {

                game_config.game_speed -= config_SPEED_GAME_STEP;
                game.hit = 0;
                game.current_speed++;
                xputs("Speed Increased\n");
            }

            previus_time = current_time;
            game.button_pressed = 10;
            display_set_score(game.score);
        }
#endif
    }

    else
    {

        stanby();
    }
}

#else

#endif

/**
 * @brief Game mode 2 function, this function run the game
 * 
 */
static void game_2(void)
{

    if ( game.game_start ) // if button start was pressed
    {

        uint32_t current_time = get_tick(); // Get current time from system 

#if 1
        if ((current_time >= config_DEFAULT_GAME_SPEED_G2)) // Led appears every 5s
        {

#ifdef USE_TRUE_RANDOME
            uint16_t s_rand = get_true_random();
            srand(s_rand);
#endif
            uint8_t random_led = rand() % 4; // Generate Random val from 0 to 3
            xprintf("random val: %d\n", random_led); // UART Debug
            xprintf("Button val: %d\n", game.button_pressed); // UART Debug
            xprintf("Current Speed: %d\n", game_config.game_speed); // UART Debug

            LATA |= game_led[random_led]; // Turn on led with random value generated 
            game.button_pressed = 10; // Set button default value

            temp_delay(game_config.game_speed); // Led stays on for n time

            if ( random_led == game.button_pressed ) // if random led value generated is equal to button pressed increase
            {                                        // game score and game hits    

                xputs("Hit!\n"); // UART Debug
                game.score++;
                game.hit++;

                if ( game.score >= config_MAX_SCORE ) // Limit max score to 99 because we only have 2 display to display the score
                    game.score = config_MAX_SCORE;
            }

            else // Increase game fails counter
            {

                game.fails++;
                xputs("Losser\n"); // UART Debug
            }

            LATA = 0x00; // Turn off leds

            /* If the user assert 3 times, the game speed increases, speed increases 5 levels */
            if ((game.hit == config_SPEED_GAME_TH) && (game.current_speed < config_SPEED_GAME_LEVELS_TH - 1))
            {

                game_config.game_speed -= config_SPEED_GAME_STEP_G2;
                game.hit = 0;
                game.current_speed++;
                xputs("Speed Increased\n");

                if (game_config.game_speed < game_config.game_min_speed) // Limit max game speed to 500 ms
                    game_config.game_speed = game_config.game_min_speed;
            }

            /* If the user failed 5 times the game is over */
            else if (game.fails == config_GAME_OVER_TH)
            {

                game_over(); // Run game over function
            }

            xprintf("Score: %d\n", game.score); // UART Debug
            xprintf("Fails %d\n", game.fails); // UART Debug
            xprintf("Hits: %d\n", game.hit); // UART Debug
            display_set_score(game.score); // Update user score
            reset_tick(); // Reset game tick

        }
#endif
    }

    else
    {

        stanby();
    }
}

/**
 * @brief Polling button 4 and set 
 * 
 */
static void read_btn_4(void)
{

    if (BTN_4)
    { //! User Button 4

        user_press_button(3);
    }
}

/**
 * @brief Generate a desired delay
 * 
 * @param delay desired delay in ms
 */
static void temp_delay(uint32_t delay)
{

    for (uint32_t i = 0; i < delay; i++)
    {

        read_btn_4();
        __delay_ms(1);
    }
}

/* END Private Functions*/

/* Functions ---------------------------------------------------------*/

void user_press_button(int8_t button)
{

    game.button_pressed = button;
    game.flag_pressed = true;
}

void app_setup(void)
{

    hw_setup();
    usart_init(9600);
    timer_setup();
    xdev_in(usart_read_byte_pol); // set putchar
    xdev_out(usart_write_byte);
}

void app_loop(void)
{

    while (1)
    {

#if !GAME_MODE

        game_1();
#else
        game_2();

#endif
    }
}

/* END Functions*/