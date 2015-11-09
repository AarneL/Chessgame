

all:
	g++ -c main.cpp ./GUI/game_screen.cpp ./GUI/menu_screen.cpp -I/Users/aarneliski/own2/lib/SFML-2.3.2-osx-clang-universal/include
	g++  main.o game_screen.o  menu_screen.o -o main.bin -L/Users/aarneliski/own2/lib/SFML-2.3.2-osx-clang-universal/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	export LD_LIBRARY_PATH=/Users/aarneliski/own2/lib/SFML-2.3.2-osx-clang-universal/lib && ./main.bin

clean:
	rm main.bin game_screen.o menu_screen.o main.o