/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'vga_lt24_accelerometer_computer'
 * SOPC Builder design path: C:/Users/vanno/OneDrive/Documents/GitKraken/3D_Graphic_Engine/test_accelerometro_vga_lt24/sopc/vga_lt24_accelerometer_computer.sopcinfo
 *
 * Generated: Fri May 20 22:03:14 CEST 2022
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x05000820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 80000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1b
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x05040020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 80000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x1b
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x05040000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x05000820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 80000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1b
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x05040020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x1b
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x05040000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SPI
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_UP_AVALON_ACCELEROMETER_SPI
#define __ALTERA_UP_AVALON_VIDEO_PIXEL_BUFFER_DMA
#define __ALTERA_UP_AVALON_VIDEO_RGB_RESAMPLER
#define __ALTPLL
#define __LT24_CONTROLLER


/*
 * HEX3_HEX0 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX3_HEX0 altera_avalon_pio
#define HEX3_HEX0_BASE 0x5001060
#define HEX3_HEX0_BIT_CLEARING_EDGE_REGISTER 0
#define HEX3_HEX0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX3_HEX0_CAPTURE 0
#define HEX3_HEX0_DATA_WIDTH 32
#define HEX3_HEX0_DO_TEST_BENCH_WIRING 0
#define HEX3_HEX0_DRIVEN_SIM_VALUE 0
#define HEX3_HEX0_EDGE_TYPE "NONE"
#define HEX3_HEX0_FREQ 80000000
#define HEX3_HEX0_HAS_IN 0
#define HEX3_HEX0_HAS_OUT 1
#define HEX3_HEX0_HAS_TRI 0
#define HEX3_HEX0_IRQ -1
#define HEX3_HEX0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX3_HEX0_IRQ_TYPE "NONE"
#define HEX3_HEX0_NAME "/dev/HEX3_HEX0"
#define HEX3_HEX0_RESET_VALUE 0
#define HEX3_HEX0_SPAN 16
#define HEX3_HEX0_TYPE "altera_avalon_pio"


/*
 * HEX5_HEX4 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX5_HEX4 altera_avalon_pio
#define HEX5_HEX4_BASE 0x5001050
#define HEX5_HEX4_BIT_CLEARING_EDGE_REGISTER 0
#define HEX5_HEX4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX5_HEX4_CAPTURE 0
#define HEX5_HEX4_DATA_WIDTH 16
#define HEX5_HEX4_DO_TEST_BENCH_WIRING 0
#define HEX5_HEX4_DRIVEN_SIM_VALUE 0
#define HEX5_HEX4_EDGE_TYPE "NONE"
#define HEX5_HEX4_FREQ 80000000
#define HEX5_HEX4_HAS_IN 0
#define HEX5_HEX4_HAS_OUT 1
#define HEX5_HEX4_HAS_TRI 0
#define HEX5_HEX4_IRQ -1
#define HEX5_HEX4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX5_HEX4_IRQ_TYPE "NONE"
#define HEX5_HEX4_NAME "/dev/HEX5_HEX4"
#define HEX5_HEX4_RESET_VALUE 0
#define HEX5_HEX4_SPAN 16
#define HEX5_HEX4_TYPE "altera_avalon_pio"


/*
 * KEY configuration
 *
 */

#define ALT_MODULE_CLASS_KEY altera_avalon_pio
#define KEY_BASE 0x5001080
#define KEY_BIT_CLEARING_EDGE_REGISTER 0
#define KEY_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEY_CAPTURE 1
#define KEY_DATA_WIDTH 2
#define KEY_DO_TEST_BENCH_WIRING 0
#define KEY_DRIVEN_SIM_VALUE 0
#define KEY_EDGE_TYPE "RISING"
#define KEY_FREQ 80000000
#define KEY_HAS_IN 1
#define KEY_HAS_OUT 0
#define KEY_HAS_TRI 0
#define KEY_IRQ -1
#define KEY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define KEY_IRQ_TYPE "NONE"
#define KEY_NAME "/dev/KEY"
#define KEY_RESET_VALUE 0
#define KEY_SPAN 16
#define KEY_TYPE "altera_avalon_pio"


