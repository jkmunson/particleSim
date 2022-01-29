linker_flags := -lSDL2 -lSDL2_image -Isrc/ -pthread -lpthread
compiler_flags := -march=native -Wpedantic -Wall -Wextra -Wsuggest-attribute=const -std=c++2b -Ofast

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
	cp ./bin/particleSim ./particleSim

