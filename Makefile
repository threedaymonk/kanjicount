CC=gcc 
CFLAGS=-Wall -g -std=c99

ALL=count-codepoints

all: $(ALL)

count-codepoints: count-codepoints.c

.PHONY: clean

clean:
	rm -f $(ALL)
