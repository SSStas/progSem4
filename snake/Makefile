#compilation options
CXX = g++
CFLAGS = -Wall -std=c++17 -O

SOURCES = $(wildcard src/*.cc)
OBJECTS = $(SOURCES:.cc=.o)
EXECUTABLE = snake


all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(notdir $(OBJECTS)) -o $@


%.o: %.cc
	$(CXX) $(CFLAGS) -fPIC -c $<


clean:
	rm -f $(notdir $(OBJECTS)) $(EXECUTABLE)


.PHONY: all lib clean
