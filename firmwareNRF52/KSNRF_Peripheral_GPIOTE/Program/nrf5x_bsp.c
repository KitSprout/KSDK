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
GPIOTE_InitTypeDef hKey = {
  .Instance      = KEY_GPIOTEx,
  .Pin           = KEY_PIN,
  .Line          = KEY_GPIOTEx_LINE,
  .Mode          = KEY_GPIOTEx_IRQn_MODE,
  .Polarity      = KEY_GPIOTEx_IRQn_POLARITY,
  .OutInit       = KEY_GPIOTEx_IRQn_OUTINIT,
  .EventCallback = NULL
};

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
  GPIOTE_Init(&hKey);

  if (event != NULL) {
    hKey.EventCallback = event;
    NVIC_SetPriority(KEY_GPIOTEx_IRQn, KEY_GPIOTEx_IRQn_PRIORITY);
    NVIC_EnableIRQ(KEY_GPIOTEx_IRQn);
    GPIOTE_IntCmd(&hKey, ENABLE);
  }
}

/*************************************** END OF FILE ****************************************/