/*
 * LCD_RESET_N configuration
 *
 */

#define ALT_MODULE_CLASS_LCD_RESET_N altera_avalon_pio
#define LCD_RESET_N_BASE 0x4000040
#define LCD_RESET_N_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_RESET_N_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_RESET_N_CAPTURE 0
#define LCD_RESET_N_DATA_WIDTH 1
#define LCD_RESET_N_DO_TEST_BENCH_WIRING 0
#define LCD_RESET_N_DRIVEN_SIM_VALUE 0
#define LCD_RESET_N_EDGE_TYPE "NONE"
#define LCD_RESET_N_FREQ 10000000
#define LCD_RESET_N_HAS_IN 0
#define LCD_RESET_N_HAS_OUT 1
#define LCD_RESET_N_HAS_TRI 0
#define LCD_RESET_N_IRQ -1
#define LCD_RESET_N_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_RESET_N_IRQ_TYPE "NONE"
#define LCD_RESET_N_NAME "/dev/LCD_RESET_N"
#define LCD_RESET_N_RESET_VALUE 0
#define LCD_RESET_N_SPAN 16
#define LCD_RESET_N_TYPE "altera_avalon_pio"


/*
 * LEDS configuration
 *
 */

#define ALT_MODULE_CLASS_LEDS altera_avalon_pio
#define LEDS_BASE 0x5001040
#define LEDS_BIT_CLEARING_EDGE_REGISTER 0
#define LEDS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDS_CAPTURE 0
#define LEDS_DATA_WIDTH 10
#define LEDS_DO_TEST_BENCH_WIRING 0
#define LEDS_DRIVEN_SIM_VALUE 0
#define LEDS_EDGE_TYPE "NONE"
#define LEDS_FREQ 80000000
#define LEDS_HAS_IN 0
#define LEDS_HAS_OUT 1
#define LEDS_HAS_TRI 0
#define LEDS_IRQ -1
#define LEDS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDS_IRQ_TYPE "NONE"
#define LEDS_NAME "/dev/LEDS"
#define LEDS_RESET_VALUE 0
#define LEDS_SPAN 16
#define LEDS_TYPE "altera_avalon_pio"


/*
 * LT24_Controller configuration
 *
 */

#define ALT_MODULE_CLASS_LT24_Controller LT24_Controller
#define LT24_CONTROLLER_BASE 0x4000050
#define LT24_CONTROLLER_IRQ -1
#define LT24_CONTROLLER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LT24_CONTROLLER_NAME "/dev/LT24_Controller"
#define LT24_CONTROLLER_SPAN 8
#define LT24_CONTROLLER_TYPE "LT24_Controller"


/*
 * SLIDERS configuration
 *
 */

#define ALT_MODULE_CLASS_SLIDERS altera_avalon_pio
#define SLIDERS_BASE 0x5001070
#define SLIDERS_BIT_CLEARING_EDGE_REGISTER 0
#define SLIDERS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SLIDERS_CAPTURE 0
#define SLIDERS_DATA_WIDTH 10
#define SLIDERS_DO_TEST_BENCH_WIRING 0
#define SLIDERS_DRIVEN_SIM_VALUE 0
#define SLIDERS_EDGE_TYPE "NONE"
#define SLIDERS_FREQ 80000000
#define SLIDERS_HAS_IN 1
#define SLIDERS_HAS_OUT 0
#define SLIDERS_HAS_TRI 0
#define SLIDERS_IRQ -1
#define SLIDERS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SLIDERS_IRQ_TYPE "NONE"
#define SLIDERS_NAME "/dev/SLIDERS"
#define SLIDERS_RESET_VALUE 0
#define SLIDERS_SPAN 16
#define SLIDERS_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "MAX 10"
#define ALT_IRQ_BASE NULL
#define ALT_LEGACY_INTERRUPT_API_PRESENT
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x50010b8
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x50010b8
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x50010b8
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "vga_lt24_accelerometer_computer"


