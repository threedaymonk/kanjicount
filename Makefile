CC=gcc 
CFLAGS=-Wall -O3 -std=c99

ALL=count-codepoints

all: $(ALL)

count-codepoints: count-codepoints.c

.PHONY: clean

clean:
	rm -f $(ALL)
