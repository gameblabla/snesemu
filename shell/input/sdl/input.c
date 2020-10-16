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

	CASE(option.config_buttons[0][10], SNES_START_MASK);
	CASE(option.config_buttons[0][11], SNES_SELECT_MASK);
	CASE(option.config_buttons[0][4], SNES_A_MASK);
	CASE(option.config_buttons[0][5], SNES_B_MASK);
	CASE(option.config_buttons[0][6], SNES_X_MASK);
	CASE(option.config_buttons[0][7], SNES_Y_MASK);
	CASE(option.config_buttons[0][8], SNES_TL_MASK);
	CASE(option.config_buttons[0][9], SNES_TR_MASK);
	CASE(option.config_buttons[0][0], SNES_UP_MASK);
	CASE(option.config_buttons[0][1], SNES_RIGHT_MASK);
	CASE(option.config_buttons[0][2], SNES_DOWN_MASK);
	CASE(option.config_buttons[0][3], SNES_LEFT_MASK);

	if (keystate[option.config_buttons[0][12]]) emulator_state = 1;

	return joypad;
}
