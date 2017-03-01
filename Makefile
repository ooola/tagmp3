INCLUDE = -I ./id3v2lib/include -I ./parg
LFLAGS = -L ./id3v2lib/build/src -L ./parg/build
LIBS = -l parg -l id3v2
CC=/usr/bin/cc
CFLAGS= -Wall
SRC=main.c
BIN=tag

.phony: all

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(SRC) $(INCLUDE) $(CFLAGS) $(LFLAGS) $(LIBS) -o $@
