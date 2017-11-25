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
 *  @date    17-Oct-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f4_system.h"
#include "modules\serial.h"
#include "modules\icm20948.h"
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
  BSP_IMU_GYR_ACC_Config();

  while (1) {
    LED_G_Toggle();
    delay_ms(100);

    int16_t imu[10] = {0};
    uint32_t status;
    status = ICM94_GetRawData(imu);
    printf("[%i][gyr] %6i %6i %6i [acc] %6i %6i %6i [mag] %6i %6i %6i [temp] %6i\r\n", status, imu[1], imu[2], imu[3], imu[4], imu[5], imu[6], imu[7], imu[8], imu[9], imu[0]);
  }
}

/*************************************** END OF FILE ****************************************/
