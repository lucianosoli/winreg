CC = gcc
CFLAGS = -Wall -g
LDFLAGS =

SOURCES = registry.h main.c
OBJECTS = $(SOURCES:.c=.o)

EXE = main.exe

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm $(OBJECTS) $(EXE)
