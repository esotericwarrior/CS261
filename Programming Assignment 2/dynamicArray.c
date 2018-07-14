/************************************************************
*	Name: Tristan Santiago									
*	Date: 7/14/2018											
*	Description: dynamicArray.c: Dynamic Array				
*	implementation.											
************************************************************/
#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"
#define TYPE int

struct DynArr
{
	TYPE *data;												// Pointer to the data array.
	int size;												// Number of elements in the array.
	int capacity;											// Capacity of the array.
};

/************************************************************************
*	Dynamic Array Functions							
************************************************************************/
/************************************************************
*	initDynArr							
*	Description: This function initializes and allocates the
*	data of the dynamic array.								
*	param: 	v		pointer to the dynamic array			
*	param:	cap 	capacity of the dynamic array			
*	pre:	v is not null										
*	post:	internal data array can hold cap elements			
*	post:	v->data is not null								
************************************************************/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;	
}

/************************************************************
*	DynArr* newDynArr						
*	Description: This function allocates and initializes the
*	dynamic array.											
*	param:	cap 	desired capacity for the dyn array		
*	pre:	none												
*	post:	none												
*	ret:	a non-null pointer to a dynArr of cap capacity and	
*	0 elements in it.											
************************************************************/
DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/************************************************************
*	freeDynArr							
*	Description: This function deallocates the data array in	
*	the dynamic array.										
*	param: 	v		pointer to the dynamic array			
*	pre:	none												
*	post:	d.data points to null								
*	post:	size and capacity are 0								
*	post:	the memory used by v->data is freed					
************************************************************/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 										// Free the space on the heap.
		v->data = 0;   										// Make it point to null.
	}
	v->size = 0;
	v->capacity = 0;
}

/************************************************************
*	deleteDynArr						
*	Description: This function deallocates the data array and
*	the dynamic array											
*	param: 	v		pointer to the dynamic array			
*	pre:	none												
*	post:	the memory used by v->data is freed					
*	post:	the memory used by d is freed						
************************************************************/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/************************************************************
*	_dynArrySetCapacity						
*	Description: This function resizes the underlying array	
*	to be the size cap.										 
*	param: 	v		pointer to the dynamic array			
*	param:	cap		the new desired capacity				
*	pre:	v is not null									
*	post:	v has capacity newCap							
************************************************************/
void _dynArrSetCapacity(DynArr *v, int newCap)
{	
	assert(v != 0);
	/* FIXME: You will write this function */
	TYPE *newData = (TYPE*)malloc(sizeof(TYPE)*newCap);		// Allocate memory for the new array.
	assert(newData != 0);									// Check that the array isn't null.
	for (int i = 0; i < v->size; i++)						// Initialize a for loop to copy the elements.
	{
		newData[i] = v->data[i];							// Copy the old values into the new array, one at a time.
	}
	free(v->data);											// Delete the old array.
	v->data = newData;										// Update data and size.
	v->capacity = newCap;									// Updata capacity.
}

/************************************************************
*	sizeDynArr							
*	Description: Get the size of the dynamic array.			
*	param: 	v		pointer to the dynamic array			
*	pre:	v is not null									
*	post:	none											
*	ret:	the size of the dynamic array					
/***********************************************************/
int sizeDynArr(DynArr *v)
{
	assert(v != 0);											// Check to make sure v isn't null.
	return v->size;											// Return the size of the array.
}

/************************************************************
*	addDynArr							
*	Description: Adds an element to the end of the dynamic	
*	array.													
*	param: 	v		pointer to the dynamic array			
*	param:	val		the value to add to the end of the		
*	dynamic array.											
*	pre:	the dynArry is not null							
*	post:	size increases by 1								
*	post:	if reached capacity, capacity is doubled		
*	post:	val is in the last utilized position in the		
*	array.													
/***********************************************************/
void addDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);											// Make sure that v isn't null.
	if (v->size >= v->capacity) {							// If size is >= capacity:
		_dynArrSetCapacity(v, 2 * v->capacity);				// Double the size of the array.
	}
	v->data[v->size] = val;									// Place value into the last position of the array.
	v->size++;												// Increment size by 1.
}

/************************************************************
*	getDynArr							
*	Desription: Get an element from the dynamic array from	
*	a specified position.									
*	param: 	v		pointer to the dynamic array			
*	param:	pos		integer index to get the element from	
*	pre:	v is not null									
*	pre:	v is not empty									
*	pre:	pos < size of the dyn array and >= 0			
*	post:	no changes to the dyn Array						
*	ret:	value stored at index pos						
/***********************************************************/
TYPE getDynArr(DynArr *v, int pos)
{
	assert(v != 0);												// Make sure that the array isn't null.
	assert(!isEmptyDynArr(v));									// Make sure that the array isn't empty.
	assert(pos < v->size);										// Make sure that the position isn't greater than the last position of the array.
	assert(pos >= 0);											// Make sure that that position isn't less than index 0.
	return v->data[pos]; 
}

/************************************************************
*	putDynArr							
*	Description: Put an item into the dynamic array at the	
*	specified location, overwriting the element that was	
*	there.													
*	param: 	v		pointer to the dynamic array			
*	param:	pos		the index to put the value into			
*	param:	val		the value to insert						
*	pre:	v is not null									
*	pre:	v is not empty									
*	pre:	pos >= 0 and pos < size of the array			
*	post:	index pos contains new value, val				
***********************************************************/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	assert(v != 0);
	assert(pos < v->size);
	assert(pos >= 0);
	v->data[pos] = val;
}

