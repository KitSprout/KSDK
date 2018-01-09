/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_bsp.c
 *  @author  KitSprout
 *  @date    09-Jan-2018
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_clock.h"
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
static RADIO_InitTypeDef hRadio;

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

void BSP_CLOCK_Config( void )
{
  CLOCK_Config();
}

void BSP_GPIO_Config( void )
{
  nrf_gpio_cfg_output(LED_R_PIN);
  nrf_gpio_cfg_output(LED_G_PIN);
  nrf_gpio_cfg_output(LED_B_PIN);
  nrf_gpio_cfg_input(KEY_PIN, NRF_GPIO_PIN_NOPULL);

  LED_R_Set();
  LED_G_Set();
  LED_B_Set();
}

void BSP_UART_SERIAL_Config( pFunc rxEvent )
{
  hSerial.RxEventCallback = rxEvent;

  Serial_Config();
//  kSerial_Config(SERIAL_UARTx);
  printf("\r\nHello World!\r\n\r\n");
}

void BSP_RADIO_Config( void )
{
  uint8_t prefixAddr[8] = { 0x23, 0x00, 0x63, 0xE3, 0x03, 0x83, 0x43, 0xC3 };
  uint32_t baseAddr[2] = { 0x80C4A2E6, 0x91D5B3F7 };

  hRadio.TxPower   = RADIO_TX_POWER;
  hRadio.Frequency = RADIO_RF_FREQ;
  hRadio.Mode      = RADIO_SPEED;
  hRadio.CRC       = RADIO_CRC;
  hRadio.Prefix    = prefixAddr;
  hRadio.BaseAddr  = baseAddr;
  hRadio.TxAddr    = 0x00;
  hRadio.RxAddr    = 0x01;
  RADIO_Init(&hRadio);
}

/*************************************** END OF FILE ****************************************/
