/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_timer.c
 *  @author  KitSprout
 *  @date    01-Dec-2017
 *  @brief   
 * 
 */
 
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_timer.h"

/** @addtogroup NRF5x_Driver
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

/**
 *  @brief  TIMER_TimeBaseInit
 */
void TIMER_TimeBaseInit( TIMER_TimeBaseInitTypeDef *htimer )
{
  htimer->Instance->MODE      = htimer->Mode;
  htimer->Instance->PRESCALER = htimer->Prescaler;
  htimer->Instance->BITMODE   = htimer->BitMode;

  TIMER_TASKS_CLEAR(htimer->Instance) = SET;
}

/**
 *  @brief  TIMER_Cmd
 */
void TIMER_Cmd( TIMER_TimeBaseInitTypeDef *htimer, uint8_t state )
{
  if (state != ENABLE) {
    TIMER_TASKS_STOP(htimer->Instance) = SET;
  }
  else {
    TIMER_TASKS_START(htimer->Instance) = SET;
  }
}

/**
 *  @brief  TIMER_CCInit
 */
void TIMER_CCInit( TIMER_TimeBaseInitTypeDef *htimer, uint32_t channel, uint32_t value )
{
  htimer->Instance->CC[channel] = value;
}

/**
 *  @brief  TIMER_InterruptCmd
 */
void TIMER_InterruptCmd( TIMER_TimeBaseInitTypeDef *htimer, uint32_t channel, uint8_t state )
{
  uint32_t setting;

  switch (channel) {
    case NRF_TIMER_CC_CHANNEL0:
      setting = TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;
      break;
    case NRF_TIMER_CC_CHANNEL1:
      setting = TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos;
      break;
    case NRF_TIMER_CC_CHANNEL2:
      setting = TIMER_INTENSET_COMPARE2_Enabled << TIMER_INTENSET_COMPARE2_Pos;
      break;
    case NRF_TIMER_CC_CHANNEL3:
      setting = TIMER_INTENSET_COMPARE3_Enabled << TIMER_INTENSET_COMPARE3_Pos;
      break;
#if (TIMER_COUNT > 3) || defined(__SDK_DOXYGEN__)
    case NRF_TIMER_CC_CHANNEL4:
      setting = TIMER_INTENSET_COMPARE4_Enabled << TIMER_INTENSET_COMPARE4_Pos;
      break;
    case NRF_TIMER_CC_CHANNEL5:
      setting = TIMER_INTENSET_COMPARE5_Enabled << TIMER_INTENSET_COMPARE5_Pos;
      break;
#endif
  }

  if (state == ENABLE) {
    htimer->Instance->INTENSET |= setting;
  }
  else {
    htimer->Instance->INTENCLR |= setting;
  }
}

/*************************************** END OF FILE ****************************************/
