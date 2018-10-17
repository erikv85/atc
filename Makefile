CC = gcc
CFLAGS = -Wall
INCLUDES = -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib -lX11 -lm
GSRC = graphics/

binaries = a.out simple_atc aircraft_main

simple_atc: simple_atc.c graphics.o collision.o aircraft.o
	$(CC) $^ -I${GSRC} -o $@ ${INCLUDES} ${LDFLAGS} ${CFLAGS}

graphics.o: $(GSRC)graphics.c $(GSRC)graphics.h
	$(CC) -c $^ $(INCLUDES)

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
