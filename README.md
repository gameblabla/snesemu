SnesEmu fork based on snes9x2005 libretro core by the Retroarch team.

The libretro team had switched the core entirely to C and made it less prone to crashes.
It made more sense to me to just reuse that work rather than trying to fix up PocketSNES,
which is now unmaintained.

==========================

snes9x2005 libretro core.

A Super Nintendo emulator core using the libretro API.

Based on:
* Snes9x 1.43, by the Snes9x team (with research by the ZSNES folks, anomie,
  zsKnight, etc.)
* NDSSFC 1.06, by the Supercard team (porting to the MIPS processor)
* BAGSFC, by BassAceGold (improving over NDSSFC)
* CATSFC, by ShadauxCat and Nebuleon (improving over BAGSFC)