/*
 * accelerometer_spi configuration
 *
 */

#define ACCELEROMETER_SPI_BASE 0x50010c4
#define ACCELEROMETER_SPI_IRQ 6
#define ACCELEROMETER_SPI_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ACCELEROMETER_SPI_NAME "/dev/accelerometer_spi"
#define ACCELEROMETER_SPI_SPAN 2
#define ACCELEROMETER_SPI_TYPE "altera_up_avalon_accelerometer_spi"
#define ALT_MODULE_CLASS_accelerometer_spi altera_up_avalon_accelerometer_spi


/*
 * altpll_0 configuration
 *
 */

#define ALTPLL_0_BASE 0x5001090
#define ALTPLL_0_IRQ -1
#define ALTPLL_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALTPLL_0_NAME "/dev/altpll_0"
#define ALTPLL_0_SPAN 16
#define ALTPLL_0_TYPE "altpll"
#define ALT_MODULE_CLASS_altpll_0 altpll


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_0
#define ALT_TIMESTAMP_CLK TIMER_1


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x50010b8
#define JTAG_UART_0_IRQ 16
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * new_sdram_controller_0 configuration
 *
 */

#define ALT_MODULE_CLASS_new_sdram_controller_0 altera_avalon_new_sdram_controller
#define NEW_SDRAM_CONTROLLER_0_BASE 0x0
#define NEW_SDRAM_CONTROLLER_0_CAS_LATENCY 3
#define NEW_SDRAM_CONTROLLER_0_CONTENTS_INFO
#define NEW_SDRAM_CONTROLLER_0_INIT_NOP_DELAY 0.0
#define NEW_SDRAM_CONTROLLER_0_INIT_REFRESH_COMMANDS 2
#define NEW_SDRAM_CONTROLLER_0_IRQ -1
#define NEW_SDRAM_CONTROLLER_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define NEW_SDRAM_CONTROLLER_0_IS_INITIALIZED 1
#define NEW_SDRAM_CONTROLLER_0_NAME "/dev/new_sdram_controller_0"
#define NEW_SDRAM_CONTROLLER_0_POWERUP_DELAY 100.0
#define NEW_SDRAM_CONTROLLER_0_REFRESH_PERIOD 7.8125
#define NEW_SDRAM_CONTROLLER_0_REGISTER_DATA_IN 1
#define NEW_SDRAM_CONTROLLER_0_SDRAM_ADDR_WIDTH 0x19
#define NEW_SDRAM_CONTROLLER_0_SDRAM_BANK_WIDTH 2
#define NEW_SDRAM_CONTROLLER_0_SDRAM_COL_WIDTH 10
#define NEW_SDRAM_CONTROLLER_0_SDRAM_DATA_WIDTH 16
#define NEW_SDRAM_CONTROLLER_0_SDRAM_NUM_BANKS 4
#define NEW_SDRAM_CONTROLLER_0_SDRAM_NUM_CHIPSELECTS 1
#define NEW_SDRAM_CONTROLLER_0_SDRAM_ROW_WIDTH 13
#define NEW_SDRAM_CONTROLLER_0_SHARED_DATA 0
#define NEW_SDRAM_CONTROLLER_0_SIM_MODEL_BASE 0
#define NEW_SDRAM_CONTROLLER_0_SPAN 67108864
#define NEW_SDRAM_CONTROLLER_0_STARVATION_INDICATOR 0
#define NEW_SDRAM_CONTROLLER_0_TRISTATE_BRIDGE_SLAVE ""
#define NEW_SDRAM_CONTROLLER_0_TYPE "altera_avalon_new_sdram_controller"
#define NEW_SDRAM_CONTROLLER_0_T_AC 5.5
#define NEW_SDRAM_CONTROLLER_0_T_MRD 3
#define NEW_SDRAM_CONTROLLER_0_T_RCD 20.0
#define NEW_SDRAM_CONTROLLER_0_T_RFC 70.0
#define NEW_SDRAM_CONTROLLER_0_T_RP 20.0
#define NEW_SDRAM_CONTROLLER_0_T_WR 14.0


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x5040000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "vga_lt24_accelerometer_computer_onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 0
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 160000
#define ONCHIP_MEMORY2_0_SPAN 160000
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * sysid_qsys_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sysid_qsys_0 altera_avalon_sysid_qsys
#define SYSID_QSYS_0_BASE 0x50010b0
#define SYSID_QSYS_0_ID 20
#define SYSID_QSYS_0_IRQ -1
#define SYSID_QSYS_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_QSYS_0_NAME "/dev/sysid_qsys_0"
#define SYSID_QSYS_0_SPAN 8
#define SYSID_QSYS_0_TIMESTAMP 1652791705
#define SYSID_QSYS_0_TYPE "altera_avalon_sysid_qsys"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x5001020
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 80000000
#define TIMER_0_IRQ 1
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 79999
#define TIMER_0_MULT 0.001
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"


