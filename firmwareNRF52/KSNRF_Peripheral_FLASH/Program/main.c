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
#include "drivers\nrf5x_flash.h"
#include "modules\serial.h"
#include "nrf5x_bsp.h"

/** @addtogroup NRF5x_Program
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
uint32_t w_data[1024] = {0};
uint32_t r_data[1024] = {0};

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  uint32_t pg_size;
  uint32_t pg_num;
  uint32_t address;
  uint32_t error = 0;

  BSP_CLOCK_Config();
  BSP_GPIO_Config();
  BSP_UART_SERIAL_Config(NULL);

  pg_size = FLASH_PAGE_SIZE;
  pg_num  = FLASH_SIZE - 1;  // Use last page in flash
  address = pg_size * pg_num;
  printf("address = %d, page size = %d, page num = %d\n\r", address, pg_size, pg_num);

  FLASH_ErasePage(address);

  for (uint32_t i = 0; i < pg_size; i++)
  {
    w_data[i] = i;
  }

  FLASH_WriteDataU32(address, w_data, pg_size >> 2);
  FLASH_ReadDataU32(address, r_data, pg_size >> 2);
  for (uint32_t i = 0; i < pg_size >> 2; i++)
  {
    if (w_data[i] != r_data[i])
    {
      error++;
    }
  }

  if (error == 0) {
    LED_G_Reset();
    LED_R_Set();
    printf("flash read / write ... OK\n\r");
  }
  else {
    LED_G_Set();
    LED_R_Reset();
    printf("flash read / write ... ERROR\n\r");
  }

  while (1) {
    LED_B_Toggle();
    delay_ms(100);
  }
}

/*************************************** END OF FILE ****************************************/
