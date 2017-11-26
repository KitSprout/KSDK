/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_uart.c
 *  @author  KitSprout
 *  @date    26-Nov-2017
 *  @brief   
 * 
 */
 
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_uart.h"

/** @addtogroup NRF52_Driver
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

/**
 *  @brief  UART_Init
 */
void UART_Init( UART_InitTypeDef *huart )
{
  nrf_gpio_cfg_output(huart->PinTXD);
  nrf_gpio_cfg_input(huart->PinRXD, NRF_GPIO_PIN_NOPULL);

  huart->Instance->PSELTXD = huart->PinTXD;
  huart->Instance->PSELRXD = huart->PinRXD;

  if (huart->HardwareFlowControl == NRF_UART_HWFC_ENABLED) {
    nrf_gpio_cfg_output(huart->PinRTS);
    nrf_gpio_cfg_input(huart->PinCTS, NRF_GPIO_PIN_NOPULL);
    huart->Instance->PSELCTS = huart->PinCTS;
    huart->Instance->PSELRTS = huart->PinRTS;
  }

  huart->Instance->CONFIG        = huart->Parity | 
                                  huart->HardwareFlowControl;
  huart->Instance->BAUDRATE      = huart->BaudRate;
  huart->Instance->TASKS_STARTTX = 1;
  huart->Instance->TASKS_STARTRX = 1;
  huart->Instance->EVENTS_RXDRDY = 0;
}

/**
 *  @brief  UART_Cmd
 */
void UART_Cmd( UART_InitTypeDef *huart, uint32_t state )
{
  if (state != ENABLE) {
    huart->Instance->ENABLE = UART_ENABLE_ENABLE_Disabled;
  }
  else {
    huart->Instance->ENABLE = UART_ENABLE_ENABLE_Enabled;
  }
}

/**
 *  @brief  UART_IntCmd
 */
void UART_IntCmd( UART_InitTypeDef *huart, uint32_t mode, uint32_t state )
{
  if (state == ENABLE) {
    huart->Instance->INTENSET = mode;
  }
  else {
    huart->Instance->INTENCLR = mode;
  }
}

/**
 *  @brief  UART_SendByte
 */
void UART_SendByte( UART_InitTypeDef *huart, uint8_t *sendByte )
{
  huart->Instance->TXD = *sendByte;
  while (huart->Instance->EVENTS_TXDRDY != SET);   // Wait for TXD data to be sent
  huart->Instance->EVENTS_TXDRDY = RESET;
}

/**
 *  @brief  UART_RecvByte
 */
void UART_RecvByte( UART_InitTypeDef *huart, uint8_t *recvByte )
{
  while (huart->Instance->EVENTS_RXDRDY != SET);   // Wait for RXD data to be received
  huart->Instance->EVENTS_RXDRDY = RESET;
  *recvByte = (uint8_t)huart->Instance->RXD;
}

/**
 *  @brief  UART_SendData
 */
uint32_t UART_SendData( UART_InitTypeDef *huart, uint8_t *sendData, uint32_t lens )
{
  if ((sendData == NULL) || (lens == 0)) {
    return KS_ERROR;
  }

  while (lens--) {
    huart->Instance->TXD = *sendData++;
    while (huart->Instance->EVENTS_TXDRDY != SET);
    huart->Instance->EVENTS_TXDRDY = RESET;
  }

  return KS_OK;
}

/**
 *  @brief  UART_RecvData
 */
uint32_t UART_RecvData( UART_InitTypeDef *huart, uint8_t *recvData, uint32_t lens )
{
  if ((recvData == NULL) || (lens == 0)) {
    return KS_ERROR;
  }

  while (lens--) {
    while (huart->Instance->EVENTS_RXDRDY != SET);
    huart->Instance->EVENTS_RXDRDY = RESET;
    *recvData++ = (uint8_t)huart->Instance->RXD;
  }

  return KS_OK;
}

/**
 *  @brief  UART_SendDataWaitTimeout
 */
uint32_t UART_SendDataWaitTimeout( UART_InitTypeDef *huart, uint8_t *sendData, uint32_t lens, uint32_t timeout )
{
  if ((sendData == NULL) || (lens == 0)) {
    return KS_ERROR;
  }

  while (lens--) {
    huart->Instance->TXD = *sendData++;
    while (huart->Instance->EVENTS_TXDRDY != SET) {
      if (--timeout) {
        delay_us(1);
      }
      else {
        huart->Instance->EVENTS_TXDRDY = RESET;
        return KS_TIMEOUT;
      }
    }
    huart->Instance->EVENTS_TXDRDY = RESET;
  }

  return KS_OK;
}

/**
 *  @brief  UART_RecvDataWaitTimeout
 */
uint32_t UART_RecvDataWaitTimeout( UART_InitTypeDef *huart, uint8_t *recvData, uint32_t lens, uint32_t timeout )
{
  if ((recvData == NULL) || (lens == 0)) {
    return KS_ERROR;
  }

  while (lens--) {
    while (huart->Instance->EVENTS_RXDRDY != SET) {
      if (--timeout) {
        delay_us(1);
      }
      else {
        huart->Instance->EVENTS_RXDRDY = RESET;
        return KS_TIMEOUT;
      }
    }
    huart->Instance->EVENTS_RXDRDY = RESET;
    *recvData++ = (uint8_t)huart->Instance->RXD;
  }

  return KS_OK;
}

/**
 *  @brief  UART_RecvDataContinuous
 */
uint32_t UART_RecvDataContinuous( UART_InitTypeDef *huart, uint8_t *recvData )
{
  uint32_t lens = 0;
  uint32_t wait = 0x7FFF; // about 32767 clocks

  while (wait--) {
    while (huart->Instance->EVENTS_RXDRDY != SET) {
      huart->Instance->EVENTS_TXDRDY = RESET;
      *recvData++ = (uint8_t)huart->Instance->RXD;
      lens++;
      wait = 0x7FFF;
    }
  }

  return lens;
}

/*************************************** END OF FILE ****************************************/
