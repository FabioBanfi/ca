NAME = ca
CC = g++
CFLAGS = -std=c++11 -g -Wall -O3 -lSDL2 -lboost_program_options
SRC = src
BIN = bin
TEST = test
OBJ = obj
OBJS = main.o AnimatedCA1D.o AnimatedCA2D.o FirstOrderCA1D.o FirstOrderCA2D.o

all: ca

ca: $(OBJS)
	$(CC) $(CFLAGS) $(OBJ)/*.o -o $(BIN)/$(NAME)

main.o: $(TEST)/main.cpp
	$(CC) -c $(CFLAGS) $(TEST)/main.cpp -o $(OBJ)/main.o

AnimatedCA1D.o: $(SRC)/AnimatedCA1D.cpp
	$(CC) -c $(CFLAGS) $(SRC)/AnimatedCA1D.cpp -o $(OBJ)/AnimatedCA1D.o

AnimatedCA2D.o: $(SRC)/AnimatedCA2D.cpp
	$(CC) -c $(CFLAGS) $(SRC)/AnimatedCA2D.cpp -o $(OBJ)/AnimatedCA2D.o

FirstOrderCA1D.o: $(SRC)/FirstOrderCA1D.cpp
	$(CC) -c $(CFLAGS) $(SRC)/FirstOrderCA1D.cpp -o $(OBJ)/FirstOrderCA1D.o

FirstOrderCA2D.o: $(SRC)/FirstOrderCA2D.cpp
	$(CC) -c $(CFLAGS) $(SRC)/FirstOrderCA2D.cpp -o $(OBJ)/FirstOrderCA2D.o

clean:
	rm -rf $(OBJ)/*.o $(BIN)/$(NAME)
