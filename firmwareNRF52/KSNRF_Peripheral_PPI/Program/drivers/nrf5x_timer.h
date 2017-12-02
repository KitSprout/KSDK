/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_timer.h
 *  @author  KitSprout
 *  @date    01-Dec-2017
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __NRF5x_TIMER_H
#define __NRF5x_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"

/* Exported types --------------------------------------------------------------------------*/

typedef struct {
  NRF_TIMER_Type *Instance;

  uint32_t Prescaler;
  // NRF_TIMER_FREQ_16MHz   - Timer frequency 16 MHz.
  // NRF_TIMER_FREQ_8MHz    - Timer frequency 8 MHz.
  // NRF_TIMER_FREQ_4MHz    - Timer frequency 4 MHz.
  // NRF_TIMER_FREQ_2MHz    - Timer frequency 2 MHz.
  // NRF_TIMER_FREQ_1MHz    - Timer frequency 1 MHz.
  // NRF_TIMER_FREQ_500kHz  - Timer frequency 500 kHz.
  // NRF_TIMER_FREQ_250kHz  - Timer frequency 250 kHz.
  // NRF_TIMER_FREQ_125kHz  - Timer frequency 125 kHz.
  // NRF_TIMER_FREQ_62500Hz - Timer frequency 62500 Hz.
  // NRF_TIMER_FREQ_31250Hz - Timer frequency 31250 Hz.
  uint32_t Period;
  // 32bit value
  uint32_t Mode;
  // NRF_TIMER_MODE_TIMER   - Timer in Normal mode.
  // NRF_TIMER_MODE_COUNTER - Timer in Counter mode.
  uint32_t BitMode;
  // NRF_TIMER_BIT_WIDTH_8  -  8-bit timer behaviour.
  // NRF_TIMER_BIT_WIDTH_16 - 16-bit timer behaviour.
  // NRF_TIMER_BIT_WIDTH_24 - 24-bit timer behaviour.
  // NRF_TIMER_BIT_WIDTH_32 - 32-bit timer behaviour.
  pFunc EventCallback;
  // TIMER EVENT CALLBACK
} TIMER_TimeBaseInitTypeDef;

/* Exported constants ----------------------------------------------------------------------*/
/* Exported macro --------------------------------------------------------------------------*/

#define TIMER_TASKS_START(__INS)            __INS->TASKS_START            // Start Timer
#define TIMER_TASKS_STOP(__INS)             __INS->TASKS_STOP             // Stop Timer
#define TIMER_TASKS_COUNT(__INS)            __INS->TASKS_COUNT            // Increment Timer (Counter mode only)
#define TIMER_TASKS_CLEAR(__INS)            __INS->TASKS_CLEAR            // Clear time
#define TIMER_TASKS_SHUTDOWN(__INS)         __INS->TASKS_SHUTDOWN         // Shut down timer
#define TIMER_TASKS_CAPTURE(__INS, __CH)    __INS->TASKS_CAPTURE[__CH]    // Capture Timer value to CC[x] register

#define TIMER_EVENTS_COPPARE(__INS, __CH)   __INS->EVENTS_COMPARE[__CH]   // Compare event on CC[x] match

/* Exported functions ----------------------------------------------------------------------*/  
void      TIMER_TimeBaseInit( TIMER_TimeBaseInitTypeDef *htimer );
void      TIMER_Cmd( TIMER_TimeBaseInitTypeDef *htimer, uint8_t state );
void      TIMER_CCInit( TIMER_TimeBaseInitTypeDef *htimer, uint32_t channel, uint32_t value );
void      TIMER_InterruptCmd( TIMER_TimeBaseInitTypeDef *htimer, uint32_t channel, uint8_t state );

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
