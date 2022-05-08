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
//#define DEBUG_ACC
//#define DEBUG_TRASLATION

#define C1 	//se definita si ha che premendo key1 si passa dal ruotare 
			//l'oggetto al traslarlo mediante accelerometro e viceversa
			//se non definito ho entrambe le trasformazioni in contemporanea
//C standard library

#include <unistd.h>
#include <stdint.h>

#include <stdio.h>
#ifdef DEBUG_1
#include <stdio.h>
#endif

#include <math.h>

//NIOS driver library
#include "system.h"
#include "drivers/inc/altera_up_avalon_video_pixel_buffer_dma.h"
#include "HAL/inc/sys/alt_timestamp.h"
#include "HAL/inc/io.h"

//header per gestione PIO
#include "./drivers/inc/altera_avalon_pio_regs.h"
//header per gestione accelerometro
#include "./drivers/inc/altera_up_avalon_accelerometer_spi.h"

//aggiunte per la funziona di samu del clipping
	#include <errno.h>
	#include "HAL/inc/priv/alt_file.h"
////////


//user header file
#include "../inc/functions.h"
#include "../inc/graphic_object.h"

#define X_RES       320
#define Y_RES       260


//MACRO per controllo comandi asseganti all'accelerometro
#define INC_S  		(float)	0.005 		//incremento scala
#define MAX_INC_T  	(float)	0.02		//massimo incremento che può avere la traslazione
#define MAX_INC_R  	(float)	(M_PI/100) 	//massimo incremento che può avere la rotazione
#define G_ACC				254 		//corrisponde a 1g ( 254 * sensitivity = 9.8 ) quindi nell'ipotesi che
										// la scheda venga usata da ferma è l'accelerazione massima che si può avere lungo un asse

//palette colori a 16 bit
#define RED         0xF800
#define GREEN       0x07E0
#define BLUE        0x001F
#define BLACK       0x0000
#define WHITE       0xFFFF
#define YELLOW      0xFFE0
#define MAGENTA     0xF81F
#define CYAN        0x07FF


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
#define BIT(x)	(1<<x)

#endif /* CONFIG_H_ */
