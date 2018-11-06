CC = gcc
CFLAGS = -Iarraylist -Igraphics
INCLUDES = -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib -lX11 -lm

VPATH=.:arraylist:graphics

binaries = a.out simple_atc aircraft_main sandbox

simple_atc: simple_atc.c graphics.o collision.o aircraft.o arraylist.o
	$(CC) $^ -o $@ ${INCLUDES} ${LDFLAGS} ${CFLAGS}

%.o: %.c %.h
	$(CC) -c $^

# mainly for aircraft_main
%: %.c
	$(CC) $^ -o $@

# example usage: make args="2" run
run: simple_atc
	./$^ $(args)

clean:
	rm -f *~ *.o *.gch $(binaries)
