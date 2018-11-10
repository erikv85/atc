%: %.c
	$(CC) $^ -o $@

combine: combine.c server client
	$(CC) $@.c -o $@

clean:
	$(RM) client server combine
