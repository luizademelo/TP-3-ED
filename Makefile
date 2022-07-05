# cc and flags
CC = g++
FLAGS = -g -Wall -c -I$(INC)
#CXXFLAGS = -std=c++11 -O3 -Wall

# folders
INC = ./include/
BIN = ./bin/
OBJ = ./obj/
SRC = ./src/
HDRS = $(INC)/email.hpp
# all sources, objs, and header files
TARGET = email

all: $(OBJ)/email.o $(OBJ)/main.o
	$(CC) -g -o $(BIN)/$(TARGET) $(OBJ)/email.o $(OBJ)/main.o -lm 

$(OBJ)/main.o: 
	$(CC) $(FLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/email.o: $(SRC)/email.cpp $(HDRS)
	$(CC) $(FLAGS) -o $(OBJ)/email.o $(SRC)/email.cpp

clean:
	rm -rf $(OBJ)* $(BIN)*