CXX=g++
LD=g++
CFLAGS=-ggdb -Wall -Wextra -std=c++11 -I./include
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
FONTBINTYPE=elf64-x86-64

EXEC=ttt
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: clean all run

all: clean fonts $(EXEC)

run: all
	./$(EXEC)

$(EXEC): $(OBJECTS)
	$(LD) $(OBJECTS) Unique.o GlacialIndifference.o Inconsolata.o $(LDFLAGS) -o $(EXEC)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

fonts:
	objcopy --input binary --output $(FONTBINTYPE) --binary-architecture i386:x86-64 Unique.ttf Unique.o
	objcopy --input binary --output $(FONTBINTYPE) --binary-architecture i386:x86-64 GlacialIndifference.otf GlacialIndifference.o
	objcopy --input binary --output $(FONTBINTYPE) --binary-architecture i386:x86-64 Inconsolata.ttf Inconsolata.o

clean:
	rm -rf $(EXEC) $(OBJECTS)
