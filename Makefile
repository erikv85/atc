CC = gcc
CFLAGS = -Wall
INCLUDES = -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib -lX11 -lm
GSRC = graphics/

binaries = simple_atc

simple_atc: simple_atc.c graphics.o collision.o
	$(CC) $^ -I${GSRC} -o $@ ${INCLUDES} ${LDFLAGS} ${CFLAGS}

graphics.o: $(GSRC)graphics.c $(GSRC)graphics.h
	$(CC) -c $^ $(INCLUDES)

collision.o: collision.c collision.h
	$(CC) -c $^

# example usage: make args="2" run
run: atc_app
	./$^ $(args)

atc_app: atc_app.c radar.o aircraft.o
	$(CC) $^ -o $@

clean:
	rm -f *~ *.o *.gch $(binaries) a.out
