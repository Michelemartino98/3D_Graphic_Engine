/*
 * config.h
 *
 *  Created on: 17 apr 2022
 *      Author: vanno
 */
#ifndef CONFIG_H_
#define CONFIG_H_
//C standard library
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

//NIOS driver library
#include "system.h"
#include "drivers/inc/altera_up_avalon_video_pixel_buffer_dma.h"
#include "sys/alt_timestamp.h"
#include <io.h>

//user header file
#include "../inc/functions.h"
#include "../inc/graphic_object.h"

#define RED         0xF800
#define GREEN       0x07E0
#define BLUE        0x001F
#define BLACK       0x0000
#define WHITE       0xFFFF
#define YELLOW      0xFFE0
#define MAGENTA     0xF81F
#define CYAN        0x07FF

#endif /* CONFIG_H_ */
