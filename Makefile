TARGET = bin/ExploitGen.bin
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))

INCLUDES = -Iinclude
CXXFLAGS = -Wall -Wextra -pedantic-errors -Weffc++ -Wconversion -Wsign-conversion -std=c++17

run: clean default
	./$(TARGET)

default: $(TARGET)

clean:
	rm -f obj/*.o
	rm -f bin/*

$(TARGET): $(OBJ)
	g++ $(CXXFLAGS) -o $@ $^ $(INCLUDES)

obj/%.o : src/%.cpp
	g++ $(CXXFLAGS) -c $< -o $@ $(INCLUDES)
