# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -I./include

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files and output binary
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/category.cpp  $(SRC_DIR)/product.cpp $(SRC_DIR)/utilities.cpp
OUTPUT = $(BUILD_DIR)/Stock_Digital

# OS detection
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    # Linux specific settings
else
    # Windows specific settings
    OUTPUT = $(BUILD_DIR)/Stok_Digital.exe
endif

# Default target
all: $(OUTPUT)

# Build target
$(OUTPUT): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean up
clean:
	rm -f $(OUTPUT)

.PHONY: all clean
