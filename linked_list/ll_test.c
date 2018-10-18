#include <stdio.h>

#include "linked_list.h"

int main(int argc, char **argv)
{
	node_t *root = NULL;
	int x = 5;
	push(&x, &root);
	printf("%d\n", *(int *)root->val);
	printf("%p\n", root->next);

	int y = 7;
	push(&y, &root);
	printf("%d\n", *(int *)root->val);
	printf("%p\n", root->next);

	printf("popped value: %d\n", *(int *)pop(&root));
	printf("%d\n", *(int *)root->val);
	printf("%p\n", root->next);

	free_list(root);

	return 0;
}
