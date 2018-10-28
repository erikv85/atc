test_al: test_al.c arraylist.o
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) -c $^

run: test_al
	./$^

valrun: test_al
	valgrind ./$^

.PHONY: clean
clean:
	$(RM) *.o *.gch test_al
