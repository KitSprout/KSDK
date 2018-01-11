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
 *  @date    10-Jan-2018
 *  @brief   
 * 
 */
 
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_uart.h"

/** @addtogroup NRF5x_Driver
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

  huart->Instance->CONFIG   = huart->Parity | 
                              huart->HardwareFlowControl;
  huart->Instance->BAUDRATE = huart->BaudRate;
  UART_Start(huart);
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
 *  @brief  UART_InterruptCmd
 */
void UART_InterruptCmd( UART_InitTypeDef *huart, uint32_t mode, uint32_t state )
{
  if (state == ENABLE) {
    huart->Instance->INTENSET = mode;
  }
  else {
    huart->Instance->INTENCLR = mode;
  }
}

/**
 *  @brief  UART_Start
 */
void UART_Start( UART_InitTypeDef *huart )
{
  UART_EVENTS_TXDRDY(huart->Instance) = RESET;
  UART_EVENTS_RXDRDY(huart->Instance) = RESET;
  UART_TASKS_STARTTX(huart->Instance) = SET;
  UART_TASKS_STARTRX(huart->Instance) = SET;
}

/**
 *  @brief  UART_Stop
 */
void UART_Stop( UART_InitTypeDef *huart )
{
  UART_TASKS_SUSPEND(huart->Instance) = SET;
}

/**
 *  @brief  UART_SendByte
 */
void UART_SendByte( UART_InitTypeDef *huart, uint8_t *sendByte )
{
  huart->Instance->TXD = *sendByte;
  while (UART_EVENTS_TXDRDY(huart->Instance) != SET);   // Wait for TXD data to be sent
  UART_EVENTS_TXDRDY(huart->Instance) = RESET;
}

/**
 *  @brief  UART_RecvByte
 */
void UART_RecvByte( UART_InitTypeDef *huart, uint8_t *recvByte )
{
  while (UART_EVENTS_RXDRDY(huart->Instance) != SET);   // Wait for RXD data to be received
  UART_EVENTS_RXDRDY(huart->Instance) = RESET;
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
    while (UART_EVENTS_TXDRDY(huart->Instance) != SET);
    UART_EVENTS_TXDRDY(huart->Instance) = RESET;
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
    while (UART_EVENTS_RXDRDY(huart->Instance) != SET);
    UART_EVENTS_RXDRDY(huart->Instance) = RESET;
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
    while (UART_EVENTS_TXDRDY(huart->Instance) != SET) {
      if (--timeout) {
        delay_us(1);
      }
      else {
        UART_EVENTS_TXDRDY(huart->Instance) = RESET;
        return KS_TIMEOUT;
      }
    }
    UART_EVENTS_TXDRDY(huart->Instance) = RESET;
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
    while (UART_EVENTS_RXDRDY(huart->Instance) != SET) {
      if (--timeout) {
        delay_us(1);
      }
      else {
        UART_EVENTS_RXDRDY(huart->Instance) = RESET;
        return KS_TIMEOUT;
      }
    }
    UART_EVENTS_RXDRDY(huart->Instance) = RESET;
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
    while (UART_EVENTS_RXDRDY(huart->Instance) != SET) {
      UART_EVENTS_RXDRDY(huart->Instance) = RESET;
      *recvData++ = (uint8_t)huart->Instance->RXD;
      lens++;
      wait = 0x7FFF;
    }
  }

  return lens;
}

/*************************************** END OF FILE ****************************************/
