/**
 *       __            ____
 *      / /__ _  __   / __/                      __  
 *     / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *    / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *   /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                     /_/   github.com/KitSprout    
 *  
 *  @file    stm32f4_i2cSimu.c
 *  @author  KitSprout
 *  @date    25-Nov-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "stm32f4_system.h"
#include "stm32f4_i2cSimu.h"

/** @addtogroup STM32_Driver
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
#define I2CxS_SCL_L()       __GPIO_RST(pSimuI2c->PortSCL, pSimuI2c->PinSCL)
#define I2CxS_SCL_H()       __GPIO_SET(pSimuI2c->PortSCL, pSimuI2c->PinSCL)
#define I2CxS_SCL_READ()    (__GPIO_READ(pSimuI2c->PortSCL, pSimuI2c->PinSCL) == pSimuI2c->PinSCL)

#define I2CxS_SDA_L()       __GPIO_RST(pSimuI2c->PortSDA, pSimuI2c->PinSDA)
#define I2CxS_SDA_H()       __GPIO_SET(pSimuI2c->PortSDA, pSimuI2c->PinSDA)
#define I2CxS_SDA_READ()    (__GPIO_READ(pSimuI2c->PortSDA, pSimuI2c->PinSDA) == pSimuI2c->PinSDA)

/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

/**
 *  @brief  SimuI2C_Config
 */
void SimuI2C_Config( SimuI2C_InitTypeDef *pSimuI2c )
{
  GPIO_InitTypeDef GPIO_InitStruct; 

  /* GPIO Pin ******************************************************************/
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = pSimuI2c->PinSCL;
  HAL_GPIO_Init(pSimuI2c->PortSCL, &GPIO_InitStruct);

  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = pSimuI2c->PinSDA;
  HAL_GPIO_Init(pSimuI2c->PortSDA, &GPIO_InitStruct);

  I2CxS_SCL_H();
  I2CxS_SDA_H();
}

/**
 *  @brief  SimuI2C_Delay
 */
static void SimuI2C_Delay( SimuI2C_InitTypeDef *pSimuI2c )
{
  uint32_t count = pSimuI2c->Freguency;

  while (count--) {
    __nop();
  }
}

/**
 *  @brief  SimuI2C_Start
 */
void SimuI2C_Start( SimuI2C_InitTypeDef *pSimuI2c )
{
  I2CxS_SDA_H();
  I2CxS_SCL_H();
  SimuI2C_Delay(pSimuI2c);
  I2CxS_SDA_L();
  SimuI2C_Delay(pSimuI2c);
}

/**
 *  @brief  SimuI2C_Stop
 */
void SimuI2C_Stop( SimuI2C_InitTypeDef *pSimuI2c )
{
  I2CxS_SDA_L();
  I2CxS_SCL_H();
  SimuI2C_Delay(pSimuI2c);
  I2CxS_SDA_H();
  SimuI2C_Delay(pSimuI2c);
}

/**
 *  @brief  SimuI2C_SendACK
 */
void SimuI2C_SendACK( SimuI2C_InitTypeDef *pSimuI2c, uint8_t sendACK )
{
  I2CxS_SCL_L();
  if (sendACK) {
    I2CxS_SDA_H();
  }
  else {
    I2CxS_SDA_L();
  }
  SimuI2C_Delay(pSimuI2c);
  I2CxS_SCL_H();
  SimuI2C_Delay(pSimuI2c);
  I2CxS_SCL_L();
  SimuI2C_Delay(pSimuI2c);
}

/**
 *  @brief  SimuI2C_RecvACK
 */
uint8_t SimuI2C_RecvACK( SimuI2C_InitTypeDef *pSimuI2c )
{
  uint8_t recvACK = 0;

  I2CxS_SCL_L();
  I2CxS_SDA_H();
  SimuI2C_Delay(pSimuI2c);
  I2CxS_SCL_H();
  SimuI2C_Delay(pSimuI2c);
  recvACK = I2CxS_SDA_READ();
  I2CxS_SCL_L();
  SimuI2C_Delay(pSimuI2c);

  return recvACK;
}

/**
 *  @brief  SimuI2C_SendByte
 */
void SimuI2C_SendByte( SimuI2C_InitTypeDef *pSimuI2c, uint8_t sendByte )
{
  for (uint32_t i = 8; i > 0; i--) {
    I2CxS_SCL_L();
    SimuI2C_Delay(pSimuI2c);
    if(sendByte & 0x80) {   /* MSB First */
      I2CxS_SDA_H();
    }
    else {
      I2CxS_SDA_L();
    }
    sendByte = sendByte << 1;
    SimuI2C_Delay(pSimuI2c);
    I2CxS_SCL_H();
    SimuI2C_Delay(pSimuI2c);
  }
  I2CxS_SCL_L();
}

/**
 *  @brief  SimuI2C_RecvByte
 */
