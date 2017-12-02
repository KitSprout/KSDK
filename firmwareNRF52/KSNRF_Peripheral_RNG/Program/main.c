/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    main.c
 *  @author  KitSprout
 *  @date    01-Dec-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_rng.h"
#include "modules\serial.h"
#include "nrf5x_bsp.h"

/** @addtogroup NRF5x_Program
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
extern RNG_InitTypeDef hrng;
uint8_t randNum;

/* Private function prototypes -------------------------------------------------------------*/
void IRQEvent_RandomGenerate( void );

/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  BSP_CLOCK_Config();
  BSP_RNG_Config(IRQEvent_RandomGenerate);
  BSP_GPIO_Config();
  BSP_UART_SERIAL_Config(NULL);

  while (1) {
    LED_G_Toggle();
    delay_ms(100);

//    randNum = RNG_GetRandomValue(&hrng);
    printf("random number : %3i\r\n", randNum);
  }
}

void IRQEvent_RandomGenerate( void )
{
  randNum = RNG_GetRandomValue(&hrng);
}

/*************************************** END OF FILE ****************************************/
