/*
 * This is the file in which you'll write the functions required to 
implement
 * a stack using two queues.  Make sure to add your name and 
@oregonstate.edu
 * email address below:
 *
 * Name: Tristan Santiago
 * Email: santiatr@oregonstate.edu
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef TYPE
#define TYPE int
#endif

/**************************************************
 All of the initial Queue functions
 ***************************************************/
struct link {				// Single link.
	TYPE value;				// Data contained by this link.
	struct link * next;		// Pointer to the next line.
};

struct listQueue {
	struct link *firstLink;	// Initialize routine sets to zero/NULL.
	struct link *lastLink;	// Initialize routine sets to zero/NULL.
	int size;				// Size of the queue.
};

/*
* This function takes a queue and allocates the memory. It then
* creates a sentinel and assigns the first link and last link
* to the sentinel.
*/
void listQueueInit(struct listQueue *q) {
	// FIXME: you must write this
	struct link *lnk = (struct link *) malloc(sizeof(struct link));
	assert(lnk != 0);							// lnk is the sentinel/header.
	lnk->next = 0;								// lnk is pointing to the next link == 0.
	q->firstLink = q->lastLink = lnk;			// At the start, because the queue is empty firstLink == lastLink.
}

/*
 * This function creates a new queue. Parts of the create include 
allocating
 * the memory, initializing all of the values and returning a pointer to 
the newly
 * created queue.
 */
struct listQueue * listQueueCreate()
{
     //FIXME: you must write this
	struct listQueue *newQueue = malloc(sizeof(struct listQueue));
	assert(newQueue);
	listQueueInit(newQueue);
	return newQueue;
}

/*
* This function returns a 1 or 0 based on the statement looking at
* the first link. If the next value is null it is empty, and will return 1
*/
int listQueueIsEmpty(struct listQueue *q) {
	//FIXME: you must write this
	return q->firstLink == q->lastLink;		// If list is empty, the first and last link will point to the same NULL value.
}

/*
 * This function adds a new link and value to the back of the queue. It 
takes
 * a list and a type variable, allocates the memory and adjusts the proper 
links
 * to make the connection. No return value.
 */
void listQueueAddBack(struct listQueue *q, TYPE e) {
	
	// FIXME: you must write this
	struct link *newLink = (struct link *) malloc(sizeof(struct link)); // Allocate memory for the new link.
	assert(newLink != 0);						// Make sure the new link was created.
	newLink->value = e;							// Assign passed value to the new link.
	newLink->next = 0;							// Set the new link's pointer to NULL, making it the new last link in the list.
	q->lastLink->next = newLink;				// Update the lastLink pointer so that it points to the next element after new link.
	q->lastLink = newLink;						// Finally, make the new link the last link in the list.
}

/*
 * This function takes a list argument and removes the link at the front.
 */
void listQueueRemoveFront(struct listQueue *q) {
// FIXME: you must write this
	struct link *tempLink = q->firstLink->next;	// Copy the value stored in the first link to a temporary link.
	//assert(!linkedListStackIsEmpty(q));		// Check to see whether or not the list is empty.
	if (q->firstLink->next->next == 0) {		// If the list is empty: 
		q->lastLink = q->firstLink;				// Set the lastLink to be equal to the firstLink.
	}											// Else:
	q->firstLink->next = tempLink->next;		// Change the pointer to the next element.
	free(tempLink);								// And free the memory of the deleted link.
}

/*
 * Function returns the value at the front of the list.
 */
TYPE listQueueFront(struct listQueue *q) {
	// FIXME: you must write this
	assert(!listQueueIsEmpty(q));				// Check to see whether or not the list is empty.
	return q->firstLink->next->value;			// Return the value of the first link. (The value after the sentinel)
}


/*
* This function is a tester function that iterates through the list
* and prints out the values at each link.
*/
void printList(struct listQueue* l)
{
	assert(l != 0);								// Verify that l isn't empty/null.
	struct link * printMe = l->firstLink->next;	// Start with the first link in the queue.
	while (printMe!= NULL) {					// While printMe isn't null: (Loop executes until end of the queue)
		printf("Value: %d\n", printMe->value);	// Print the value printMe points to.
		printMe = printMe->next;				// Set printMe to the next link.
	}
}

/**************************************************
Stack Implementation
***************************************************/
struct linkedListStack {
	struct listQueue *Q1;						// Initialize routine sets to zero/NULL.
	struct listQueue *Q2;						// Initialize routine sets to zero/NULL.
	int structSize;								// Size of the stack.
};

/*
 * This function initializes the values of the created Stack. Initializes 
both 
 * queues and the structSize.
 */
void linkedListStackInit(struct linkedListStack * s)
{
	// FIXME: you must write this
	s->structSize = 0;												// Set initial size to 0.
	s->Q1 = (struct listQueue *)malloc(sizeof(struct listQueue));	// Allocate memory for Q1.
	s->Q2 = (struct listQueue *)malloc(sizeof(struct listQueue));	// Allocate memory for Q2.
	listQueueInit(s->Q1);											// Initialize the first queue.
	listQueueInit(s->Q2);											// Initialize the second queue.
}

