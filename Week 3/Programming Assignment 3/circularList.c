#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this
	list->sentinel = (struct Link*)malloc(sizeof(struct Link));
	assert(list->sentinel != 0);
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this
	struct Link *newLink = (struct Link*)malloc(sizeof(struct Link));
	newLink->next = NULL;
	newLink->prev = NULL;
	newLink->value = value;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	struct Link *newLink = createLink(value);
	assert(list != 0);
	assert(link != 0);
	newLink->next = link->next;
	newLink->prev = link;

	// Assign pointers to links flanking newLink
	(newLink->next)->prev = newLink;
	(newLink->prev)->next = newLink;

	// Increment list size
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	printf("Deleting the following link: %g\n", link->value);
	link->prev->next = link->next;
	link->next->prev = link->prev;
	list->size--;
	free(link);
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this
	while (list->size > 0) {
		circularListRemoveFront(list);
	}
	free(list->sentinel);

	//while (!circularListIsEmpty(list)) {
	//	struct Link * temp = list->sentinel->next;
	//	removeLink(list, temp);
	//}

	//free(list->sentinel);
	//free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	//assert(!circularListIsEmpty(list));
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	if (list->size == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
	//struct Link *temp = malloc(sizeof(struct Link));
	//assert(list != 0);
	////assert(!circularListIsEmpty(list));
	//temp = list->sentinel->next;
	//while (temp != list->sentinel) {
	//	printf("%f", temp->value);
	//	temp = temp->next;
	//}
	//free(temp);
	int size = list->size;
	struct Link * itr = list->sentinel->next;
	printf("List front to back: ");

	while (size) {
		printf("%g, ", itr->value);
		//printf("\tValue:%lf, Address:%p, Address next:%p, Address before:%p, value next: %lf\n", itr->value, itr, itr->next, itr->prev, itr->next->value);
		itr = itr->next;
		size--;
	}
	printf("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this
	struct Link * itr = list->sentinel;

	// Traverse all size + 1 links (data links + sentinel)

	for (int i = 0; i < list->size + 1; i++) {
		// Save current node
		struct Link * temp = itr->next;

		// Set current node next to previous
		itr->next = itr->prev;

		// Set current node prev to next
		itr->prev = temp;

		// Traverse to *new* next node
		itr = itr->next;
	}
}
