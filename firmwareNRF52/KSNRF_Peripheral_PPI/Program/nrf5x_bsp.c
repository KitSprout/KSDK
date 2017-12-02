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
#include "drivers\nrf5x_ppi.h"
#include "drivers\nrf5x_timer.h"
#include "nrf5x_bsp.h"

/** @addtogroup NRF5x_Program
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
TIMER_TimeBaseInitTypeDef htick;
TIMER_TimeBaseInitTypeDef htick_start;
TIMER_TimeBaseInitTypeDef htick_stop;

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

void BSP_TIMER_Config( pFunc event, uint32_t freq )
{
  htick.EventCallback = event;

  htick.Instance  = TIMERx;
  htick.Mode      = TIMERx_MODE;
  htick.BitMode   = TIMERx_BIT_MODE;
  htick.Prescaler = TIMERx_PRESCALER;
  TIMER_TimeBaseInit(&htick);
  TIMER_CCInit(&htick, TIMERx_CHANNEL, freq);   // 1 MHz timer clock

  TIMER_InterruptCmd(&htick, TIMERx_CHANNEL, ENABLE);
  NVIC_SetPriority(TIMERx_IRQn, TIMERx_IRQn_PRIORITY);
  NVIC_EnableIRQ(TIMERx_IRQn);

  htick_start.Instance  = NRF_TIMER1;
  htick_start.Mode      = NRF_TIMER_MODE_TIMER;
  htick_start.BitMode   = NRF_TIMER_BIT_WIDTH_16;
  htick_start.Prescaler = NRF_TIMER_FREQ_31250Hz;
  TIMER_TimeBaseInit(&htick_start);
  TIMER_CCInit(&htick_start, NRF_TIMER_CC_CHANNEL0, 2000 * 31.25f);

  htick_stop.Instance   = NRF_TIMER2;
  htick_stop.Mode       = NRF_TIMER_MODE_TIMER;
  htick_stop.BitMode    = NRF_TIMER_BIT_WIDTH_16;
  htick_stop.Prescaler  = NRF_TIMER_FREQ_31250Hz;
  TIMER_TimeBaseInit(&htick_stop);
  TIMER_CCInit(&htick_stop, NRF_TIMER_CC_CHANNEL0, 1000 * 31.25f);

  TIMER_Cmd(&htick, ENABLE);
  TIMER_Cmd(&htick_start, ENABLE);
  TIMER_Cmd(&htick_stop, ENABLE);
}

void BSP_PPI_Config( void )
{
  PPI_InitTypeDef hppi_start;
  PPI_InitTypeDef hppi_stop;

  hppi_start.Channel          = NRF_PPI_CHANNEL0;
  hppi_start.Group            = NRF_PPI_CHANNEL_GROUP0;
  hppi_start.EventEndPoint    = (uint32_t)(&TIMER_EVENTS_COPPARE(htick_start.Instance, NRF_TIMER_CC_CHANNEL0));
  hppi_start.TaskEndPoint     = (uint32_t)(&TIMER_TASKS_START(htick.Instance));
  hppi_start.ForkState        = DISABLE;
  hppi_start.ForkTaskEndPoint = NULL;
  PPI_Init(&hppi_start);

  hppi_stop.Channel           = NRF_PPI_CHANNEL1;
  hppi_stop.Group             = NRF_PPI_CHANNEL_GROUP0;
  hppi_stop.EventEndPoint     = (uint32_t)(&TIMER_EVENTS_COPPARE(htick_stop.Instance, NRF_TIMER_CC_CHANNEL0));
  hppi_stop.TaskEndPoint      = (uint32_t)(&TIMER_TASKS_STOP(htick.Instance));
  hppi_start.ForkState        = DISABLE;
  hppi_start.ForkTaskEndPoint = NULL;
  PPI_Init(&hppi_stop);

  PPI_ChannelCmd(&hppi_start, ENABLE);
  PPI_ChannelCmd(&hppi_stop,  ENABLE);

//  PPI_SetChannelGroup(&hppi_start, ENABLE);
//  PPI_SetChannelGroup(&hppi_stop,  ENABLE);
//  PPI_GroupCmd(&hppi_start, ENABLE);
//  PPI_GroupCmd(&hppi_stop,  ENABLE);
}

/*************************************** END OF FILE ****************************************/
