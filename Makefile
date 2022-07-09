CC = g++ 
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/wordcounter.o
HDRS = $(INC)/wordcounter.hpp $(INC)/memlog.h

TARGET = email

all: $(TARGET)

$(TARGET): $(SRC)/email.cpp $(SRC)/main.cpp 
	$(CC) $(SRC)/email.cpp $(SRC)/main.cpp -I$(INC) -o $(TARGET)
