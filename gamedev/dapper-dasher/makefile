# Linux
# dapper_dasher: dasher.cpp
# 	clang++ dasher.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o dapper_dasher
#
# Mac OS
# dapper_dasher: libraylib.a dasher.cpp
# 	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -std=c++11 libraylib.a dasher.cpp -o dapper_dasher
#
dapper_dasher: dasher.cpp
	clang++ dasher.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o dapper_dasher

clean:
	rm *.o dapper_dasher
