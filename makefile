# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I./src
LDFLAGS = -lm

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/chess

# Default target
all: $(TARGET)

# Create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the target
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Clean build files
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run