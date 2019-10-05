#include <SDL/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <portaudio.h>
#include "main.h"
#include "snes9x.h"
#include "soundux.h"
#include "memmap.h"
#include "apu.h"
#include "cheats.h"
#include "display.h"
#include "gfx.h"
#include "cpuexec.h"
#include "spc7110.h"
#include "srtc.h"
#include "sa1.h"
#include "scaler.h"

#include "menu.h"
#include "config.h"

uint8_t *keystate;
uint8_t exit_snes = 0;
extern uint32_t emulator_state;

#define CASE(realkey, key) \
	if (keystate[realkey]) \
		joypad |= key; \
	else \
		joypad &= ~key; \

uint32_t S9xReadJoypad(int32_t port)
{
	SDL_Event event;
	static const uint32_t snes_lut[] =
	{
      SNES_B_MASK,
      SNES_Y_MASK,
      SNES_SELECT_MASK,
      SNES_START_MASK,
      SNES_UP_MASK,
      SNES_DOWN_MASK,
      SNES_LEFT_MASK,
      SNES_RIGHT_MASK,
      SNES_A_MASK,
      SNES_X_MASK,
      SNES_TL_MASK,
      SNES_TR_MASK
	};

	int32_t i;
	uint32_t joypad = 0;
	
	keystate = SDL_GetKeyState(NULL);
	
	SDL_PollEvent(&event);

	CASE(SDLK_RETURN, SNES_START_MASK);
	CASE(SDLK_ESCAPE, SNES_SELECT_MASK);
	CASE(SDLK_LCTRL, SNES_A_MASK);
	CASE(SDLK_LALT, SNES_B_MASK);
	CASE(SDLK_LSHIFT, SNES_X_MASK);
	CASE(SDLK_SPACE, SNES_Y_MASK);
	CASE(SDLK_TAB, SNES_TL_MASK);
	CASE(SDLK_BACKSPACE, SNES_TR_MASK);
	CASE(SDLK_UP, SNES_UP_MASK);
	CASE(SDLK_LEFT, SNES_LEFT_MASK);
	CASE(SDLK_RIGHT, SNES_RIGHT_MASK);
	CASE(SDLK_DOWN, SNES_DOWN_MASK);
	
	if (keystate[SDLK_END])	emulator_state = 1;

   return joypad;
}
