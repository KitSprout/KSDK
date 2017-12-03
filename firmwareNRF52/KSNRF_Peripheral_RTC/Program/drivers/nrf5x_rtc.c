/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_rtc.c
 *  @author  KitSprout
 *  @date    02-Dec-2017
 *  @brief   
 * 
 */
 
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_rtc.h"

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
 *  @brief  RTC_BaseInit
 */
void RTC_BaseInit( RTC_BaseInitTypeDef *hrtc )
{
  hrtc->Instance->PRESCALER = hrtc->Prescaler;
}

void RTC_ChannelInit( RTC_BaseInitTypeDef *hrtc, RTC_ChannelInitTypeDef *hcompare )
{
  hrtc->Instance->CC[hcompare->Channel] = hcompare->Period;
}

/**
 *  @brief  RTC_Cmd
 */
void RTC_Cmd( RTC_BaseInitTypeDef *hrtc, uint8_t state )
{
  if (state != ENABLE) {
    RTC_TASKS_STOP(hrtc->Instance) = SET;
  }
  else {
    RTC_TASKS_CLEAR(hrtc->Instance) = SET;
    RTC_TASKS_START(hrtc->Instance) = SET;
  }
}

/**
 *  @brief  RTC_InterruptCmd
 */
void RTC_InterruptCmd( RTC_BaseInitTypeDef *hrtc, uint32_t events, uint8_t state )
{
  if (state != ENABLE) {
    hrtc->Instance->INTENCLR |= events;
  }
  else {
    hrtc->Instance->INTENSET |= events;
  }
}

/**
 *  @brief  RTC_RoutingCmd
 */
void RTC_RoutingCmd( RTC_BaseInitTypeDef *hrtc, uint32_t events, uint8_t state )
{
  if (state != ENABLE) {
    hrtc->Instance->EVTENCLR |= events;
  }
  else {
    hrtc->Instance->EVTENSET |= events;
  }
}

/*************************************** END OF FILE ****************************************/
