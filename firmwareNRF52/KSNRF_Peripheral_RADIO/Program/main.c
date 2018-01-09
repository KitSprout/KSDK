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
 *  @date    09-Jan-2018
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_radio.h"
#include "modules\serial.h"
#include "nrf5x_bsp.h"

/** @addtogroup NRF5x_Program
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
static int8_t rssi = 0;
static uint8_t lens = 0;
static uint8_t packet[256];

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  BSP_CLOCK_Config();
  BSP_GPIO_Config();
  BSP_UART_SERIAL_Config(NULL);
  BSP_RADIO_Config();

  if (KEY_Read()) {
    // RECV
    while (1) {
      LED_G_Toggle();
      RADIO_RecvPacket(packet, &lens, &rssi);
      printf("[%03i][%04i dBm]", lens, rssi);
      for (uint8_t i = 0; i < lens; i++) {
        printf(" %02X", packet[i]);
      }
      printf("\r\n");
    }
  }
  else {
    // SEND
    while (1) {
      LED_G_Toggle();
      delay_ms(50);

      packet[0] = packet[0] + 1;
      packet[1] = packet[1] + 2;
      packet[2] = packet[2] + 4;
      packet[3] = packet[3] + 8;
      packet[4] = 0x0A;
      packet[5] = 0x0B;
      packet[6] = 0x0C;
      packet[7] = 0x0D;
      RADIO_SendPacket(packet, 8);
    }
  }
}

/*************************************** END OF FILE ****************************************/
