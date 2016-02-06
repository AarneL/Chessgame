optimized:
	g++ -std=c++11 -Wall -pedantic -O3 -o Chessgame.bin main.cpp \
	GUI/menu_screen.cpp GUI/game_screen.cpp GUI/new_game_screen.cpp \
	Game/Player/player.cpp Game/Player/human.cpp Game/Player/ai.cpp \
	Game/board.cpp Game/rules.cpp Game/ai_algorithm.cpp \
	GUI/object.cpp GUI/button.cpp GUI/square.cpp GUI/text.cpp GUI/chess_piece.cpp \
	GUI/tinyfiledialogs.c \
	-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lpthread


debug:
	g++ -std=c++11 -gstabs+ -Wall -pedantic -o Chessgame.bin main.cpp \
	GUI/menu_screen.cpp GUI/game_screen.cpp GUI/new_game_screen.cpp \
	Game/Player/player.cpp Game/Player/human.cpp Game/Player/ai.cpp \
	Game/board.cpp Game/rules.cpp Game/ai_algorithm.cpp \
	GUI/object.cpp GUI/button.cpp GUI/square.cpp GUI/text.cpp GUI/chess_piece.cpp \
	GUI/tinyfiledialogs.c \
	-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lpthread

autotesting:
	g++ -std=c++11 -Wall -pedantic -O3 -o autotest.bin -pthread autotest/automatic.cpp \
	autotest/game.cpp \
	Game/Player/player.cpp Game/Player/human.cpp Game/Player/ai.cpp \
	Game/board.cpp Game/rules.cpp Game/ai_algorithm.cpp \
	-lpthread

autotestingdebug:
	g++ -std=c++11 -gstabs+ -Wall -pedantic -O0 -o autotest.bin autotest/automatic.cpp \
	autotest/game.cpp \
	Game/Player/player.cpp Game/Player/human.cpp Game/Player/ai.cpp \
	Game/board.cpp Game/rules.cpp Game/ai_algorithm.cpp 
	-lpthread


clean:
	rm Chessgame.bin
