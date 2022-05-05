/*
 * config.h
 *
 *  Created on: 17 apr 2022
 *      Author: vanno
 */
#ifndef CONFIG_H_
#define CONFIG_H_

//#define DEBUG_1
//#define DEBUG_VECTORS

//C standard library

#include <unistd.h>
#include <stdint.h>

#ifdef DEBUG_1
#include <stdio.h>
#endif

#include <math.h>

//NIOS driver library
#include "system.h"
#include "drivers/inc/altera_up_avalon_video_pixel_buffer_dma.h"
#include "HAL/inc/sys/alt_timestamp.h"
#include "HAL/inc/io.h"

//aggiunte per la funziona di samu del clipping
	#include <errno.h>
	#include "HAL/inc/priv/alt_file.h"
////////

//user header file
#include "../inc/functions.h"
#include "../inc/graphic_object.h"

#define X_RES       320
#define Y_RES       240


//palette colori a 16 bit
#define RED         0xF800
#define GREEN       0x07E0
#define BLUE        0x001F
#define BLACK       0x0000
#define WHITE       0xFFFF
#define YELLOW      0xFFE0
#define MAGENTA     0xF81F
#define CYAN        0x07FF

//MACRO per maschere controllo slider
#define SLIDER0     0b0000000001;
#define SLIDER1     0b0000000010;
#define SLIDER2     0b0000000100;
#define SLIDER3     0b0000001000;
#define SLIDER4     0b0000010000;
#define SLIDER5     0b0000100000;
#define SLIDER6     0b0001000000;
#define SLIDER7     0b0010000000;
#define SLIDER8     0b0100000000;
#define SLIDER9     0b1000000000;

/*  controlla se mandare a terminale le coordinate x,y,z,w dei singoli vettori,
 *  oltre che le coordinate x,y dello schermo finali
 */
//#define DEBUG_VECTORS

#define X 0
#define Y 1
#define Z 2
#define W 3

// user macros
#define M4(x,y) (x*4+y)     //indirizza l'lemento (x,y) di una matrice a 4 colonne, (rappresentato sotto forma di array lineare)
#define M8(x,y) (x*8+y)     //indirizza l'lemento (x,y) di una matrice a 8 colonne,(rappresentato sotto forma di array lineare)

#endif /* CONFIG_H_ */
