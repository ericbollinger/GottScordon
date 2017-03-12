CC = g++
CXXFLAGS = -Wall -g
LDLIBS = -Wall -g
SRCDIR = src
BUILDDIR = build
TARGET = bin/gottscordon
SRCEXT = cc

SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

#CXXFLAGS += -L lib -lboost_thread -lboost_system -lboost_regex
#LDLIBS += -L lib -lboost_thread -lboost_system -lboost_regex
INC = -I include

#C++ 14 Libraries / C++11 XOR These
#CXXFLAGS += -std=c++14
#LDLIBS += -std=c++14
#CXXFLAGS += -std=c++11
#LDLIBS += -std=c++11

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

# Tests
# tester:
# 	$(CC) test/gridtest.cc src/mongo.cc $(CXXFLAGS) $(INC) -o bin/gridtests
#
clean :
	rm build/*
	rm bin/*
