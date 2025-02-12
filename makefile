# Directories
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Targets
TARGET = $(BIN_DIR)/chess
TEST_TARGET = $(BIN_DIR)/test_chess

# Compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -I$(SRC_DIR) -I$(TEST_DIR)

# Default target
all: $(TARGET) $(TEST_TARGET)

# Create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile test files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link main program (excluding test_main.o)
$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(filter-out $(OBJ_DIR)/test_main.o, $(OBJ)) -o $@ $(LDFLAGS)

# Link test program
$(TEST_TARGET): $(OBJ) $(TEST_OBJ) | $(BIN_DIR)
	$(CC) $(filter-out $(OBJ_DIR)/main.o, $(OBJ)) $(TEST_OBJ) -o $@ $(LDFLAGS)

# Clean
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run main program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean test run