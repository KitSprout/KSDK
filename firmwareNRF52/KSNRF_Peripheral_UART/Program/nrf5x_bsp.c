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
#include "modules\serial.h"
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

void BSP_UART_SERIAL_Config( pFunc rxEvent )
{
  hSerial.RxEventCallback = rxEvent;

  Serial_Config();
//  kSerial_Config(SERIAL_UARTx);
  printf("\r\nHello World!\r\n\r\n");
}

/*************************************** END OF FILE ****************************************/
