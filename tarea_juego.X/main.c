/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jose Noel Dominguez Miralrio.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  * 
  * Task description:
  * Una vez elaborado el producto de aprendizaje teórico es importante generar una práctica
  * en  la que se utilicen los conocimientos adquiridos. Para ello, en esta actividad deberás
  * desarrollar un programa en un PIC 18F4550 que tenga cuatro botones de entrada y cuatro LED de salida.
  * El juego consiste en encender uno de los cuatro LED de forma aleatoria. El jugador tendrá que presionar
  * el botón correspondiente al LED encendido. Si el usuario acierta en un tiempo determinado, su puntuación
  * se incrementa en uno (el valor inicial de la puntuación deberá ser cero) y se muestra en un par de display
  * de 7 segmentos, uno para las unidades y otro para las decenas. Después de cinco fallas, el juego termina.
  * Cada tres aciertos, el tiempo que tiene el jugador para presionar el botón deberá disminuir, con un mínimo de 5 niveles.
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <xc.h>
#include "lib/app/Inc/app.h"
#include "config.h"


/**
 * @brief main app
 * 
 */
void main(void) {
    
    app_setup();
    app_loop();
    return;
}
