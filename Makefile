linker_flags := -lSDL2 -lSDL2_image -Isrc/
compiler_flags := -march=native -Wpedantic -Wall -Wextra -Wsuggest-attribute=const -std=c++17 -O2

all: doxygen build

clean:
	@-rm bin/particleSim
	@-rm docs/* -r
	@-rm asm/* -r
doxygen:
#TODO get doxygen setup
assembly:
	g++ src/*.cpp -S $(linker_flags) $(compiler_flags)
	mv *.s asm/
#FIXME: Can gcc be told to put the.s files there firectly?
valgrind:
#TODO: Get Valgrind set up
build:
	g++ src/*.cpp -o bin/particleSim $(linker_flags) $(compiler_flags)

