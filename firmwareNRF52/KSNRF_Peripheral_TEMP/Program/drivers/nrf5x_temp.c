/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_temp.c
 *  @author  KitSprout
 *  @date    01-Dec-2017
 *  @brief   
 * 
 */
 
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_temp.h"

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
 *  @brief  TEMP_Init
 */
void TEMP_Init( void )
{
  nrf_temp_init();
}

/**
 *  @brief  TEMP_GetTemperature
 */
float32_t TEMP_GetTemperature( void )
{
  float32_t temperature;

  TEMP_TASKS_START();
  while (TEMP_EVENTS_DATARDY() != SET);
  TEMP_EVENTS_DATARDY() = RESET;
  temperature = nrf_temp_read() * 0.25f;

  return (temperature);
}

/*************************************** END OF FILE ****************************************/
