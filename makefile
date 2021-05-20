CC=g++ -O3

OBJECTS= main.cpp Ponto.cpp Instancia.cpp

LDLIBS=-lglut -lGLU -lGL -lstdc++

all: clean program

program:
	@$(CC) $(OBJECTS) -o program $(LDLIBS) 
clean:
	rm -rf *.o program 