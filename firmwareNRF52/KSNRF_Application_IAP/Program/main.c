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
 *  @date    10-Jan-2018
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "modules\serial.h"
#include "nrf5x_bsp.h"
#include "nrf5x_bootloader.h"

/** @addtogroup NRF5x_Program
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

#include "IAP_GPIO_BINRARY.h"

int main( void )
{
  BSP_CLOCK_Config();
  BSP_GPIO_Config();

  if (KEY_Read()) {
    BSP_UART_SERIAL_Config(NULL);
    nrf_bootloader_set_receiver(Serial_RecvData);

    LED_R_Reset();
    delay_ms(100);

    uint32_t binaryFileSize = 0;
    uint8_t binaryFile[4096] = {0};
    binaryFileSize = nrf_bootloader_download(binaryFile);
    nrf_bootloader_upload(binaryFile, binaryFileSize);

    delay_ms(1000);
    LED_R_Set();

    NVIC_SystemReset();
  }
  else {
    nrf_bootloader_app_start(APPLICATION_ADDR);
  }
}

/*************************************** END OF FILE ****************************************/
