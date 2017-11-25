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
 *  @date    25-Nov-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_gpiote.h"
#include "nrf5x_bsp.h"

/** @addtogroup NRF52_Program
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

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

void BSP_GPIOE_Config( pFunc event )
{
  GPIOTE_InitTypeDef GPIOTE_InitStruct;

  GPIOTE_InitStruct.Pin      = KEY_PIN;
  GPIOTE_InitStruct.Line     = KEY_IRQx_LINE;
  GPIOTE_InitStruct.Mode     = GPIOTE_CONFIG_MODE_Event;
  GPIOTE_InitStruct.Polarity = KEY_IRQx_POLARITY;
  GPIOTE_InitStruct.Event    = event;
  GPIOTE_Init(&GPIOTE_InitStruct);
  
  if (event != NULL) {
    GPIOTE_IntCmd(KEY_IRQx_LINE, ENABLE);
  }
}

/*************************************** END OF FILE ****************************************/
