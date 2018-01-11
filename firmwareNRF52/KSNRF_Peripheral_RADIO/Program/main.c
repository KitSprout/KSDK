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
 *  @date    11-Jan-2018
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_timer.h"
#include "drivers\nrf5x_radio.h"
#include "modules\serial.h"
#include "modules\kSerial.h"
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

static uint16_t sec = 0;
static uint16_t msc = 0;

/* Private function prototypes -------------------------------------------------------------*/
void IRQEvent_TimerTick( void );

/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  BSP_CLOCK_Config();
  BSP_GPIO_Config();
  BSP_UART_SERIAL_Config(NULL);
  BSP_RADIO_Config();

  if (KEY_Read()) {
    // RECV
    uint16_t buff[2] = {0};
    while (1) {
      LED_G_Toggle();
      RADIO_RecvPacket(packet, &lens, &rssi);
      buff[0] = (uint16_t)BYTE16(packet[1], packet[0]);
      buff[1] = (uint16_t)BYTE16(packet[3], packet[2]);

#if 1
      printf("[%03i][%04i dBm]", lens, rssi);
      printf(" [%03i, %03i]\r\n", buff[0], buff[1]);

#else
      kSerial_SendPacket(NULL, buff, 2, KS_I16);

#endif
    }
  }
  else {
    // SEND
    BSP_TIMER_Config(IRQEvent_TimerTick);
    while (1) {
      LED_G_Toggle();
//      delay_ms(50);

      packet[0] = BYTE16U8L(sec);
      packet[1] = BYTE16U8H(sec);
      packet[2] = BYTE16U8L(msc);
      packet[3] = BYTE16U8H(msc);
      RADIO_SendPacket(packet, 4);
    }
  }
}

void IRQEvent_TimerTick( void )
{
  if (++msc == 100) {
    msc = 0;
    sec++;
  }
}

/*************************************** END OF FILE ****************************************/
