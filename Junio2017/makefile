BIN = bin
INC = include
OBJ = obj
SRC = src

CXX = g++
CXXFLAGS = -c -Wall -Iinclude -g

$(BIN)/main: $(OBJ)/main.o $(OBJ)/redciudades.o
	$(CXX) $(OBJ)/redciudades.o $(OBJ)/main.o -o $(BIN)/main

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/redciudades.h
	$(CXX) $(CXXFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/redciudades.o: $(SRC)/redciudades.cpp $(INC)/redciudades.h
	$(CXX) $(CXXFLAGS) $(SRC)/redciudades.cpp -o $(OBJ)/redciudades.o

clean:
	rm -f $(OBJ)/*.o

mrproper: clean
	rm -f $(BIN)/main
