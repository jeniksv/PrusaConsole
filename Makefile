CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin

EXECUTABLE = $(BIN_DIR)/app
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_EXECUTABLES = $(patsubst $(TEST_DIR)/%.cpp,$(BIN_DIR)/%,$(TEST_SOURCES))

all: $(EXECUTABLE) tests

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
    @mkdir -p $(@D)
    $(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
    @mkdir -p $(BIN_DIR)
    $(CXX) $(CXXFLAGS) $^ -o $@

tests: $(TEST_EXECUTABLES)

$(BIN_DIR)/%: $(TEST_DIR)/%.cpp $(filter-out $(BUILD_DIR)/main.o,$(OBJECTS))
    @mkdir -p $(BIN_DIR)
    $(CXX) $(CXXFLAGS) $^ -o $@

clean:
    @rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean

