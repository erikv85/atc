CC = gcc

CFLAGS = -I..
LDFLAGS = -lm

VPATH=.:..

al_test: al_test.c linked_list.o collision.o aircraft.o
	$(CC) $^ -o $@ ${LDFLAGS} ${CFLAGS}

ll_test: ll_test.c linked_list.o
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) -c $^ ${CFLAGS} ${LDFLAGS}

clean:
	rm -f *~ *.o ll_test al_test
