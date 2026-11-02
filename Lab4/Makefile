# Debug Flag Makefile
LDLIBS = -lm

CXX = aarch64-linux-gnu-g++
CXXFLAGS = -static -g

CC = aarch64-linux-gnu-gcc
CFLAGS = -static -g

SRCS = $(wildcard *.c)
BINS = $(SRCS:.c=)

CPPSRCS = $(wildcard *.cpp)
CPPBINS = $(CPPSRCS:.cpp=)

all: $(BINS)
all_all: all $(CPPBINS)

%: %.c
	$(CC) $(CFLAGS) $< $(LDLIBS) -o $@

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(BINS)
	rm -f $(CPPBINS)

.PHONY: all clean
