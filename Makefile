CXX=g++
LD=g++
CFLAGS=-ggdb -Wall -Wextra -std=c++1z -I./include
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

EXEC=ttt
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: clean

all: clean $(EXEC)

run: all
	./$(EXEC)

$(EXEC): $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o $(EXEC)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@ 

clean:
	rm -rf $(EXEC) $(OBJECTS)