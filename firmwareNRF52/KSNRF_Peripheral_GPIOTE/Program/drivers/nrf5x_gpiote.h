/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_gpiote.h
 *  @author  KitSprout
 *  @date    26-Nov-2017
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __NRF5x_GPIOE_H
#define __NRF5x_GPIOE_H

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes --------------------------------------------------------------------------------*/
#include "nrf.h"

/* Exported types --------------------------------------------------------------------------*/

typedef struct {
  NRF_GPIOTE_Type *Instance;

  uint8_t Line;
  // Line 0-3
  uint32_t Pin;
  // Pin 0-31
  uint32_t Mode;
  // GPIOTE_CONFIG_MODE_Disabled - Disabled.
  // GPIOTE_CONFIG_MODE_Event    - Channel configure in event mode.
  // GPIOTE_CONFIG_MODE_Task     - Channel configure in task mode.
  uint32_t Polarity;
  // NRF_GPIOTE_POLARITY_LOTOHI - Low to high.
  // NRF_GPIOTE_POLARITY_HITOLO - High to low.
  // NRF_GPIOTE_POLARITY_TOGGLE - Toggle.
  uint32_t OutInit;
  // NRF_GPIOTE_INITIAL_VALUE_LOW  - Initial low output when in task mode.
  // NRF_GPIOTE_INITIAL_VALUE_HIGH - Initial high output when in task mode.
  pFunc EventCallback;
  // GPIOTE EVENT CALLBACK
} GPIOTE_InitTypeDef;

/* Exported constants ----------------------------------------------------------------------*/
/* Exported macro --------------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------*/  
void GPIOTE_Init( GPIOTE_InitTypeDef *hgpiotx );
void GPIOTE_IntCmd( GPIOTE_InitTypeDef *hgpiotx, uint32_t state );

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
