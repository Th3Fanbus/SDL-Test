CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -pthread -Wall -Wpedantic -Wextra -std=c++11
LDFLAGS=-g -lOpenCL -lGL -lglfw -lGLEW -lSDL2 

SRCS=SDL.cpp Hex.cpp Point.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
OBHS=$(subst .cpp,.h.gch,$(SRCS))

all: SDL

SDL: $(OBJS)
	$(CXX) $(LDFLAGS) -o SDL $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBHS)
	$(RM) SDL

run:	SDL
	./SDL
