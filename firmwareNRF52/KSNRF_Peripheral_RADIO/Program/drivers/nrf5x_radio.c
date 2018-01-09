/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_radio.c
 *  @author  KitSprout
 *  @date    09-Jan-2018
 *  @brief   
 * 
 */
 
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_radio.h"

/** @addtogroup NRF5x_Driver
 *  @{
 */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
#define RADIOx    NRF_RADIO

/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
static uint8_t radio_packet[256 + 2] = {0};

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

/**
 *  @brief  RADIO_Init
 */
void RADIO_Init( RADIO_InitTypeDef *hradio )
{
  // tx power, radio frequence, transmission speed
  RADIOx->TXPOWER   = hradio->TxPower   << RADIO_TXPOWER_TXPOWER_Pos;
  RADIOx->FREQUENCY = hradio->Frequency << RADIO_FREQUENCY_FREQUENCY_Pos;
  RADIOx->MODE      = hradio->Mode      << RADIO_MODE_MODE_Pos;

  // crc check
  RADIOx->CRCCNF = (hradio->CRC << RADIO_CRCCNF_LEN_Pos);
  switch (hradio->CRC) {
    case RADIO_CRCCNF_LEN_One:
      RADIOx->CRCINIT = 0xFFUL;     // Initial Value
      RADIOx->CRCPOLY = 0x107UL;    // CRC poly: x^8 + x^2^x^1 + 1
      break;
    case RADIO_CRCCNF_LEN_Two:
      RADIOx->CRCINIT = 0xFFFFUL;   // Initial Value
      RADIOx->CRCPOLY = 0x11021UL;  // CRC poly: x^16 + x^12^x^5 + 1
      break;
    case RADIO_CRCCNF_LEN_Three:
      break;
  }

  // address prefix 0 - 7
  RADIOx->PREFIX0 = BYTE32(hradio->Prefix[7], hradio->Prefix[6], hradio->Prefix[5], hradio->Prefix[4]);
  RADIOx->PREFIX1 = BYTE32(hradio->Prefix[3], hradio->Prefix[2], hradio->Prefix[1], hradio->Prefix[0]);

  // base address 0 - 1
  RADIOx->BASE0 = hradio->BaseAddr[0];
  RADIOx->BASE1 = hradio->BaseAddr[1];

  // tx / rx address
  RADIOx->TXADDRESS   = hradio->TxAddr;
  RADIOx->RXADDRESSES = hradio->RxAddr;

  // packet config
  RADIOx->PCNF0 = (RADIO_PACKET_S1_FIELD_SIZE       << RADIO_PCNF0_S1LEN_Pos) |
                  (RADIO_PACKET_S0_FIELD_SIZE       << RADIO_PCNF0_S0LEN_Pos) |
                  (RADIO_PACKET_LENGTH_FIELD_SIZE   << RADIO_PCNF0_LFLEN_Pos);
  RADIOx->PCNF1 = (RADIO_PCNF1_WHITEEN_Disabled     << RADIO_PCNF1_WHITEEN_Pos) |
                  (RADIO_PCNF1_ENDIAN_Big           << RADIO_PCNF1_ENDIAN_Pos)  |
                  (RADIO_PACKET_BASE_ADDRESS_LENGTH << RADIO_PCNF1_BALEN_Pos)   |
                  (RADIO_PACKET_STATIC_LENGTH       << RADIO_PCNF1_STATLEN_Pos) |
                  (RADIO_PACKET_PAYLOAD_MAXSIZE     << RADIO_PCNF1_MAXLEN_Pos);

  // enable rss measure automatic
  NRF_RADIO->SHORTS |= RADIO_SHORTS_ADDRESS_RSSISTART_Msk;

  // set buffer
  RADIOx->PACKETPTR = (uint32_t)radio_packet;
}

void RADIO_Disable( void )
{
  RADIOx->SHORTS = RESET;
  RADIO_EVENTS_DISABLED(RADIOx) = RESET;
#ifdef NRF51
  RADIOx->TEST = RESET;
#endif
  RADIO_EVENTS_DISABLED(RADIOx) = SET;
  while (RADIO_EVENTS_DISABLED(RADIOx) == RESET) {;}
  RADIO_EVENTS_DISABLED(RADIOx) = RESET;
}

/**
 *  @brief  RADIO_SetPacket
 */
void RADIO_SetPacket( uint32_t *packet )
{
  RADIOx->PACKETPTR = (uint32_t)packet;
}

/**
 *  @brief  RADIO_RecvPacket
 */
uint32_t RADIO_RecvPacket( uint8_t *pdata, uint8_t *lens, int8_t *rssi )
{
  RADIO_EVENTS_READY(RADIOx) = RESET;
  RADIO_TASKS_RXEN(RADIOx) = SET;
  while (RADIO_EVENTS_READY(RADIOx) == RESET);

  RADIO_EVENTS_END(RADIOx) = RESET;
  RADIO_TASKS_START(RADIOx) = SET;
  while (RADIO_EVENTS_END(RADIOx) == RESET);
  if (RADIOx->CRCSTATUS == SET) {
    *rssi = -RADIOx->RSSISAMPLE;
    *lens = radio_packet[0];
    for (uint8_t i = 0; i < *lens; i++) {
      pdata[i] = radio_packet[i + 2];
    }
  }

  RADIO_EVENTS_DISABLED(RADIOx) = RESET;
  RADIO_TASKS_DISABLE(RADIOx) = SET;
  while (RADIO_EVENTS_DISABLED(RADIOx) == RESET);

  return KS_OK;
}

/**
 *  @brief  RADIO_SendPacket
 */
uint32_t RADIO_SendPacket( uint8_t *pdata, uint16_t lens )
{
  radio_packet[0] = lens;
  radio_packet[1] = 0xAB;
  while (lens) {
    lens--;
    radio_packet[lens + 2] = pdata[lens];
  }

  // send packet
  RADIO_EVENTS_READY(RADIOx) = RESET;
  RADIO_TASKS_TXEN(RADIOx) = SET;
  while (RADIO_EVENTS_READY(RADIOx) == RESET);

  RADIO_EVENTS_END(RADIOx) = RESET;
  RADIO_TASKS_START(RADIOx) = SET;
  while (RADIO_EVENTS_END(RADIOx) == RESET);

  RADIO_EVENTS_DISABLED(RADIOx) = RESET;
  RADIO_TASKS_DISABLE(RADIOx) = SET;
  while (RADIO_EVENTS_DISABLED(RADIOx) == RESET);

  return KS_OK;
}

/*************************************** END OF FILE ****************************************/
