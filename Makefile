linker_flags := -lSDL2 -lSDL2_image -Isrc/ -pthread -lpthread
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
