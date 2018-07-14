#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define TYPE int

void _dequeSetCapacity(struct deque *d, int newCap) {
	int i;

	/* Create a new underlying array*/
	TYPE *newData = (TYPE*)malloc(sizeof(TYPE)*newCap);
	assert(newData != 0);

	/* copy elements to it */
	int j = d->beg;
	for (i = 0; i < d->size; i++)
	{
		newData[i] = d->data[j];
		j = j + 1;
		if (j >= d->capacity)
			j = 0;
	}

	/* Delete the oldunderlying array*/
	free(d->data);
	/* update capacity and size and data*/
	d->data = newData;
	d->capacity = newCap;
	d->beg = 0;
}

void dequeFree(struct deque *d) {
	free(d->data); d->size = 0; d->capacity = 0;
}
struct deque {
	TYPE * data;
	int capacity;
	int size;
	int beg;
};

void dequeInit(struct deque *d, int initCapacity) {
	d->size = d->beg = 0;
	d->capacity = initCapacity; assert(initCapacity > 0);
	d->data = (TYPE *)malloc(initCapacity * sizeof(TYPE));
	assert(d->data != 0);
}

int dequeSize(struct deque *d) {
	return d->size;
}

void dequeAddFront(struct deque *d, TYPE newValue) {
	if (d->size >= d->capacity) _dequeSetCapacity(d, 2 * d->capacity);













}

void dequeAddBack(struct deque *d, TYPE newValue) {
	if (d->size >= d->capacity) _dequeSetcapacity(d, 2 * d->capacity);












}

/********************************************************************
*							dequeFront								*
* Parameters: struct deque *d										*
* - struct deque *d: Pointer to the linked list deque.				*
* Description: This function returns the value of the first link in	*
* the deque.														*
********************************************************************/
TYPE dequeFront(struct deque *d) {
	assert(d->size);											// Check to see if the deque is empty.
	return d->data[d->beg];
}

/********************************************************************
*							dequeBack								*
* Parameter: struct deque *d										*
* - struct deque *d: Pointer to the linked list deque.				*
* Description: This function returns the value of the last link in	*
* the deque.														*
********************************************************************/
TYPE dequeBack(struct deque *d) {
	assert(d->size);											// Check to see if the deque is empty.
	if (d->beg + d->size > d->capacity) {						// If beginning + size > capacity, the deque has been wrapped, so:
		return d->data[d->beg + (d->size - 1) - d->capacity];	// The last element is found at beginning + ((size - 1) - capacity).
	}
	else {
		return d->data[d->beg + d->size - 1];
	}
}

/********************************************************************
*						dequeRemoveFront							*
* Parameter: struct deque *d										*
* - struct deque *d: Pointer to the linked list deque.				*
* Description: This function removes the first element of the deque.*
********************************************************************/
void dequeRemoveFront(struct deque *d) {
	if (d->beg >= d->capacity - 1) {							// Case 1: If the beginning index >= the capacity of the deque:
		d->beg = 0;												// We need to wrap the deque, so we set the beginning to index[0].
	}
	else {														// Case 2: In all other cases (default case):
		d->beg = d->beg++;										// We don't need to wrap, so the new beginning is simply = beg + 1 ;
	}
	d->size--;													// In either case, we decrement the size.
}

void dequeRemoveBack(struct deque *d) {












}


int main() {
	
	return 0;
}