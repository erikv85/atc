%: %.c
	$(CC) $^ -o $@

combine: combine.c server client
	$(CC) $@.c -o $@

test_broadcast: broadcaster listener1 listener2
	./broadcaster &
	./listener1 &
	./listener2 &

clean:
	$(RM) client server combine
