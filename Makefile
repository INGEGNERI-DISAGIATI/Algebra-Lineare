# Compiler e flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Directories
SRC_DIR = src
INC_DIR = include
LIB_DIR = lib
OBJ_DIR = obj
BIN_DIR = bin

# Files libreria
LIB_SRC = $(SRC_DIR)/algebra.c
LIB_OBJ = $(OBJ_DIR)/algebra.o
LIB = $(LIB_DIR)/libalgebra.a

# Files programma principale
MAIN = $(BIN_DIR)/mainProgram
MAIN_SRC = mainProgram.c

# Target principale
all: directories $(LIB) $(MAIN)

# Crea le directory necessarie
directories:
    mkdir -p $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)

# Compila la libreria
$(LIB_OBJ): $(LIB_SRC)
    $(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Crea la libreria statica
$(LIB): $(LIB_OBJ)
    ar rcs $@ $^

# Compila il programma principale
$(MAIN): $(MAIN_SRC) $(LIB)
    $(CC) $(CFLAGS) -I$(INC_DIR) $^ -o $@

# Pulizia
clean:
    rm -rf $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)

.PHONY: all clean directories