DIR=out
all: $(DIR)/main

$(DIR)/main: $(DIR)/main.o
	gcc $(DIR)/main.o -o $(DIR)/main

$(DIR)/main.o: main.c
	gcc -g -c main.c -o $(DIR)/main.o
    
