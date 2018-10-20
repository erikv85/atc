CC = gcc

INCLUDES = -I..
LDFLAGS = -lm

al_test: al_test.c linked_list.c ../collision.o ../aircraft.o
	$(CC) $^ -o $@ ${INCLUDES} ${LDFLFAGS}

ll_test: ll_test.c linked_list.c
	$(CC) $^ -o $@

clean:
	rm -f *~ *.o ll_test al_test
