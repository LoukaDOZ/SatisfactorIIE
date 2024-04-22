.DEFAULT_GOAL := all

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

BIN_DIR=bin
HEADERS_DIR=headers
OBJ_DIR=obj
SRC_DIR=src
OBJ_FILES=$(OBJ_DIR)/coordonne.o $(OBJ_DIR)/cout.o $(OBJ_DIR)/ligneDeProduction.o $(OBJ_DIR)/machine.o $(OBJ_DIR)/carte.o $ $(OBJ_DIR)/interface.o $(OBJ_DIR)/persoCarte.o $(OBJ_DIR)/personnel.o $(OBJ_DIR)/structure.o $(OBJ_DIR)/main.o $(OBJ_DIR)/serveur.o $(OBJ_DIR)/client.o

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/satisfactoriie $^

carte.c: $(OBJ_DIR)/carte.o
coordonne.c: $(OBJ_DIR)/coordonne.o
cout.c: $(OBJ_DIR)/cout.o
interface.c: $(OBJ_DIR)/interface.o
lignedeproduction.c: $(OBJ_DIR)/ligneDeProduction.o
machine.c: $(OBJ_DIR)/machine.o
main.c: $(OBJ_DIR)/main.o
persoCarte.c: $(OBJ_DIR)/persoCarte.o
personnel.c: $(OBJ_DIR)/personnel.o
structure.c: $(OBJ_DIR)/structure.o
client.c: $(OBJ_DIR)/client.o
serveur.c: $(OBJ_DIR)/serveur.o

$(OBJ_DIR)/carte.o: $(SRC_DIR)/carte.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/coordonne.o: $(SRC_DIR)/coordonne.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/cout.o: $(SRC_DIR)/cout.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/interface.o: $(SRC_DIR)/interface.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/ligneDeProduction.o: $(SRC_DIR)/ligneDeProduction.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/machine.o: $(SRC_DIR)/machine.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/persoCarte.o: $(SRC_DIR)/persoCarte.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/personnel.o: $(SRC_DIR)/personnel.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/structure.o: $(SRC_DIR)/structure.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/client.o: $(SRC_DIR)/client.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/serveur.o: $(SRC_DIR)/serveur.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

run:
	./bin/satisfactoriie

clean:
	rm -f obj/*.o bin/satisfactoriie
