CXX = g++
CFLAGS = -Wall -std=c++20

TARGET = prusa-console
SRCDIR = src
INCDIR = include
BUILDDIR = build

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
DEPS = $(OBJECTS:.o=.d)
INCLUDES = -I$(INCDIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

-include $(DEPS)

.PHONY: clean

clean:
	rm -rf $(BUILDDIR) $(TARGET)

