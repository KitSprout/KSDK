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
#include "modules\lps22hb.h"
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
  BSP_IMU_LPS22HB_Config();

  float32_t pressure = 1013.0f, temperature = 22.0f, altitude = 0.0f;
  while (1) {
    LED_G_Toggle();
    delay_ms(50);

    float32_t baro[2] = {0};
    LPS22_GetData(baro);

    pressure    = 0.2f * baro[0] + 0.8f * pressure;
    temperature = 0.2f * baro[1] + 0.8f * temperature;
    altitude    = LPS22_GetAltitude(pressure);
    printf(" %8.2f hPa, %7.2f degC, %8.2f m\r\n", pressure, temperature, altitude);
  }
}

/*************************************** END OF FILE ****************************************/
