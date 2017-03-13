CC = g++
CXXFLAGS = -Wall -g
LDLIBS = -Wall -g
SRCDIR = src
BUILDDIR = build
TARGET = bin/gottscordon
SRCEXT = cc

SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

INC = -I include

#Uncomment for threading
#CXXFLAGS += -pthread
#LDLIBS += -pthread

#Uncomment for Dev Optimization Compilation
#CXXFLAGS += -O3
#LDLIBS += -O3

all: $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $(LDFLAGS) $^ $(INC) $(LDLIBS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) 
		$(CC) -c $(CXXFLAGS) $(INC) $< -o $@

clean :
	rm build/*
	rm bin/*
