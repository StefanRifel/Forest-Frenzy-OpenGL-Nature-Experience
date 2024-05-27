CC = g++

BIN = ./bin
SRC = ./src
LIB = ./lib

complib:
	$(CC) $(SRC)/*.cpp -c
	mv *.o $(BIN)/
	ar -crs $(BIN)/libsmath.a $(BIN)/*.o

clean:
	rm $(BIN)/*