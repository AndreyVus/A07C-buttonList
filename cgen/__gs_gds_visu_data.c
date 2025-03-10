
/**-----------------------------------------------
 * __gs_gds_visu_data.c
 * This file is automatically generated, don't try to edit it
 * all modifications will be lost with exporting the project
 **-----------------------------------------------*/

#include <stdint.h>

typedef int32_t tObjNum;
typedef struct tagVisMaskColorTabEntry
{
  tObjNum  Number;  // Container or Mask number
  uint16_t BkColorNameIdx;
  uint16_t FrColorNameIdx;
  uint32_t Transparent;
}tVisMaskColorTabEntry;

const uint32_t _gs_ColorTableOffset = 512;
const uint32_t _gs_ContainerCnt = 2;
const uint32_t _gs_MaskCnt = 1;

const tVisMaskColorTabEntry _gs_visMaskColorTab[] =
{
  //  Co/Ma  BkColor  FrColor  Trans-
  // Number, NameIdx, NameIdx, parent
          0,   65535,   65535,     0,  // container: Container0
          1,   65535,   65535,     0,  // container: Container1
          0,   65535,   65535,     0   // mask: Maske0
};

