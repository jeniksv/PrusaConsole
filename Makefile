CXX = g++
CFLAGS = -Wall -std=c++20

TARGET = prusa-console
TEST_TARGET = test_runner
SRCDIR = src
TESTDIR = tests
INCDIR = include
BUILDDIR = build/app
TEST_BUILDDIR = build/tests

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(TEST_BUILDDIR)/%.o)
DEPS = $(OBJECTS:.o=.d)
TEST_DEPS = $(TEST_OBJECTS:.o=.d)
INCLUDES = -I$(INCDIR)

.PHONY: clean test

$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p build
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(TEST_TARGET): $(filter-out $(BUILDDIR)/main.o, $(OBJECTS)) $(TEST_OBJECTS)
	$(CXX) $(CFLAGS) $(INCLUDES) $^ -o $@

$(TEST_BUILDDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p build
	@mkdir -p $(TEST_BUILDDIR)
	$(CXX) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

-include $(DEPS)
-include $(TEST_DEPS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET) $(TEST_BUILDDIR) $(TEST_TARGET)

