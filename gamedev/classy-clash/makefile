# Linux
# classy_clash: libraylib.a main.cpp
# 	clang++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o classy_clash
#
# Mac OS
# classy_clash: libraylib.a main.cpp
# 	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -std=c++11 libraylib.a main.cpp -o classy_clash
#
classy_clash: main.cpp
	clang++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o classy_clash

clean:
	rm *.o classy_clash
