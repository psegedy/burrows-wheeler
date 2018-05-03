CXX=g++
CXXFLAGS=-g -pedantic -Wall -Wextra -std=c++11
SOURCES=main.cpp main.h bwted.cpp bwted.h rle.cpp rle.h mtf.cpp mtf.h
EXECUTABLES=bwted

all:$(EXECUTABLES)

bwted: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(SOURCES_COMMON) -o $@

clean:
	rm -f $(EXECUTABLES) xseged00.zip

pack:
	zip xseged00.zip $(SOURCES) bwted.pdf Makefile
