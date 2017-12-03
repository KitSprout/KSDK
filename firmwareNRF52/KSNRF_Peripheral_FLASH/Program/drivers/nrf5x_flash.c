/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_flash.c
 *  @author  KitSprout
 *  @date    03-Dec-2017
 *  @brief   
 * 
 */
 
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_flash.h"

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
 *  @brief  FLASH_WriteDataU32
 */
void FLASH_WriteDataU32( const uint32_t writeAddr, const uint32_t *writeData, uint32_t lens )
{
  uint32_t count = 0;

  // write enable
  NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos);
  while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {}

  // write data
  do {
    *(__IO uint32_t*)(writeAddr + (count << 2)) = writeData[count];
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {}
  } while (++count < lens);

  // read only enable
  NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);
  while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {}
}

/**
 *  @brief  FLASH_ReadDataU32
 */
void FLASH_ReadDataU32( const uint32_t readAddr, uint32_t *readData, const uint32_t lens )
{
  uint32_t count = 0;

  do {
    readData[count] = (uint32_t)(*(__IO uint32_t*)(readAddr + (count << 2)));
  } while (++count < lens);
}

/**
 *  @brief  FLASH_ErasePage
 */
void FLASH_ErasePage( uint32_t erasePageAddr )
{
    // erase enable
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Een << NVMC_CONFIG_WEN_Pos);
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {}

    // erase page
    NRF_NVMC->ERASEPAGE = erasePageAddr;
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {}

    // read only enable
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {}
}

/*************************************** END OF FILE ****************************************/
