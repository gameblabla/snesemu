#ifndef VIDEO_BLIT_H
#define VIDEO_BLIT_H

#include <SDL/SDL.h>

#define HOST_WIDTH_RESOLUTION 320
#define HOST_HEIGHT_RESOLUTION 240

#define INTERNAL_SNES_WIDTH_NTSC 256
#define INTERNAL_SNES_HEIGHT_NTSC 224

extern SDL_Surface *screen, *backbuffer;

extern uint32_t width_of_surface;
extern uint32_t* Draw_to_Virtual_Screen;

void Init_Video();
void Set_Video_Menu();
void Set_Video_InGame();
void Video_Close();
void Update_Video_Menu();
void Update_Video_Ingame();

#endif
