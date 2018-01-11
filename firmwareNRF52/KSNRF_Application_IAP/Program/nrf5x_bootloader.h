/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_bootloader.h
 *  @author  KitSprout
 *  @date    10-Jan-2018
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __NRF5X_BOOTLOADER_H
#define __NRF5X_BOOTLOADER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_flash.h"

/* Exported types --------------------------------------------------------------------------*/
/* Exported constants ----------------------------------------------------------------------*/
#define BOOTLOADER_ADDR           (FLASH_PAGE_SIZE * 0)
#define BOOTLOADER_SIZE           ((uint32_t)0x4000)
#define APPLICATION_ADDR          (BOOTLOADER_ADDR + BOOTLOADER_SIZE)

/* Exported functions ----------------------------------------------------------------------*/
void      nrf_bootloader_app_start( uint32_t startAddress );
void      nrf_bootloader_set_receiver( uint32_t (*fptr)(uint8_t*, uint32_t) );
uint32_t  nrf_bootloader_download( uint8_t *binaryFile );
void      nrf_bootloader_upload( uint8_t *binaryFile, uint32_t binaryFileSize );

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
