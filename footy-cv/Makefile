# Compiler Settings
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2
LDFLAGS = -lm

# Directories
SRC_DIR = src
BUILD_DIR = build
INC_DIR = include

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/test_engine

# Default rule to build everything
all: directories $(TARGET)

# Link the object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile .c files into .o (object) files in the build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	@mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all directories clean