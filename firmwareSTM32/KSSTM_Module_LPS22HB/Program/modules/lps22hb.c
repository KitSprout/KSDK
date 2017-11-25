/**
 *       __            ____
 *      / /__ _  __   / __/                      __  
 *     / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *    / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *   /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                     /_/   github.com/KitSprout    
 * 
 *  @file    lps22hb.c
 *  @author  KitSprout
 *  @date    25-Nov-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f4_system.h"
#include "drivers\stm32f4_spi.h"
#include "modules\lps22hb.h"

/** @addtogroup STM32_Module
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

/**
 *  @brief  LPS22_WriteReg
 */
void LPS22_WriteReg( uint8_t writeAddr, uint8_t writeData )
{
  IMU_CSB_L();
  SPI_RW(hImu.handle, writeAddr);
  SPI_RW(hImu.handle, writeData);
  IMU_CSB_H();
}

/**
 *  @brief  LPS22_WriteRegs
 */
void LPS22_WriteRegs( uint8_t writeAddr, uint8_t *writeData, uint8_t lens )
{
  IMU_CSB_L();
  SPI_RW(hImu.handle, writeAddr);
  for (uint32_t i = 0; i < lens; i++) {
    SPI_RW(hImu.handle, writeData[i]);
  }
  IMU_CSB_H();
}

/**
 *  @brief  LPS22_ReadReg
 */
uint8_t LPS22_ReadReg( uint8_t readAddr )
{
  uint8_t readData;

  IMU_CSB_L();
  SPI_RW(hImu.handle, 0x80 | readAddr);
  readData = SPI_RW(hImu.handle, 0x00);
  IMU_CSB_H();

  return readData;
}

/**
 *  @brief  LPS22_ReadRegs
 */
void LPS22_ReadRegs( uint8_t readAddr, uint8_t *readData, uint8_t lens )
{
  IMU_CSB_L();
  SPI_RW(hImu.handle, 0x80 | readAddr);
  for (uint32_t i = 0; i < lens; i++) {
    readData[i] = SPI_RW(hImu.handle, 0x00);
  }
  IMU_CSB_H();
}

/**
 *  @brief  LPS22_Config
 */
void LPS22_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* SPI Pin ******************************************************************/
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = IMU_CSB_PIN;
  HAL_GPIO_Init(IMU_CSB_GPIO_PORT, &GPIO_InitStruct);

  IMU_CSB_H();    // LOW ENABLE

  /* SPI Init ****************************************************************/
  hImu.handle->Instance               = IMU_SPIx;
  hImu.handle->Init.Mode              = SPI_MODE_MASTER;
  hImu.handle->Init.Direction         = SPI_DIRECTION_2LINES;
  hImu.handle->Init.DataSize          = SPI_DATASIZE_8BIT;
  hImu.handle->Init.CLKPolarity       = SPI_POLARITY_HIGH;
  hImu.handle->Init.CLKPhase          = SPI_PHASE_2EDGE;
  hImu.handle->Init.NSS               = SPI_NSS_SOFT;
  hImu.handle->Init.BaudRatePrescaler = IMU_SPIx_SPEED_LOW;
  hImu.handle->Init.FirstBit          = SPI_FIRSTBIT_MSB;
  hImu.handle->Init.TIMode            = SPI_TIMODE_DISABLE;
  hImu.handle->Init.CRCCalculation    = SPI_CRCCALCULATION_ENABLE;
  hImu.handle->Init.CRCPolynomial     = 7;
  HAL_SPI_Init(hImu.handle);

  __HAL_SPI_ENABLE(hImu.handle);
}

/**
 *  @brief  LPS22_Init
 */
