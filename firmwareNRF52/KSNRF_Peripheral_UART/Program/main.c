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
#include "modules\serial.h"
#include "nrf5x_bsp.h"

/** @addtogroup NRF5x_Program
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
void IRQEvent_SerialRecv( void );

/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  static uint8_t i = 0;
  static uint8_t recvData[16] = {0};

  BSP_CLOCK_Config();
  BSP_GPIO_Config();

  if (!KEY_Read()) {
    BSP_UART_SERIAL_Config(NULL);

    while (1) {
      uint32_t status = Serial_RecvDataWaitTimeout(recvData, 1, 500000);

      if (status == KS_TIMEOUT) {
        LED_R_Toggle();
        printf("Timeout ... %d\r\n", i);
        i = (i == 255) ? 0 : i + 1;
      }
      else if (recvData[0] == 0x0D) { // if press enter
        LED_G_Toggle();
        printf("\r\n");
      }
      else {
        LED_B_Toggle();
        Serial_SendDataWaitTimeout(recvData, 1, 2000000);
      }
      if (KEY_Read()) {
        printf("\f");
      }
    }
  }
  else {
    BSP_UART_SERIAL_Config(IRQEvent_SerialRecv);
    while (1) {
      LED_B_Toggle();
      delay_ms(100);
      while (KEY_Read()) {
        printf("\f");
      }
    }
  }

}

void IRQEvent_SerialRecv( void )
{
  uint8_t recvByte = Serial_RecvByte();

  LED_G_Toggle();
  if (recvByte == 0x0D) {
    printf("\r\n");
  }
  else {
    Serial_SendByte(recvByte);
  }
}

/*************************************** END OF FILE ****************************************/
