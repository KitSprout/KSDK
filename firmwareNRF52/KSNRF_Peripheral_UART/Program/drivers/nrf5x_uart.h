/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_uart.h
 *  @author  KitSprout
 *  @date    26-Nov-2017
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __NRF5x_UART_H
#define __NRF5x_UART_H

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes --------------------------------------------------------------------------------*/
#include "nrf.h"

/* Exported types --------------------------------------------------------------------------*/

typedef struct {
  NRF_UART_Type *Instance;

  uint8_t  PinTXD;
  uint8_t  PinRXD;
  uint8_t  PinRTS;
  uint8_t  PinCTS;
  uint32_t Parity;
  // NRF_UART_PARITY_EXCLUDED   - Parity bit excluded.
  // NRF_UART_PARITY_INCLUDED   - Parity bit included.
  uint32_t HardwareFlowControl;
  // NRF_UART_HWFC_DISABLED     - Hardware flow control disabled.
  // NRF_UART_HWFC_ENABLED      - Hardware flow control enabled.
  uint32_t BaudRate;
  // NRF_UART_BAUDRATE_1200     -   1200 baud.
  // NRF_UART_BAUDRATE_2400     -   2400 baud.
  // NRF_UART_BAUDRATE_4800     -   4800 baud.
  // NRF_UART_BAUDRATE_9600     -   9600 baud.
  // NRF_UART_BAUDRATE_14400    -  14400 baud.
  // NRF_UART_BAUDRATE_19200    -  19200 baud.
  // NRF_UART_BAUDRATE_28800    -  28800 baud.
  // NRF_UART_BAUDRATE_38400    -  38400 baud.
  // NRF_UART_BAUDRATE_57600    -  57600 baud.
  // NRF_UART_BAUDRATE_76800    -  76800 baud.
  // NRF_UART_BAUDRATE_115200   - 115200 baud.
  // NRF_UART_BAUDRATE_230400   - 230400 baud.
  // NRF_UART_BAUDRATE_250000   - 250000 baud.
  // NRF_UART_BAUDRATE_460800   - 460800 baud.
  // NRF_UART_BAUDRATE_921600   - 921600 baud.
  // NRF_UART_BAUDRATE_1000000  -     1M baud.
  pFunc TxEventCallback;
  pFunc RxEventCallback;
  // UART EVENT CALLBACK
} UART_InitTypeDef;

/* Exported constants ----------------------------------------------------------------------*/
/* Exported macro --------------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------*/  
void      UART_Init( UART_InitTypeDef *huart );
void      UART_Cmd( UART_InitTypeDef *huart, uint32_t state );
void      UART_IntCmd( UART_InitTypeDef *huart, uint32_t mode, uint32_t state );
void      UART_SendByte( UART_InitTypeDef *huart, uint8_t *sendByte );
void      UART_RecvByte( UART_InitTypeDef *huart, uint8_t *recvData );
uint32_t  UART_SendData( UART_InitTypeDef *huart, uint8_t *sendData, uint32_t lens );
uint32_t  UART_RecvData( UART_InitTypeDef *huart, uint8_t *recvData, uint32_t lens );
uint32_t  UART_SendDataWaitTimeout( UART_InitTypeDef *huart, uint8_t *sendData, uint32_t lens, uint32_t timeout );
uint32_t  UART_RecvDataWaitTimeout( UART_InitTypeDef *huart, uint8_t *recvData, uint32_t lens, uint32_t timeout );
uint32_t  UART_RecvDataContinuous( UART_InitTypeDef *huart, uint8_t *recvData );

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
