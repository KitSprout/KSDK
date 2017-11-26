/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_gpiote.c
 *  @author  KitSprout
 *  @date    26-Nov-2017
 *  @brief   
 * 
 */
 
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_gpiote.h"

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
 *  @brief  GPIOTE_Init
 */
void GPIOTE_Init( GPIOTE_InitTypeDef *hgpiotx )
{
  hgpiotx->Instance->CONFIG[hgpiotx->Line] = (hgpiotx->Pin      << GPIOTE_CONFIG_PSEL_Pos) | 
                                             (hgpiotx->Mode     << GPIOTE_CONFIG_MODE_Pos) | 
                                             (hgpiotx->Polarity << GPIOTE_CONFIG_POLARITY_Pos) | 
                                             (hgpiotx->OutInit  << GPIOTE_CONFIG_OUTINIT_Pos);
}

/**
 *  @brief  GPIOTE_IntCmd
 */
void GPIOTE_IntCmd( GPIOTE_InitTypeDef *hgpiotx, uint32_t state )
{
  if (state == ENABLE) {
    NRF_GPIOTE->INTENSET = 1UL << hgpiotx->Line;
  }
  else {
    NRF_GPIOTE->INTENCLR = 1UL << hgpiotx->Line;
  }
}

/*************************************** END OF FILE ****************************************/
