# Makefile for Snake Game with raylib

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -O2
INCLUDE_RAYLIB := $(shell pkg-config --cflags-only-I raylib) 
LDFLAGS := $(shell pkg-config --libs --cflags-only-other raylib)

# Source and build directories
SRC_DIR := src
BUILD_DIR := build

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
TARGET := snake

# Default target
all: $(BUILD_DIR) $(TARGET)

# Rule to create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< $(INCLUDE_RAYLIB) -o $@

# Rule to link executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Clean rule
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
