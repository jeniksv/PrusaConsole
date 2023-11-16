CXX = g++
CFLAGS = -Wall -std=c++20
LIBS = -lgtest -lgtest_main -lpthread

TARGET = prusa-console
TEST_TARGET = test_runner
SRCDIR = src
TESTDIR = tests
INCDIR = include
BUILDDIR = build/app
TEST_BUILDDIR = build/tests

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
DEPS = $(OBJECTS:.o=.d)
INCLUDES = -I $(INCDIR)

TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(TEST_BUILDDIR)/%.o)
TEST_DEPS = $(TEST_OBJECTS:.o=.d)
TEST_INCLUDES = -I$(INCDIR) -I/usr/src/googletest/googletest/include/

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(filter-out $(BUILDDIR)/main.o, $(OBJECTS))
	$(CXX) $(CFLAGS) $(TEST_INCLUDES) $^ $(LIBS) -o $(TEST_TARGET)

$(TEST_BUILDDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(TEST_BUILDDIR)
	$(CXX) $(CFLAGS) $(TEST_INCLUDES) -MMD -c $< -o $@

-include $(DEPS)
-include $(TEST_DEPS)

clean:
	@rm -rf $(BUILDDIR) $(TEST_BUILDDIR) $(TARGET) $(TEST_TARGET) build