/*
 * timer_1 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_1 altera_avalon_timer
#define TIMER_1_ALWAYS_RUN 0
#define TIMER_1_BASE 0x5001000
#define TIMER_1_COUNTER_SIZE 32
#define TIMER_1_FIXED_PERIOD 0
#define TIMER_1_FREQ 80000000
#define TIMER_1_IRQ 0
#define TIMER_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_1_LOAD_VALUE 79999
#define TIMER_1_MULT 0.001
#define TIMER_1_NAME "/dev/timer_1"
#define TIMER_1_PERIOD 1
#define TIMER_1_PERIOD_UNITS "ms"
#define TIMER_1_RESET_OUTPUT 0
#define TIMER_1_SNAPSHOT 1
#define TIMER_1_SPAN 32
#define TIMER_1_TICKS_PER_SEC 1000
#define TIMER_1_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_1_TYPE "altera_avalon_timer"


/*
 * touch_busy configuration
 *
 */

#define ALT_MODULE_CLASS_touch_busy altera_avalon_pio
#define TOUCH_BUSY_BASE 0x4000020
#define TOUCH_BUSY_BIT_CLEARING_EDGE_REGISTER 0
#define TOUCH_BUSY_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TOUCH_BUSY_CAPTURE 0
#define TOUCH_BUSY_DATA_WIDTH 1
#define TOUCH_BUSY_DO_TEST_BENCH_WIRING 0
#define TOUCH_BUSY_DRIVEN_SIM_VALUE 0
#define TOUCH_BUSY_EDGE_TYPE "NONE"
#define TOUCH_BUSY_FREQ 10000000
#define TOUCH_BUSY_HAS_IN 1
#define TOUCH_BUSY_HAS_OUT 0
#define TOUCH_BUSY_HAS_TRI 0
#define TOUCH_BUSY_IRQ -1
#define TOUCH_BUSY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TOUCH_BUSY_IRQ_TYPE "NONE"
#define TOUCH_BUSY_NAME "/dev/touch_busy"
#define TOUCH_BUSY_RESET_VALUE 0
#define TOUCH_BUSY_SPAN 16
#define TOUCH_BUSY_TYPE "altera_avalon_pio"


/*
 * touch_pen_irq_n configuration
 *
 */

