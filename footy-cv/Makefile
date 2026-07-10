# Compilers
CC = gcc
CXX = g++

# Flags
CFLAGS = -Wall -Wextra -Iinclude -O2
# Use pkg-config to automatically find OpenCV headers
CXXFLAGS = -Wall -Wextra -Iinclude -O2 $(shell pkg-config --cflags opencv2)
# Use pkg-config to link the OpenCV libraries
LDFLAGS = -lm $(shell pkg-config --libs opencv2)

# Directories
SRC_DIR = src
BUILD_DIR = build

# Files
C_SRCS = $(wildcard $(SRC_DIR)/*.c)
CXX_SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SRCS)) \
       $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CXX_SRCS))

TARGET = $(BUILD_DIR)/test_engine

all: directories $(TARGET)

# Final Link (Must use g++ for linking when C++ objects are involved)
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

directories:
	@mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all directories clean