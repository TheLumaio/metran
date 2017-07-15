SRC = $(wildcard src/*.cpp) $(wildcard src/game/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))
CLFAGS = --std=c++11 -w -fpermissive
OUT = build/metran

LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx
LIBS = 
CC = g++

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBS) -o $(OUT)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
