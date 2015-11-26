

all:
	g++ -c main.cpp ./GUI/game_screen.cpp ./GUI/menu_screen.cpp -I/Users/aarneliski/own2/lib/SFML-2.3.2-osx-clang-universal/include
	g++  main.o game_screen.o  menu_screen.o -o main.bin -L/Users/aarneliski/own2/lib/SFML-2.3.2-osx-clang-universal/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	export LD_LIBRARY_PATH=/Users/aarneliski/own2/lib/SFML-2.3.2-osx-clang-universal/lib && ./main.bin


asd:
	g++ -std=c++11 -g -gstabs+ -Wall -pedantic -o Screentest.bin main.cpp \
	GUI/menu_screen.cpp GUI/game_screen.cpp GUI/options_screen.cpp GUI/new_game_screen.cpp \
	Game/Player/player.cpp Game/Player/human.cpp Game/Player/ai.cpp \
	Game/game.cpp Game/board.cpp Game/rules.cpp \
	Game/ai_algorithm.cpp \
	GUI/tinyfiledialogs.c \
	-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

clean:
	rm main.bin game_screen.o menu_screen.o main.o