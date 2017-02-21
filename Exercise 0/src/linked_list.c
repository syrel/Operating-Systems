/* gcc -Wall -O2 linked_list.c */
/* valgrind ./a.out */

#include <stdio.h>
#include <stdlib.h>

struct elem {
	int pos;
	struct elem *next;
};

static void panic(const char *serror)
{
	printf("%s", serror);
	exit(1);
}

/**
 * Allocates a dynamic memory and garantees to return a valid pointer
 * @param size
 * @return
 */
static void *xmalloc(size_t size)
{
	void *ptr;
	if (size == 0)
		panic("Size is 0!\n");
	ptr = malloc(size);
	if (!ptr)
		panic("No mem left!\n");
	return ptr;
}

static void xfree(void *ptr)
{
	if (ptr == NULL)
		panic("Got Null-Pointer!\n");
	free(ptr);
}

static struct elem *init_list(size_t len)
{
	struct elem* head = xmalloc(sizeof(struct elem));
    head->pos = 0;
    head->next = head;

    struct elem* previous = head;

    // we already created a head element in a linked list, start iteration from 1
    for (size_t index = 1; index < len; index++) {
        struct elem* next = xmalloc(sizeof(struct elem));
        next->next = head;
        next->pos = (previous->pos) + 1;

        previous->next = next;
        previous = next;
    }
    return head;
}

static void clean_list(struct elem *head, size_t len)
{
    // end of recursion
    if (len == 0) {
        return;
    }

    struct elem *current = head;
    clean_list(current->next, len - 1);
    current->next = NULL;
    xfree(current);
}

static void traverse_list(struct elem *head, int times)
{
    for (int iteration = 0; iteration < times; iteration++) {
        struct elem *current = head;

        // using do since we want to perform an iteration step at least on one element.
        do {
            printf("iteration: %u position: %u\n", iteration, current->pos);
            current = current->next;
        } while (current != head);
    }
}

int main(void)
{
	struct elem *head = NULL;
	size_t len = 10;

    head = init_list(len);
    traverse_list(head, 2);
    clean_list(head, len);

	return 0;
}

