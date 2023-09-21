/**
 * @copyright (c) 2023 Jose Noel Dominguez Miralrio.
 *
 * @brief	USART Driver
 * @file	usart.h
 * @version 1.0.0
 * @date 20/09/23
 *
 * @author Jose Noel Dominguez Miralrio.
 */

/* Includes ------------------------------------------------------------------*/
#include <xc.h>
#include <stdlib.h>
/* END Includes */

/* Function prototypes ----------------------------------------------------------*/

/**
 * @brief Config USART speed
 * 
 * @param baud_rate desired speed it can be 9600/115200...
 */
void usart_init(uint32_t baud_rate);

/**
 * @brief Write byte by usart
 * 
 * @param byte byte val
 */
void usart_write_byte(unsigned char byte);

/**
 * @brief Read byte from usar
 * 
 * @return char byte read
 */
char usart_read_byte_pol(void);

/* END Function prototypes */