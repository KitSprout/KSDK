/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    ist8308.c
 *  @author  KitSprout
 *  @date    25-Nov-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f4_system.h"
#include "drivers\stm32f4_i2cSimu.h"
#include "modules\ist8308.h"

/** @addtogroup STM32_Module
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
#define IST83_Delay(__MS)   delay_ms(__MS)

/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
static SimuI2C_InitTypeDef IST83_SimuI2C;

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

/**
 *  @brief  IST83_WriteReg
 */
void IST83_WriteReg( uint8_t writeAddr, uint8_t writeData )
{
  SimuI2C_WriteReg(&IST83_SimuI2C, IST8308_I2C_ADDR, writeAddr, writeData);
}

/**
 *  @brief  IST83_WriteRegs
 */
void IST83_WriteRegs( uint8_t writeAddr, uint8_t *writeData, uint8_t lens )
{
  SimuI2C_WriteRegs(&IST83_SimuI2C, IST8308_I2C_ADDR, writeAddr, writeData, lens);
}

/**
 *  @brief  IST83_ReadReg
 */
uint8_t IST83_ReadReg( uint8_t writeAddr )
{
  uint8_t readData;
  SimuI2C_ReadReg(&IST83_SimuI2C, IST8308_I2C_ADDR, writeAddr, &readData);
  return readData;
}

/**
 *  @brief  IST83_ReadRegs
 */
void IST83_ReadRegs( uint8_t writeAddr, uint8_t *readData, uint8_t lens )
{
  SimuI2C_ReadRegs(&IST83_SimuI2C, IST8308_I2C_ADDR, writeAddr, readData, lens);
}

/**
 *  @brief  IST83_Config
 */
void IST83_Config( void )
{
  IST83_SimuI2C.PinSCL    = IMU_SCL_PIN;
  IST83_SimuI2C.PortSCL   = IMU_SCL_GPIO_PORT;
  IST83_SimuI2C.PinSDA    = IMU_SDA_PIN;
  IST83_SimuI2C.PortSDA   = IMU_SDA_GPIO_PORT;
  IST83_SimuI2C.Freguency = 16;
  SimuI2C_Config(&IST83_SimuI2C);
}

/**
 *  @brief  IST83_Init
 */
#define IST83_INIT_REG_LENS 5
uint32_t IST83_Init( void )
{
  uint8_t IST83_InitData[IST83_INIT_REG_LENS][2] = {
    {0x01, IST8308_CNTL3},      /* [0] Soft resert                                  */
    {0x20, IST8308_CNTL1},      /* [1] Noise Suppression Filter : Low               */
    {0x00, IST8308_CNTL4},      /* [2] Dynamic Range ±500uT, Sensitivity 6.6 LSB/uT */
    {0x1B, IST8308_OSRCNTL},    /* [3] OSR = 8, 200Hz                               */
    {0x0A, IST8308_CNTL2},      /* [4] Continuous Measurement Mode with ODR 200Hz   */
  };

  if (IST83_DeviceCheck() != SUCCESS) {
    return ERROR;
  }

  IST83_Delay(10);
  IST83_WriteReg(IST83_InitData[0][1], IST83_InitData[0][0]);
  IST83_Delay(50);
  IST83_WriteReg(IST83_InitData[1][1], IST83_InitData[1][0]);
  IST83_WriteReg(IST83_InitData[2][1], IST83_InitData[2][0]);
  IST83_WriteReg(IST83_InitData[3][1], IST83_InitData[3][0]);
  IST83_WriteReg(IST83_InitData[4][1], IST83_InitData[4][0]);
  IST83_Delay(10);

  return SUCCESS;
}

/**
 *  @brief  IST83_DeviceCheck
 */
uint32_t IST83_DeviceCheck( void )
{
  uint8_t deviceID = IST83_ReadReg(IST8308_WAI);

#if 0
  printf("id = 0x%02X\r\n", deviceID);
//  return ERROR;
#endif

  if (deviceID != IST8308_DEVICD_ID) {
    return ERROR;
  }

  return SUCCESS;
}

/**
 *  @brief  IST83_GetRawData
 */
uint32_t IST83_GetRawData( int16_t *raw )
{
  if ((IST83_ReadReg(IST8308_STAT) & 0x01) == 0x01) {
    uint8_t buff[6];
    IST83_ReadRegs(IST8308_DATAXL, buff, 6);

    // NED
    raw[0] = -(((int16_t)buff[3]) << 8) | buff[2];
    raw[1] =  (((int16_t)buff[1]) << 8) | buff[0];
    raw[2] = -(((int16_t)buff[5]) << 8) | buff[4];
    return SUCCESS;
  }

  return ERROR;
}

/**
 *  @brief  IST83_GetData
 */
uint32_t IST83_GetData( float32_t *raw )
{
  if ((IST83_ReadReg(IST8308_STAT) & 0x01) == 0x01) {
    uint8_t buff[6];
    IST83_ReadRegs(IST8308_DATAXL, buff, 6);

    // NED
    raw[0] = -((((int16_t)buff[3]) << 8) | buff[2]) * IST8308_SENS_500UT;
    raw[1] =  ((((int16_t)buff[1]) << 8) | buff[0]) * IST8308_SENS_500UT;
    raw[2] = -((((int16_t)buff[5]) << 8) | buff[4]) * IST8308_SENS_500UT;
    return SUCCESS;
  }

  return ERROR;
}

/*************************************** END OF FILE ****************************************/