uint8_t SimuI2C_RecvByte( SimuI2C_InitTypeDef *pSimuI2c )
{
  uint8_t recvByte = 0;

  I2CxS_SDA_H();
  for (uint32_t i = 8; i > 0; i--) {
    recvByte = recvByte << 1;
    I2CxS_SCL_L();
    SimuI2C_Delay(pSimuI2c);
    I2CxS_SCL_H();
    SimuI2C_Delay(pSimuI2c);
    if(I2CxS_SDA_READ()) {
      recvByte |= 0x01;
    }
  }
  I2CxS_SCL_L();

  return recvByte;
}

/**
 *  @brief  SimuI2C_WriteData
 */
void SimuI2C_WriteData( SimuI2C_InitTypeDef *pSimuI2c, uint8_t slaveAddr, uint8_t *writeData, uint8_t lens )
{
  SimuI2C_Start(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, slaveAddr);
  SimuI2C_RecvACK(pSimuI2c);
  for (uint32_t i = 0; i < lens; i++) {
    SimuI2C_SendByte(pSimuI2c, writeData[i]);
    SimuI2C_RecvACK(pSimuI2c);
  }
  SimuI2C_Stop(pSimuI2c);
}

/**
 *  @brief  SimuI2C_ReadData
 */
void SimuI2C_ReadData( SimuI2C_InitTypeDef *pSimuI2c, uint8_t slaveAddr, uint8_t *readData, uint8_t lens )
{
  SimuI2C_Start(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, slaveAddr | 0x01);
  SimuI2C_RecvACK(pSimuI2c);
  for (uint32_t i = 0; i < lens; i++) {
    readData[i] = SimuI2C_RecvByte(pSimuI2c);
    if (i == (lens - 1)) {
      SimuI2C_SendACK(pSimuI2c, 1);
    }
    else {
      SimuI2C_SendACK(pSimuI2c, 0);
    }
  }
  SimuI2C_Stop(pSimuI2c);
}

/**
 *  @brief  SimuI2C_WriteReg
 */
void SimuI2C_WriteReg( SimuI2C_InitTypeDef *pSimuI2c, uint8_t slaveAddr, uint8_t writeAddr, uint8_t writeData )
{
  SimuI2C_Start(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, slaveAddr);
  SimuI2C_RecvACK(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, writeAddr);
  SimuI2C_RecvACK(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, writeData);
  SimuI2C_RecvACK(pSimuI2c);
  SimuI2C_Stop(pSimuI2c);
}

/**
 *  @brief  SimuI2C_ReadReg
 */
void SimuI2C_ReadReg( SimuI2C_InitTypeDef *pSimuI2c, uint8_t slaveAddr, uint8_t readAddr, uint8_t *readData )
{
  SimuI2C_Start(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, slaveAddr);
  SimuI2C_RecvACK(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, readAddr);
  SimuI2C_RecvACK(pSimuI2c);
  SimuI2C_Start(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, slaveAddr | 0x01);
  SimuI2C_RecvACK(pSimuI2c);
  *readData = SimuI2C_RecvByte(pSimuI2c);
  SimuI2C_SendACK(pSimuI2c, 1);
  SimuI2C_Stop(pSimuI2c);
}

/**
 *  @brief  SimuI2C_WriteRegs
 */
void SimuI2C_WriteRegs( SimuI2C_InitTypeDef *pSimuI2c, uint8_t slaveAddr, uint8_t writeAddr, uint8_t *writeData, uint8_t lens )
{
  SimuI2C_Start(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, slaveAddr);
  SimuI2C_RecvACK(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, writeAddr);
  SimuI2C_RecvACK(pSimuI2c);
  for (uint32_t i = 0; i < lens; i++) {
    SimuI2C_SendByte(pSimuI2c, writeData[i]);
    SimuI2C_RecvACK(pSimuI2c);
  }
  SimuI2C_Stop(pSimuI2c);
}

/**
 *  @brief  SimuI2C_ReadRegs
 */
void SimuI2C_ReadRegs( SimuI2C_InitTypeDef *pSimuI2c, uint8_t slaveAddr, uint8_t readAddr, uint8_t *readData, uint8_t lens )
{
  SimuI2C_Start(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, slaveAddr);
  SimuI2C_RecvACK(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, readAddr);
  SimuI2C_RecvACK(pSimuI2c);
  SimuI2C_Start(pSimuI2c);
  SimuI2C_SendByte(pSimuI2c, slaveAddr | 0x01);
  SimuI2C_RecvACK(pSimuI2c);
  for (uint32_t i = 0; i < lens; i++) {
    readData[i] = SimuI2C_RecvByte(pSimuI2c);
    if(i == lens - 1) {
      SimuI2C_SendACK(pSimuI2c, 1);
    }
    else {
      SimuI2C_SendACK(pSimuI2c, 0);
    }
  }
  SimuI2C_Stop(pSimuI2c);
}

/*************************************** END OF FILE ****************************************/
