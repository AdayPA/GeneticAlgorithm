CXX ?= g++
CC ?= gcc

BUILD_DIR := build
TARGET := $(BUILD_DIR)/ag

CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -O2 -Ilib
CFLAGS ?= -std=c99 -Wall -Wextra -Wno-array-bounds -Wno-format -O2 -Ilib
LDFLAGS ?= -lm

CPP_SOURCES := src/ag.cpp src/chromosome.cpp src/individual.cpp src/population.cpp
C_SOURCES := src/tinyexpr.c
OBJECTS := $(CPP_SOURCES:src/%.cpp=$(BUILD_DIR)/%.o) $(C_SOURCES:src/%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(TARGET)
	$(TARGET) input/hojadecalculo.txt --generations 4

clean:
	rm -rf $(BUILD_DIR)
