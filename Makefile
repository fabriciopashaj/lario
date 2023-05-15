CC		 	= x86_64-w64-mingw32-gcc
CXX		 	= x86_64-w64-mingw32-g++
SRC 	 	= Main.cpp Object.cpp Platform.cpp Floor.cpp Turtle.cpp Game.cpp \
					Pipe.cpp ScoreBoard.cpp Mario.cpp
CFLAGS 	= -std=c++11 -I./SFML-2.5.1/include -O0
LDFLAGS	= -L./SFML-2.5.1/lib -L./SFML-2.5.1/bin \
					-lsfml-window -lsfml-graphics -lsfml-system -lsfml-main
EXEC		= lario.exe
OBJS		= $(SRC:%.cpp=build/%.o)

.PHONY: all clean

all: $(EXEC)

build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CFLAGS) -c $^ -o $@

$(EXEC): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)
	cp -f $@ -r /mnt/c/Users/fabricio/Desktop/lario/$(EXEC)

clean:
	@rm -f $(OBJS) $(EXEC) /mnt/c/Users/fabricio/Desktop/$(EXEC)
