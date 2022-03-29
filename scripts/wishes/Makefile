CC = g++

CFLAGS  = -std=c++14 -g -Wall -O2

all: roll.x freqs.x

%.x: %.cpp
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.x
