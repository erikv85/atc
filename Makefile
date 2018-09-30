CC = gcc
CFLAGS = -Wall
INCLUDES = -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib -lX11 -lm
GSRC = graphics/

binaries = simple_atc basic_graphics

simple_atc: simple_atc.c graphics.o ball.o
	$(CC) $^ -I$(GSRC) -o $@ $(INCLUDES) $(LDFLAGS) $(CFLAGS)

graphics.o: $(GSRC)graphics.c $(GSRC)graphics.h
	$(CC) -c $^ $(INCLUDES)

ball.o: ball.c ball.h
	$(CC) -c $^

collision.o: collision.c collision.h
	$(CC) -c $^

basic_graphics: basic_graphics.c graphics.o collision.o
	$(CC) $^ -I${GSRC} -o $@ ${INCLUDES} ${LDFLAGS} ${CFLAGS}

clean:
	rm -f *~ *.o *.gch $(binaries)
