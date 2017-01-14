#include "../copyright"

#include "snes9x.h"
#include "memmap.h"
#include "sdd1.h"
#include "display.h"

void S9xSetSDD1MemoryMap(uint32_t bank, uint32_t value)
{
   bank = 0xc00 + bank * 0x100;
   value = value * 1024 * 1024;

   int c;

   for (c = 0; c < 0x100; c += 16)
   {
      uint8_t* block = &Memory.ROM [value + (c << 12)];
      int i;

      for (i = c; i < c + 16; i++)
         Memory.Map [i + bank] = block;
   }
}

void S9xResetSDD1()
{
   memset(&Memory.FillRAM [0x4800], 0, 4);
   int i;
   for (i = 0; i < 4; i++)
   {
      Memory.FillRAM [0x4804 + i] = i;
      S9xSetSDD1MemoryMap(i, i);
   }
}

void S9xSDD1PostLoadState()
{
   int i;
   for (i = 0; i < 4; i++)
      S9xSetSDD1MemoryMap(i, Memory.FillRAM [0x4804 + i]);
}