/************************************************************
*	swapDynArr							
*	Description: Swap two specified elements in the dynamic	
*	array.													
*	param: 	v		pointer to the dynamic array			
*	param:	i,j		the elements to be swapped				
*	pre:	v is not null									
*	pre:	v is not empty									
*	pre:	i, j >= 0 and i,j < size of the dynamic array	
*	post:	index i now holds the value at j and index j	
*	now holds the value at i.								
************************************************************/
void swapDynArr(DynArr *v, int i, int  j)
{
	TYPE temp;
	assert(v != 0);
	assert(i < v->size);
	assert(j < v->size);
	assert(i >= 0);
	assert(j >= 0);
	temp = v->data[i];											// Assign the first value to a temporary variable.
	v->data[i] = v->data[j];									// Swap the values of element j and element i.
	v->data[j] = temp;											// Copy the value of the temporary value into j.
}

/************************************************************
*	removeAtDynArr							
*	Description: Remove the element at the specified		
*	location from the array, shifts other elements back one	
*	to fill the gap.										
*	param: 	v		pointer to the dynamic array			
*	param:	idx		location of element to remove			
*	pre:	v is not null									
*	pre:	v is not empty									
*	pre:	idx < size and idx >= 0							
*	post:	the element at idx is removed					
*	post:	the elements past idx are moved back one		
************************************************************/
void removeAtDynArr(DynArr *v, int idx)
{
	assert(v != 0);
	assert(!isEmptyDynArr(v));
	assert(idx < v->size);
	assert(idx >= 0);
	
	for(int i = idx; i <= v->size-2; i++)
	{
		v->data[i] = v->data[i+1];
	}
	v->size--;
}

/************************************************************************
*	Stack Interface Functions
************************************************************************/
/************************************************************
*						isEmptyDynArr						
*	Description: Returns boolean (encoded in an int)		
*	demonstrating whether or not the dynamic array stack	
*	has an item on it.										
*	param:	v		pointer to the dynamic array			
*	pre:	the dynArr is not null							
*	post:	none											
*	ret:	1 if empty, otherwise 0							
************************************************************/
int isEmptyDynArr(DynArr *v)
{
	assert(v != 0);
	return !(v->size);
}

/************************************************************
*	pushDynArr							
* 	Push an element onto the top of the stack				
*	param:	v		pointer to the dynamic array			
*	param:	val		the value to push onto the stack		
*	pre:	v is not null									
*	post:	size increases by 1								
*			if reached capacity, capacity is doubled		
*			val is on the top of the stack					
************************************************************/
void pushDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);
	addDynArr(v, val);
}

/************************************************************
*	topDynArr							
*	Returns the element at the top of the stack 			
*	param:	v		pointer to the dynamic array			
*	pre:	v is not null									
*	pre:	v is not empty									
*	post:	no changes to the stack/						
************************************************************/
TYPE topDynArr(DynArr *v)
{
	assert(v != 0);
	assert(!isEmptyDynArr(v));
	return v->data[v->size - 1];
}

/************************************************************
*	popDynArr							
*	Description: Removes the element on top of the stack.	
*	param:	v		pointer to the dynamic array			
*	pre:	v is not null									
*	pre:	v is not empty									
*	post:	size is decremented by 1						
*			the top has been removed.						
************************************************************/
void popDynArr(DynArr *v)
{
	assert(v != 0);												// Verify that the array isn't null.
	assert(!isEmptyDynArr(v));									// Verify that the array isn't empty.
	v->size--;													// Decrement size by 1.
}

/************************************************************************
*	Bag Interface Functions							
************************************************************************/
/************************************************************
*	containsDynArr							
*	Description: Returns boolean (encoded as an int)		
*	demonstrating whether or not the specified value is in	
*	the collection:											
*	true = 1												
*	false = 0												
*	param:	v		pointer to the dynamic array			
*	param:	val		the value to look for in the bag		
*	pre:	v is not null									
*	pre:	v is not empty									
*	post:	no changes to the bag							
************************************************************/
int containsDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);
	assert(!isEmptyDynArr(v));
	for (int i = 0; i < sizeDynArr(v); i++) {
		if (EQ(v->data[i], val)) {
			return 1;
		}
	}
	return 0;
}

/************************************************************
*	removeDynArr						
*	Description: Removes the first occurrence of the		
*	specified value from the collection if it occurs.		
*	param:	v		pointer to the dynamic array			
*	param:	val		the value to remove from the array		
*	pre:	v is not null									
*	pre:	v is not empty									
*	post:	val has been removed							
*	post:	size of the bag is reduced by 1					
************************************************************/
void removeDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);											// Check to make sure the array isn't null.
	assert(!isEmptyDynArr(v));								// Check to make sure the array isn't empty.
	assert(containsDynArr(v, val));							// Check to see if the element is actually present.
	for (int i = 0; i < sizeDynArr(v); i++) {
		if (EQ(v->data[i], val))
		{
			removeAtDynArr(v, i);							// Remove element and decrement size by 1.
			break;
		}
	}
}