#define ALT_MODULE_CLASS_touch_pen_irq_n altera_avalon_pio
#define TOUCH_PEN_IRQ_N_BASE 0x4000030
#define TOUCH_PEN_IRQ_N_BIT_CLEARING_EDGE_REGISTER 0
#define TOUCH_PEN_IRQ_N_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TOUCH_PEN_IRQ_N_CAPTURE 1
#define TOUCH_PEN_IRQ_N_DATA_WIDTH 1
#define TOUCH_PEN_IRQ_N_DO_TEST_BENCH_WIRING 0
#define TOUCH_PEN_IRQ_N_DRIVEN_SIM_VALUE 0
#define TOUCH_PEN_IRQ_N_EDGE_TYPE "FALLING"
#define TOUCH_PEN_IRQ_N_FREQ 10000000
#define TOUCH_PEN_IRQ_N_HAS_IN 1
#define TOUCH_PEN_IRQ_N_HAS_OUT 0
#define TOUCH_PEN_IRQ_N_HAS_TRI 0
#define TOUCH_PEN_IRQ_N_IRQ 3
#define TOUCH_PEN_IRQ_N_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TOUCH_PEN_IRQ_N_IRQ_TYPE "EDGE"
#define TOUCH_PEN_IRQ_N_NAME "/dev/touch_pen_irq_n"
#define TOUCH_PEN_IRQ_N_RESET_VALUE 0
#define TOUCH_PEN_IRQ_N_SPAN 16
#define TOUCH_PEN_IRQ_N_TYPE "altera_avalon_pio"


/*
 * touch_spi configuration
 *
 */

#define ALT_MODULE_CLASS_touch_spi altera_avalon_spi
#define TOUCH_SPI_BASE 0x4000000
#define TOUCH_SPI_CLOCKMULT 1
#define TOUCH_SPI_CLOCKPHASE 0
#define TOUCH_SPI_CLOCKPOLARITY 0
#define TOUCH_SPI_CLOCKUNITS "Hz"
#define TOUCH_SPI_DATABITS 8
#define TOUCH_SPI_DATAWIDTH 16
#define TOUCH_SPI_DELAYMULT "1.0E-9"
#define TOUCH_SPI_DELAYUNITS "ns"
#define TOUCH_SPI_EXTRADELAY 0
#define TOUCH_SPI_INSERT_SYNC 0
#define TOUCH_SPI_IRQ 5
#define TOUCH_SPI_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TOUCH_SPI_ISMASTER 1
#define TOUCH_SPI_LSBFIRST 0
#define TOUCH_SPI_NAME "/dev/touch_spi"
#define TOUCH_SPI_NUMSLAVES 1
#define TOUCH_SPI_PREFIX "spi_"
#define TOUCH_SPI_SPAN 32
#define TOUCH_SPI_SYNC_REG_DEPTH 2
#define TOUCH_SPI_TARGETCLOCK 32000u
#define TOUCH_SPI_TARGETSSDELAY "0.0"
#define TOUCH_SPI_TYPE "altera_avalon_spi"


/*
 * video_pixel_buffer_dma_0 configuration
 *
 */

#define ALT_MODULE_CLASS_video_pixel_buffer_dma_0 altera_up_avalon_video_pixel_buffer_dma
#define VIDEO_PIXEL_BUFFER_DMA_0_BASE 0x50010a0
#define VIDEO_PIXEL_BUFFER_DMA_0_IRQ -1
#define VIDEO_PIXEL_BUFFER_DMA_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define VIDEO_PIXEL_BUFFER_DMA_0_NAME "/dev/video_pixel_buffer_dma_0"
#define VIDEO_PIXEL_BUFFER_DMA_0_SPAN 16
#define VIDEO_PIXEL_BUFFER_DMA_0_TYPE "altera_up_avalon_video_pixel_buffer_dma"


/*
 * video_rgb_resampler_0 configuration
 *
 */

#define ALT_MODULE_CLASS_video_rgb_resampler_0 altera_up_avalon_video_rgb_resampler
#define VIDEO_RGB_RESAMPLER_0_BASE 0x50010c0
#define VIDEO_RGB_RESAMPLER_0_IRQ -1
#define VIDEO_RGB_RESAMPLER_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define VIDEO_RGB_RESAMPLER_0_NAME "/dev/video_rgb_resampler_0"
#define VIDEO_RGB_RESAMPLER_0_SPAN 4
#define VIDEO_RGB_RESAMPLER_0_TYPE "altera_up_avalon_video_rgb_resampler"

#endif /* __SYSTEM_H_ */
