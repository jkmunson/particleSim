#TODO: Only recompile specific object files, among other make nicities I don't know how to do yet.

linker_flags := -lSDL2main -lSDL2 -lSDL2_image -Isrc/ -pthread -lpthread
compiler_flags := -march=native -Wpedantic -Wall -Wextra -Wsuggest-attribute=const -std=c++2b

all: doxygen build

clean:
	@-rm bin/particleSim
	@-rm docs/* -r
	@-rm asm/* -r
	@-rm particleSim
doxygen:
#TODO get doxygen setup
assembly:
	g++ src/*.cpp -S $(linker_flags) $(compiler_flags) -Os
	mv *.s asm/
#FIXME: Can gcc be told to put the.s files there directly?
valgrind:
	g++ src/*.cpp -o bin/particleSim $(linker_flags) $(compiler_flags) -Og
	valgrind --leak-check=full --num-callers=50 --suppressions=valgrind-suppressions ./bin/particleSim > valgrind.txt
	@rm valgrind.txt
	@echo "There should be 319,159 bytes in use at exit\n"
build:
	g++ src/*.cpp -o bin/particleSim $(linker_flags) $(compiler_flags) -Os
test:
	g++ src/*.cpp -o bin/particleSim $(linker_flags) $(compiler_flags) -O0
	cp ./bin/particleSim ./particleSim

#FIXME: is there a good way to standardize cross-compiling for windows? ~/win-cross-dev has the SDL2 dev library manually placed there on my machine. Winows isn't really a priority at this time, so "works" is fine...
win:
	x86_64-w64-mingw32-g++ src/*.cpp -o particleSim.exe -lmingw32 $(linker_flags) -std=c++20 -mwindows -Os -I/home/jkmunson/win-cross-dev/SDL2/include -L/home/jkmunson/win-cross-dev/SDL2/lib/ 
