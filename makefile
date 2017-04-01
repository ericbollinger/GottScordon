# Note: This makefile was provided by Robert Rico for my first C++ project last year, and I have been 
# using it ever since in my projects. This is the only similarity between our CSC 180 projects, all other
# code was written completely independently. --Eric Bollinger

CC = g++
CXXFLAGS = -Wall -g
LDLIBS = -Wall -g
SRCDIR = src
BUILDDIR = build
TARGET = bin/xeno
SRCEXT = cc

SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

INC = -I include

all: $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $(LDFLAGS) $^ $(INC) $(LDLIBS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) 
		$(CC) -c $(CXXFLAGS) $(INC) $< -o $@

clean :
	rm build/*
	rm bin/*
