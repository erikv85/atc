#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int capacity = 8;
	int *list = malloc(capacity * sizeof(int));
	int i;
	for (i = 0; i <= 4; i++)
		list[i] = i + 1;
	for (i = 5; i <= capacity; i++)
		list[i] = -1;
	int target = 2;
	int *dst = list + target;
	int *src = dst + 1;
	size_t size = capacity - 1 - target;
	// use memmove since dst, src overlap
	memmove(dst, src, size);
	int len = 5;
	list[len - 1] = -1;
	for (i = 0; i < capacity; i++)
		printf("%d ", list[i]);
	printf("\n");

	free(list);
	return 0;
}
