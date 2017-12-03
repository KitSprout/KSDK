/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_bsp.c
 *  @author  KitSprout
 *  @date    01-Dec-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_clock.h"
#include "drivers\nrf5x_rtc.h"
#include "nrf5x_bsp.h"

/** @addtogroup NRF5x_Program
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
RTC_BaseInitTypeDef hrtc;
RTC_ChannelInitTypeDef hrtc_ch;

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

void BSP_CLOCK_Config( void )
{
  CLOCK_Config();
}

void BSP_GPIO_Config( void )
{
  nrf_gpio_cfg_output(LED_R_PIN);
  nrf_gpio_cfg_output(LED_G_PIN);
  nrf_gpio_cfg_output(LED_B_PIN);
  nrf_gpio_cfg_input(KEY_PIN, NRF_GPIO_PIN_NOPULL);

  LED_R_Set();
  LED_G_Set();
  LED_B_Set();
}

void BSP_RTC_Config( pFunc eventTick, pFunc eventCompare )
{
  hrtc.Instance              = RTCx;
  hrtc.Prescaler             = RTC_FREQ_TO_PRESCALER(RTCx_CLOCK_FREQ);
  hrtc.TickEventCallback     = eventTick;
  hrtc.OverflowEventCallback = NULL;
  RTC_BaseInit(&hrtc);

  hrtc_ch.Channel       = RTCx_CHANNEL;
  hrtc_ch.Period        = RTCx_CHANNEL_PERIOD;
  hrtc_ch.EventCallback = eventCompare;
  RTC_ChannelInit(&hrtc, &hrtc_ch);

  if (eventTick != NULL) {
    RTC_InterruptCmd(&hrtc, NRF_RTC_INT_TICK_MASK, ENABLE);
//    RTC_RoutingCmd(&hrtc, NRF_RTC_INT_TICK_MASK, ENABLE);
  }
  if (eventCompare != NULL) {
    RTC_InterruptCmd(&hrtc, NRF_RTC_INT_COMPARE0_MASK, ENABLE);
//    RTC_RoutingCmd(&hrtc, NRF_RTC_INT_COMPARE0_MASK, ENABLE);
  }
  if ((eventTick != NULL) || (eventCompare != NULL)) {
    NVIC_SetPriority(RTCx_IRQn, RTCx_IRQn_PRIORITY);
    NVIC_EnableIRQ(RTCx_IRQn);
  }

  RTC_Cmd(&hrtc, ENABLE);
}

/*************************************** END OF FILE ****************************************/
