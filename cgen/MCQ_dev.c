/*****************************************************************************
 * File:  MCQ_dev.c
 * 
 * This file is automatically generated, don't try to edit it
 * all modifications will be lost with next build
 * 
 * Description:  description
 * 
 ****************************************************************************/

/* include files ************************************************************/
#include <stdint.h>
#include <UserCEvents.h>  /* API-Function declarations                      */
#include <UserCAPI.h>
#include <gsCanTgmTypes.h>

/* macro definitions ********************************************************/
/* Note: This must be in line with definitions in "McqConfigFrm" */
#define SEND_KEY_VIA_CAN0_P 0
#define SEND_KEY_VIA_CAN0_R 1
#define SEND_KEY_VIA_CAN1_P 2
#define SEND_KEY_VIA_CAN1_R 3
#define SEND_KEY_VIA_CAN2_P 4
#define SEND_KEY_VIA_CAN2_R 5

/* local prototypes *********************************************************/
static void _gs_send_via_can(uint32_t channel, uint32_t id, uint8_t ext, uint8_t keyCode, uint8_t state);

/* global variables *********************************************************/
uint32_t _gs_CAN0_TxId = 220;
uint32_t _gs_CAN1_TxId = 220;
uint32_t _gs_CAN2_TxId = 220;
uint8_t _gs_CAN0_TxExt = 0;
uint8_t _gs_CAN1_TxExt = 0;
uint8_t _gs_CAN2_TxExt = 0;

/* local constants  *********************************************************/
const uint16_t keyConfTable1[] =
{
       0, /* dummy */
  0x003F, /* key code   1 (F1) */
  0x003F, /* key code   2 (F2) */
  0x003F, /* key code   3 (F3) */
};

const uint16_t keyConfTable2[] =
{
       0, /* dummy */
       0, /* unused */
       0, /* unused */
       0, /* unused */
  0x003F, /* key code 103 (PRIGHTDOWN) */
  0x003F, /* key code 104 (PRIGHTUP) */
  0x003F, /* key code 105 (PRIGHTPRESS) */
};

/*****************************************************************************
  Key telegram init part
 ****************************************************************************/
void _gs_event_keytelegram_preinit(void)
{
  uint32_t cfg1;
  uint32_t cfg2;
  _gs_CAN0_TxId = 220;
  _gs_CAN1_TxId = 220;
  _gs_CAN2_TxId = 220;
  _gs_CAN0_TxExt = 0;
  _gs_CAN1_TxExt = 0;
  _gs_CAN2_TxExt = 0;
  if (   (0 == ConfigGetInt("DeviceConfiguration.CANInterfaces.[0].TxId", &cfg1))
      && (0 == ConfigGetInt("DeviceConfiguration.CANInterfaces.[0].TxExt", &cfg2)) )
  {
    _gs_CAN0_TxId = cfg1;
    _gs_CAN0_TxExt = (uint8_t)cfg2;
  }
  if (   (0 == ConfigGetInt("DeviceConfiguration.CANInterfaces.[1].TxId", &cfg1))
      && (0 == ConfigGetInt("DeviceConfiguration.CANInterfaces.[1].TxExt", &cfg2)) )
  {
    _gs_CAN1_TxId = cfg1;
    _gs_CAN1_TxExt = (uint8_t)cfg2;
  }
  if (   (0 == ConfigGetInt("DeviceConfiguration.CANInterfaces.[2].TxId", &cfg1))
      && (0 == ConfigGetInt("DeviceConfiguration.CANInterfaces.[2].TxExt", &cfg2)) )
  {
    _gs_CAN2_TxId = cfg1;
    _gs_CAN2_TxExt = (uint8_t)cfg2;
  }
}

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
/*****************************************************************************
  Key telegram event part
 ****************************************************************************/
int32_t _gs_event_keytelegram_event(uint32_t evtc, tUserCEvt * evtv)
{
  for (uint32_t i = 0; i < evtc; i++)
  {
    if (CEVT_KEY == evtv[i].Type)
    {
      /* It's a key event ... */
      uint8_t kc = evtv[i].Content.mKey.KeyCode;
      uint16_t keyTelegram = 0;
      int kcValid = 0;
      if ((0 < kc) && (kc < (uint8_t)(sizeof(keyConfTable1) / sizeof(keyConfTable1[0]))))
      {
        keyTelegram = keyConfTable1[kc];
        kcValid = 1;
      }
      else if ((0 < kc-99) && (kc-99 < (uint8_t)(sizeof(keyConfTable2) / sizeof(keyConfTable2[0]))))
      {
        keyTelegram = keyConfTable2[kc-99];
        kcValid = 1;
      }
      if (1 == kcValid)
      {
        if (1 == evtv[i].Content.mKey.State)
        {
          /* Key pressed */
          if (1 == ((keyTelegram >> SEND_KEY_VIA_CAN0_P) & 0x0001))
          {
            /* send key pressed via CAN0 */
            _gs_send_via_can(0, _gs_CAN0_TxId, _gs_CAN0_TxExt, kc, 0x00);
          }
          if (1 == ((keyTelegram >> SEND_KEY_VIA_CAN1_P) & 0x0001))
          {
            /* send key pressed via CAN1 */
            _gs_send_via_can(1, _gs_CAN1_TxId, _gs_CAN1_TxExt, kc, 0x00);
          }
          if (1 == ((keyTelegram >> SEND_KEY_VIA_CAN2_P) & 0x0001))
          {
            /* send key pressed via CAN2 */
            _gs_send_via_can(2, _gs_CAN2_TxId, _gs_CAN2_TxExt, kc, 0x00);
          }
        }
        else
        {
          /* Key released */
          if (1 == ((keyTelegram >> SEND_KEY_VIA_CAN0_R) & 0x0001))
          {
            /* send key released via CAN0 */
            _gs_send_via_can(0, _gs_CAN0_TxId, _gs_CAN0_TxExt, kc, 0x80);
          }
          if (1 == ((keyTelegram >> SEND_KEY_VIA_CAN1_R) & 0x0001))
          {
            /* send key released via CAN1 */
            _gs_send_via_can(1, _gs_CAN1_TxId, _gs_CAN1_TxExt, kc, 0x80);
          }
          if (1 == ((keyTelegram >> SEND_KEY_VIA_CAN2_R) & 0x0001))
          {
            /* send key released via CAN2 */
            _gs_send_via_can(2, _gs_CAN2_TxId, _gs_CAN2_TxExt, kc, 0x80);
          }
        }
      }
    }
  }
  return 0;
}
#pragma GCC diagnostic warning "-Wdeprecated-declarations"

/****************************************************************************
  Send via CAN part
 ****************************************************************************/
static void _gs_send_via_can(uint32_t channel, uint32_t id, uint8_t ext, uint8_t keyCode, uint8_t state)
{
  tCanMessage CanMsg;
  
  memset(&CanMsg, 0, sizeof(tCanMessage));
  CanMsg.id = id;
  CanMsg.data.u8[0] = CAN_TGM_KEY_DATA;
  CanMsg.data.u8[2] = (state | keyCode);
  CanMsg.ext = ext;
  CanMsg.channel = channel;
  CanMsg.len = 3;
  
  /* Send it... */
  CANSendMsg(&CanMsg);
}

