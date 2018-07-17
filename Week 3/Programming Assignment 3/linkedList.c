#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;					// Data contained by this link.		
	struct Link* next;			// Pointer to the next link.
	struct Link* prev;			// Pointer to the previous link.
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;					// Number of elements in the list.
	struct Link* frontSentinel;	// Initialize routine sets to zero/NULL.
	struct Link* backSentinel;	// Initialize routine sets to zero/NULL.
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXME: you must write this
	list->frontSentinel = (struct Link *) malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);
	list->backSentinel = (struct Link *) malloc(sizeof(struct Link));
	assert(list->backSentinel);
	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	list->size = 0;
}
/********************************************************************
*						addLinkBefore									
* Parameters: struct LinkedList * list, struct Link *link, TYPE value(int)
* - struct LinkedList *list: Pointer to the linked list deque.			
* - struct Link *link: Pointer to a single link in the list.		
* - TYPE value: An integer to be assigned to the newly created link.	
* Description: _addLink places a new link before the given location
* of struct dlink *lnk (second parameter) and increments the size
* of the deque by one.											
********************************************************************/
/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(link != 0);
	struct Link * newLink = (struct Link *) malloc(sizeof(struct Link));	// Allocate memory for the new link.
	assert(newLink != 0);						// Make sure that the new link was created.
	newLink->value = value;						// Assign the passed value of e to the value of the new link.
	newLink->prev = link->prev;					// Update the new link's prev point to match the passed location's prev pointer.
	newLink->next = link;						// Update the new link's next pointer to the passed location, since it now proceeds it.
	link->prev->next = newLink;					// Update the next pointer of the link that once proceeded lnk, but now proceeds newLink.
	link->prev = newLink;						// Update lnk's prev point to newLink, since newLink now proceeds lnk.
	list->size++;								// Increment the size of the list by 1, since a new link has been added.
}

/********************************************************************
*							removeLink								
* Parameters: struct LinkedList *list, struct Link *link				
* - struct LinkedList *list: Pointer to the linked list deque.			
* - struct Link *link: Pointer to a single link in the list, which	
* will be removed from the deque.									
* Description: When called, this function will remove the target	
* link from the deque (the second parameter) and decrement the size	
* of the deque by 1.												
********************************************************************/
/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(link != 0);
	link->next->prev = link->prev;				// Update the previous pointer of the previous link.
	link->prev->next = link->next;				// Update the next pointer of the next link.
	free(link);									// Free the memory of the link being removed.
	list->size--;								// Decrement the size of the list by 1, since a link has been removed.
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	return(list->frontSentinel->next->value);
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	return(list->backSentinel->prev->value);
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	return list->size == 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	struct Link *current = list->frontSentinel->next;
	assert(current != 0);
	while (current != list->backSentinel) {
		printf("%d\n", current->value);
		current = current->next;
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	struct Link * current = list->frontSentinel->next;
	while (current != list->backSentinel) {
		if (current->value == value) {
			return 1;
		}
		current = current->next;
	}
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	struct Link *current = list->frontSentinel->next;
	while (current != list->backSentinel) {
		if (current->value == value) {
			current->prev->next = current->next;
			current->next->prev = current->prev;
			free(current);
			list->size--;
			break;
		}
		current = current->next;
	}
}
