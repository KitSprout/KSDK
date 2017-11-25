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
 *  @date    25-Nov-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f4_system.h"
#include "modules\serial.h"
#include "modules\ist8308.h"
#include "stm32f4xx_bsp.h"

/** @addtogroup STM32_Program
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  HAL_Init();
  BSP_GPIO_Config();
  BSP_UART_SERIAL_Config(NULL);
  BSP_IMU_MAG_Config();

  while (1) {
    LED_G_Toggle();
    delay_ms(100);

    int16_t mag[3] = {0};
    uint32_t status;
    status = IST83_GetRawData(mag);
    printf("[%i][mag] %6i %6i %6i\r\n", status, mag[0], mag[1], mag[2]);
  }
}

/*************************************** END OF FILE ****************************************/
