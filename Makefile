SHELL = /bin/sh

CXX ::= g++
CXXFLAGS ::= -g -std=c++17

srcdir ::= ./src
objdir ::= ./obj
bindir ::= ./bin

src ::= $(wildcard $(srcdir)/*.cpp)
obj ::= $(src:$(srcdir)/%.cpp=$(objdir)/%.o)
bin ::= $(obj:$(objdir)/%.o=$(bindir)/%)

.DEFAULT_GOAL := all

.PHONY all:
all: clean mkdirs build

.PHONY build:
build: $(bin)

$(bindir)/%: $(objdir)/%.o
	$(CXX) $< -o $@

$(objdir)/%.o: $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY clean:
clean:
	rm -rf $(objdir) $(bindir)

.PHONY mkdirs:
mkdirs:
	mkdir -p $(objdir) $(bindir)
