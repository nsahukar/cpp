# Linux
# axe_game: axe_game.cpp
# 	clang++ axe_game.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o axe_game
#
# Mac OS
# axe_game: libraylib.a axe_game.cpp
# 	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -std=c++11 libraylib.a axe_game.cpp -o axe_game
#
axe_game: axe_game.cpp
	clang++ axe_game.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o axe_game

clean:
	rm *.o axe_game
