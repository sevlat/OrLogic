#ifndef BsMemory_h_already_included__10_04_2013__608C3C0
#define BsMemory_h_already_included__10_04_2013__608C3C0
//
// SeVlaT, 10.04.2013
//

#include "BsTypes.h"

#include "ByteBuffer.h"

typedef TBbAddr<3, BoBe, TBsMemDate> TBbAdrMemDate;
typedef TBbAddr<3, BoBe, TBsMemTime> TBbAdrMemTime;


struct TBsMemoryMask {
  TBbAdr1B      bbaMode;
  TBbAdr2BeW    bbaModel;
  
  TBbAdr3BeDw   bbaFirmware;

  TBbAddr4Dw    bbaBackupPtr;
  TBbAdr1B      bbaOverflow;
  TBbAdr1B      bbaMemSizeKib;
  
  TBbAdrMemDate bbaBuildDate;
  TBbAdrMemDate bbaBatDate;
  TBbAdrMemDate bbaWakeupDate;
  TBbAdrMemTime bbaWakeupTime;
  TBbAdrMemTime bbaSleepTime;
  
  TBsMemoryMask()
   : bbaMode(c_BsAdr_MODE),
     bbaModel(c_BsAdr_MODEL_ID),
     bbaFirmware(c_BsAdr_FIRMWARE),
     bbaBackupPtr(c_BsAdr_BACKUP_PTR),
     bbaOverflow(c_BsAdr_MEM_OVERFLOW),
     bbaMemSizeKib(c_BsAdr_MEM_SIZE),
     bbaBuildDate(c_BsAdr_BUILD_DATE),
     bbaBatDate(c_BsAdr_BAT_DATE),
     bbaWakeupDate(c_BsAdr_WAKEUP_DATE),
     bbaWakeupTime(c_BsAdr_WAKEUP_TIME),
     bbaSleepTime(c_BsAdr_SLEEP_TIME) {}
};

struct TBsMemoryMaskNew: public TBsMemoryMask {
  TBbAddr4BeDw bbaSerNum;

  TBsMemoryMaskNew()
   : bbaSerNum(c_BsAdr_SERIAL_NO) {}
};

struct TBsMemoryMaskOld: public TBsMemoryMask {
  TBbAdr2BeW bbaSerNum;
  TBbAdr2BeW bbaCpuId;

  TBsMemoryMaskOld()
   : bbaSerNum(c_BsAdr_OLD_SERIAL),
     bbaCpuId(c_BsAdr_OLD_CPU_ID) {}
};

typedef TBiasedByteBuffer TBsMemory;

class TBsSysMemory {
 public:
  TBsSysMemory(const IByteBuffer &buf)
   : m_buf(buf) {}
  
 public:

 private:
  const IByteBuffer &m_buf;
};

/*
    O_OLD_SERIAL  = '\x00' # 2 bytes - only up to BSx6, numbers < 65.536
    O_OLD_CPU_ID  = '\x02' # 2 bytes - only up to BSx6, numbers < 65.536
    O_SERIAL_NO   = '\x00' # 4 bytes - only after BSx7, numbers > 70.000
                           #   (if byte 0x00 > 0, better use OLD offsets)
    O_FIRMWARE    = '\x05' # 3 bytes
    O_BUILD_DATE  = '\x08' # 3 bytes - YYMMDD
    O_MODEL_ID    = '\x0B' # 2 bytes:
                           #   8003: BSF3 (serial numbers > 1.000)
                           #   8004: BSF4 (serial numbers > 10.000)
                           #   8084: BSM4-RS232
                           #   8086: BSM6-RS232 / BSM6-USB
                           #   8146: BSF6 (serial numbers > 30.000)
                           #   8115: BSF5 (serial numbers > 50.000)
                           #   8117 / 8118: BSF7 / BSF8 (serial no. 70.000...70.521, 72.002...72.009)
                           #   8187 / 8188: BS7-SI-Master / BS8-SI-Master
                           #   8197: BSF7 (serial numbers > 71.000, apart from 72.002...72.009)
                           #   8198: BSF8 (serial numbers > 80.000)
                           #   9197 / 9198: BSM7-RS232, BSM7-USB / BSM8-USB, BSM8-SRR
                           #   9199: unknown
                           #   9597: BS7-S
                           #   B197 / B198: BS7-P / BS8-P
                           #   B897: BS7-GSM
    O_MEM_SIZE    = '\x0D' # 1 byte - in KB
    O_BAT_DATE    = '\x15' # 3 bytes - YYMMDD
    O_BAT_CAP     = '\x19' # 2 bytes - battery capacity in mAh (as multiples of 14.0625?!)
    O_BACKUP_PTR  = '\x1C' # 4 bytes - at positions 1C,1D,21,22
    O_SI6_CB      = '\x33' # 1 byte - bitfield defining which SI Card 6 blocks to read:
                           #   \x00=\xC1=read block0,6,7; \x08=\xFF=read all 8 blocks
    O_MEM_OVERFLOW= '\x3D' # 1 byte - memory overflow if != 0x00
    O_PROGRAM     = '\x70' # 1 byte - station program: xx0xxxxxb competition, xx1xxxxxb training
    O_MODE        = '\x71' # 1 byte - see SI station modes below
    O_STATION_CODE= '\x72' # 1 byte
    O_PROTO       = '\x74' # 1 byte - protocol configuration, bit mask value:
                           #   xxxxxxx1b extended protocol
                           #   xxxxxx1xb auto send out
                           #   xxxxx1xxb handshake (only valid for card readout)
                           #   xxx1xxxxb access with password only
                           #   1xxxxxxxb read out SI-card after punch (only for punch modes;
                           #             depends on bit 2: auto send out or handshake)
    O_WAKEUP_DATE = '\x75' # 3 bytes - YYMMDD
    O_WAKEUP_TIME = '\x78' # 3 bytes - 1 byte day (see below), 2 bytes seconds after midnight/midday
    O_SLEEP_TIME  = '\x7B' # 3 bytes - 1 byte day (see below), 2 bytes seconds after midnight/midday
                           #   xxxxxxx0b - seconds relative to midnight/midday: 0 = am, 1 = pm
                           #   xxxx000xb - day of week: 000 = Sunday, 110 = Saturday
                           #   xx00xxxxb - week counter 0..3, relative to programming date

*/

#endif
