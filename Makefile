PRGNAME     = PocketSNES

# define regarding OS, which compiler to use
CC          = gcc

# change compilation / linking flag options
CFLAGS		= -DLSB_FIRST -I. -Ilibretro-common/include -Isrc -DINLINE="inline" -DRIGHTSHIFT_IS_SAR
CFLAGS		+= -Isource -I./shell/emu -I./shell/scalers -I./shell/emu -I./shell/audio -I./shell/menu -I./shell/video/sdl -I./shell/input -Ishell/headers

CFLAGS		+= -O2 -DNDEBUG -DLAGFIX -DGIT_VERSION=\"" c9b3980"\" -fno-builtin -fno-exceptions -ffunction-sections -std=gnu99
CFLAGS		+=  -Wall -Wextra -pedantic -Wno-implicit-function-declaration -Wno-implicit-fallthrough -Wno-sign-compare -Wno-unused-variable -Wno-unused-function -Wno-uninitialized -Wno-strict-aliasing -Wno-overflow -fno-strict-overflow

#-fprofile-generate=/mnt/int_sd/profile
LDFLAGS     = -lSDL -lasound -lm

# Files to be compiled
SRCDIR    = ./source ./shell/emu ./shell/scalers ./shell/audio/alsa ./shell/menu ./shell/video/sdl ./shell/input/sdl ./shell/other
VPATH     = $(SRCDIR)
SRC_C   = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
SRC_CP   = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.cpp))
OBJ_C   = $(notdir $(patsubst %.c, %.o, $(SRC_C)))
OBJ_CP   = $(notdir $(patsubst %.cpp, %.o, $(SRC_CP)))
OBJS     = $(OBJ_C) $(OBJ_CP)

# Rules to make executable
$(PRGNAME): $(OBJS)  
	$(CC) $(CFLAGS) -o $(PRGNAME) $^ $(LDFLAGS)

$(OBJ_C) : %.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PRGNAME)$(EXESUFFIX) *.o
