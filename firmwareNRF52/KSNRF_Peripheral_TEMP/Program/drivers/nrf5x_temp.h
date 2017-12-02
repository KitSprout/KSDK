/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_temp.h
 *  @author  KitSprout
 *  @date    01-Dec-2017
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __NRF5x_TEMP_H
#define __NRF5x_TEMP_H

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"

/* Exported types --------------------------------------------------------------------------*/
/* Exported constants ----------------------------------------------------------------------*/
/* Exported macro --------------------------------------------------------------------------*/
#define TEMP_TASKS_START()      (NRF_TEMP->TASKS_START = SET)  // Start temperature measurement
#define TEMP_TASKS_STOP()       (NRF_TEMP->TASKS_STOP = SET)   // Stop temperature measurement\

#define TEMP_EVENTS_DATARDY()   NRF_TEMP->EVENTS_DATARDY        // Temperature measurement complete, data ready

/* Exported functions ----------------------------------------------------------------------*/  
void      TEMP_Init( void );
float32_t TEMP_GetTemperature( void );

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
