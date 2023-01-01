# To use `Makefile` in Microsoft Windows, we use `mingw32-make`bundled with
# mingw itself in the bin folder and added the folder into the environment
# variables... 
#
# Made a batch file with the name `make.bat` containing of `mingw32-make` 
# command, which lets me use the keyword `make` in the cmd.exe/
# windows terminal instead of the longer `mingw32-make`.
#
# Since $(CC) do not work in Microsoft Windows, we did change CC variable to
# gcc.
CC = gcc

CFLAGS =-Wall -Wextra -Werror -std=c17 -pedantic -ggdb -Isrc/include \
		-Isrc/include/SDL2
# We have used `-std=c17` since it is a bug fixer version of `-std=c11` &
# `-std=c14`.
#
# "pkg-config --cflags --print-errors sdl2" //does not work in Microsoft 
# Windows

# The package config thing did not work in Windows even though I installed the
# pkg-config with no success in windows whatsoever... No results also for the
# commands `pkg-config --libs` and `pkg-config --cflags` shows no result.
#
# So what we do is get sdl-devel from http://www.libsdl.org/ and store it in
# the mingw installation folder and
# use `gcc` flag for include `-I{path/to/with/SDL2/folder}` and for linking
# file `-l{nameOfPackage}` will do.

LIBS =-lmingw32 -Lsrc/lib -lSDL2main -lSDL2 -lm
# "pkg-config --libs --print-errors sdl2" //does not work in Microsoft Windows 
# either
#
# NEVER EVER make the tag for libs `-L{nameOfLib}` with capital L.
# ALWAYS do this with small "l" like this `-l{nameOfLib}`
#
# "-L" the capital L flag is used to write the path(s) to search for to find
# libraries while "-l" the small l flag is used to write the name of the
# library to include in the final compiled file.
#
# MAKE SURE TO USE `-L` TAG BEFORE USING `-l` TAG TO MAKE SURE YOU HAVE LISTED
# ALL THE LIBRARIES TO USE THEM BEFOREHAND, ALTHOUGH YOU CAN DO IT JUST BEFORE
# USING THE `-l` ON WHICH IT DEPENDS (LIKE DONE HERE).
te: main.c
	$(CC) main.c -o build/te $(CFLAGS) $(LIBS)