//#define LPS22HB_InitRegNum    5
uint32_t LPS22_Init( void )
{
  uint8_t treg = 0;
//  uint8_t LPS22HB_InitData[LPS22HB_InitRegNum][2] = {
//    {0x00, LPS22HB_RES_CONF},       /* [0]  Normal mode (low-noise mode)  */
//    {0x04, MPU6500_PWR_MGMT_1},     /* [1]  Clock Source                  */
//    {0x10, MPU6500_INT_PIN_CFG},    /* [2]  Set INT_ANYRD_2CLEAR          */
//    {0x01, MPU6500_INT_ENABLE},     /* [3]  Set RAW_RDY_EN                */
//    {0x00, MPU6500_PWR_MGMT_2},     /* [4]  Enable Acc & Gyro             */
//    {0x00, MPU6500_SMPLRT_DIV},     /* [5]  Sample Rate Divider           */
//    {0x00, MPU6500_GYRO_CONFIG},    /* [6]  default : +-250dps            */
//    {0x00, MPU6500_ACCEL_CONFIG},   /* [7]  default : +-2G                */
//    {0x00, MPU6500_CONFIG},         /* [8]  default : GyrLPS_250Hz        */
//    {0x00, MPU6500_ACCEL_CONFIG_2}, /* [9]  default : AccLPS_460Hz        */
//    {0x30, MPU6500_USER_CTRL},      /* [10] Set I2C_MST_EN, I2C_IF_DIS    */
//  };

  if (LPS22_DeviceCheck() != SUCCESS) {
    return ERROR;
  }

  /* Normal mode (low-noise mode) */
  treg = LPS22_ReadReg(LPS22HB_RES_CONF);
  treg &= 0x02;
  treg |= 0x00;
  LPS22_WriteReg(LPS22HB_RES_CONF, treg);
  delay_ms(5);

  /* Control register 1 */
  treg  = 0x00;
  treg |= 0x50; // Output data rate, 75 Hz
  treg |= 0x00; // Low-pass filter disabled
  treg |= 0x02; // Block data update, enable
  LPS22_WriteReg(LPS22HB_CTRL_REG1, treg);
  delay_ms(5);

  /* Control register 2 */
  treg = LPS22_ReadReg(LPS22HB_CTRL_REG2);
  treg &= 0xED;
  treg |= 0x10;
  LPS22_WriteReg(LPS22HB_RES_CONF, treg);
  delay_ms(5);

  return SUCCESS;
}

/**
 *  @brief  LPS22_DeviceCheck
 */
uint32_t LPS22_DeviceCheck( void )
{
  uint8_t deviceID;

  deviceID = LPS22_ReadReg(LPS22HB_WHO_AM_I);
#if 0
  printf("device id = 0x%02X\r\n", deviceID);
#endif
  if (deviceID != LPS22HB_DEVICE_ID) {
    return ERROR;
  }

  return SUCCESS;
}

/**
 *  @brief  LPS22_GetRawData
 */
uint32_t LPS22_GetRawData( int32_t *raw )
{
  uint8_t buff[3];
  uint32_t tmp = 0;

  LPS22_ReadRegs(LPS22HB_PRESS_OUT_XL, buff, 3);

  for (uint32_t i = 0; i < 3; i++) {
    tmp |= (((uint32_t)buff[i]) << (i << 3));
  }

  /* convert the 2's complement 24 bit to 2's complement 32 bit */
  if (tmp & 0x00800000) {
    tmp |= 0xFF000000;
  }

  raw[0] = (int32_t)tmp;

  LPS22_ReadRegs(LPS22HB_TEMP_OUT_L, buff, 2);
  tmp = (((uint16_t)buff[1]) << 8) + (uint16_t)buff[0];

  raw[1] = (int16_t)tmp;

  return SUCCESS;
}

/**
 *  @brief  LPS22_GetData
 */
uint32_t LPS22_GetData( float32_t *raw )
{
  int32_t buff[2] = {0};
  LPS22_GetRawData(buff);

  raw[0] = buff[0] * LPS22HB_SENS_HPA;  // hPa
  raw[1] = buff[1] * LPS22HB_SENS_DEGC; // degC

  return SUCCESS;
}

/**
 *  @brief  LPS22_GetAltitude
 */
float32_t LPS22_GetAltitude( float32_t pressure )
{
  float32_t altitude;

  // altitude above sea level (ASL)
  // (1.f - pow(*pressure / CONST_SEA_PRESSURE, CONST_PF)) * CONST_PF2
  // ((pow((1015.7 / *pressure), CONST_PF) - 1.0) * (25. + 273.15)) / 0.0065
  #define CONST_SEA_PRESSURE 102610.f
  #define CONST_PF 0.1902630958f //(1/5.25588f) Pressure factor
  #define CONST_PF2 44330.0f
  #define FIX_TEMP 25
  altitude = ((powf((1015.7f / pressure), CONST_PF) - 1.0f) * (FIX_TEMP + 273.15f)) / 0.0065f;

  return altitude;
}

/*************************************** END OF FILE ****************************************/
