#include <SDL/SDL.h>
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

static uint32_t width_snes = 256;

const char* S9xGetFilename(const char* in)
{
   static char filename [PATH_MAX + 1];
   char drive [_MAX_DRIVE + 1];
   char dir [_MAX_DIR + 1];
   char fname [_MAX_FNAME + 1];
   char ext [_MAX_EXT + 1];
   _splitpath(Memory.ROMFilename, drive, dir, fname, ext);
   _makepath(filename, drive, dir, fname, in);
   return filename;
}

void S9xMessage(int a, int b, const char* msg)
{
   //printf("%s\n", msg);
}

const char* S9xGetDirectory(uint32_t dirtype) { return NULL; }

void S9xDeinitDisplay(void)
{
   if (GFX.Screen_buffer)
      free(GFX.Screen_buffer);
      
   if (GFX.SubScreen_buffer)
      free(GFX.SubScreen_buffer);
      
   if (GFX.ZBuffer_buffer)
      free(GFX.ZBuffer_buffer);
   if (GFX.SubZBuffer_buffer)
      free(GFX.SubZBuffer_buffer);

   GFX.Screen = NULL;
   GFX.Screen_buffer = NULL;
   GFX.SubScreen = NULL;
   GFX.SubScreen_buffer = NULL;
   GFX.ZBuffer = NULL;
   GFX.ZBuffer_buffer = NULL;
   GFX.SubZBuffer = NULL;
   GFX.SubZBuffer_buffer = NULL;
}

void S9xInitDisplay(void)
{
   int32_t h = IMAGE_HEIGHT;
   
   width_snes = IMAGE_WIDTH;
   
   GFX.Pitch = IMAGE_WIDTH;
   GFX.Screen_buffer = (uint8_t *) malloc(GFX.Pitch * h);
   GFX.SubScreen_buffer = (uint8_t *) malloc(GFX.Pitch * h);
   GFX.ZBuffer_buffer = (uint8_t *) malloc((GFX.Pitch >> 1) * h );
   GFX.SubZBuffer_buffer = (uint8_t *) malloc((GFX.Pitch >> 1) * h);

   GFX.Screen = GFX.Screen_buffer;
   GFX.SubScreen = GFX.SubScreen_buffer;
   GFX.ZBuffer = GFX.ZBuffer_buffer;
   GFX.SubZBuffer = GFX.SubZBuffer_buffer;

   GFX.Delta = (GFX.SubScreen - GFX.Screen) >> 1;
}

void _splitpath (const char *path, char *drive, char *dir, char *fname, char *ext)
{
    char *slash = strrchr ((char *) path, SLASH_CHAR);
    char *dot   = strrchr ((char *) path, '.');

    *drive = '\0';

    if (dot && slash && dot < slash)
    {
        dot = 0;
    }

    if (!slash)
    {
        *dir = '\0';
        strcpy (fname, path);

        if (dot)
        {
            fname[dot - path] = '\0';
            strcpy (ext, dot + 1);
        }
        else
        {
            *ext = '\0';
        }
    }
    else
    {
        strcpy (dir, path);
        dir[slash - path] = '\0';
        strcpy (fname, slash + 1);

        if (dot)
        {
            fname[(dot - slash) - 1] = '\0';
            strcpy (ext, dot + 1);
        }
        else
        {
            *ext = '\0';
        }
    }

    return;
}

void _makepath (char *path, const char *drive, const char *dir, const char *fname,const char *ext)
{
    if (dir && *dir)
    {
        strcpy (path, dir);
        strcat (path, "/");
    }
    else
        *path = '\0';

    strcat (path, fname);

    if (ext && *ext)
    {
        strcat (path, ".");
        strcat (path, ext);
    }

    return;
}


bool S9xReadMousePosition(int32_t which1, int32_t* x, int32_t* y, uint32_t* buttons)
{
   (void) which1;
   (void) x;
   (void) y;
   (void) buttons;
   return false;
}

bool S9xReadSuperScopePosition(int32_t* x, int32_t* y, uint32_t* buttons)
{
   (void) x;
   (void) y;
   (void) buttons;
   return true;
}

bool JustifierOffscreen(void)
{
   return false;
}

void JustifierButtons(uint32_t* justifiers)
{
   (void) justifiers;
}