/*
* This function creates the linked list stack. It allocates the memory and 
calls the
* initialization function to initialize all of the values. It then returns 
the stack.
*/
struct linkedListStack * linkedListStackCreate(){
    // FIXME: you must write this
	struct linkedListStack *newStack = malloc(sizeof(struct linkedListStack));	// Allocate memory for the new stack.
	linkedListStackInit(newStack);												// Initialize the new stack.
	return newStack;															// Return statement.
}

/*
* This function returns 1 if the linked list stack is empty and otherwise 
returns a 0.
*/
int linkedListStackIsEmpty(struct linkedListStack *s) {
	// FIXME: you must write this
	if (s->structSize == 0) {	// If size == 0, the stack is empty, so:
		return 1;
	}
	else {						// Otherwise:
		return 0;
	}
}

/*
 * This is the linked list acting as a stack push function. It takes 
 * a linked list stack argument and a value and pushes it onto the stack. 
The
 * funciton then also increases the size of the stack by 1. 
 */
void linkedListStackPush(struct linkedListStack *s, TYPE d) {
	
    // FIXME: you must write this
	listQueueAddBack(s->Q2, d);
	while (!listQueueIsEmpty(s->Q1)){	// Push all the remaining elements in Q1 to Q2.
		listQueueAddBack(s->Q2, listQueueFront(s->Q1));
		listQueueRemoveFront(s->Q1);
	}
	// Swap the queues:
	struct listQueue *q = s->Q1;		// Assign the contents of Q1 to a temporary queue.
	s->Q1 = s->Q2;						// Swap the contents of Q1 and Q2.
	s->Q2 = q;							// Copy the elements of the temporary queue (Q1) into Q2.
	s->structSize++;					// Decrement the size by 1.
}

/*
 * This function pops a value off of the stack. It does this by moving all 
values
 * that are currently on the stack to the other queue. The stack top is 
maintained
 * at the back of the queue list. 
 */
void linkedListStackPop(struct linkedListStack *s) {
	// FIXME: you must write this
	if (!listQueueIsEmpty(s->Q1)) {		// If Q1 is empty, return:
		listQueueRemoveFront(s->Q1);	// Remove the first element of Q1.
		s->structSize--;				// Decrement the size of the stack by 1.
	}
	else {								// Otherwise:
		printf("Stack is empty.\n");	// Print statement.
		return;
	}
}

/*
 * This function returns the value that is at the back of the queue that 
is 
 * maintaing the values of the stack. 
 */
TYPE linkedListStackTop(struct linkedListStack *s) {
	// FIXME: you must write this
	if (listQueueIsEmpty(s->Q1)) {	// If no elements are in Q1, return:
		return -1;
	}
	else {							// Otherwise:
		TYPE value = listQueueFront(s->Q1);		// Retrieve the front value of Q1 and store it into the TYPE (int) variable.
		return value;				// Return the value.
	}
}

/*
 * This function gores through the stack and removes each link in the 
queue.
 * It then frees the struct itself. 
 */
void linkedListStackFree(struct linkedListStack *s){
	assert(s != 0);
	while (s->structSize != 0) 
	{
		linkedListStackPop(s);
	}
	free(s->Q1->firstLink);
	free(s->Q2->firstLink);
	free(s->Q1);
	free(s->Q2);
	free(s);
}

/*
 * Main is used to test the stack ADT.
 */
int main(int argc, char* argv[])
{
	struct linkedListStack *stack = linkedListStackCreate();

	//Test Stack
	//Push 4 values onto the stack
	printf("Pushing the value: 1\n");
	linkedListStackPush(stack, 1);
	printf("Pushed.\n\n");

	printf("Pushing the value: 2\n");
	linkedListStackPush(stack, 2);
	printf("Pushed.\n\n");

	printf("Pushing the value: 3\n");
	linkedListStackPush(stack, 3);
	printf("Pushed.\n\n");

	printf("Pushing the value: 4\n");
	linkedListStackPush(stack, 4);
	printf("Pushed.\n\n");



	//Print value at the top and then remove it
	printf("Value at the top of stack %d now being popped. \n",linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));  
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	//Try to pop when the stack is empty prints error:
	printf("Trying to pop empty stack:\n");

	linkedListStackPop(stack);

	
	//Push and Pop alternating
	printf("Pushing the value: 10\n");
	linkedListStackPush(stack, 10);
	printf("Pushed.\n\n");

	printf("Pushing the value: 11\n");
	linkedListStackPush(stack, 11);
	printf("Pushed.\n\n");

	printf("One more pop:\n");
	linkedListStackPop(stack);
	printf("Value at the top of stack: %d\n", 
linkedListStackTop(stack));

	linkedListStackFree(stack);

	return 0;

}


