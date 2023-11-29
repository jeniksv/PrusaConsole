CXX = g++
CFLAGS = -Wall -std=c++20
LIBS = -Lbuild/googletest/lib -lgtest -lgtest_main -lpthread -Lbuild/cpp-terminal/cpp-terminal -lcpp-terminal  -Lbuild/cpp-terminal/cpp-terminal/private -lcpp-terminal-private

TARGET = prusa-console
TEST_TARGET = test_runner
SRCDIR = src
TESTDIR = tests
INCDIR = include
BUILDDIR=build
BUILD_APP_DIR = build/app
BUILD_TEST_DIR = build/tests

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILD_APP_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)
INCLUDES = -I$(INCDIR) -I external/cpp-terminal

TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(BUILD_TEST_DIR)/%.o)
TEST_DEPS = $(TEST_OBJECTS:.o=.d)
TEST_INCLUDES = -I$(INCDIR) -Iextern/googletest/googletest/include -Iexternal/cpp-terminal

.PHONY: all clean test googletest

all: $(TARGET)

googletest:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/googletest
	cmake -B $(BUILDDIR)/googletest extern/googletest && make -C $(BUILDDIR)/googletest -j8

cpp-terminal:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/cpp-terminal
	cmake -B $(BUILDDIR)/cpp-terminal extern/cpp-terminal && make -C $(BUILDDIR)/cpp-terminal -j8



$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BUILD_APP_DIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILD_APP_DIR)
	$(CXX) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

test: $(TEST_TARGET) googletest cpp-terminal

$(TEST_TARGET): $(TEST_OBJECTS) $(filter-out $(BUILD_APP_DIR)/main.o, $(OBJECTS))
	$(CXX) $(CFLAGS) $(TEST_INCLUDES) $^ $(LIBS) -o $(TEST_TARGET)

$(BUILD_TEST_DIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(BUILD_TEST_DIR)
	$(CXX) $(CFLAGS) $(TEST_INCLUDES) -MMD -c $< -o $@

-include $(DEPS)
-include $(TEST_DEPS)

clean:
