/************************************************************
*	Name: Tristan Santiago									*
*	Date: 7/14/2018											*
*	Description: stack.c: Stack application.				*
*	implementation.											*
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"

/****************************************************************
*		Using stack to check for unbalanced parentheses.		*
****************************************************************/
/************************************************************
*							nextChar						*
*	Description: Returns the next character of the string,	*
*	once reaches end return '0' (zero).						*
*	param: 	s pointer to a string							*
*	pre: s is not null										*
************************************************************/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}
/************************************************************
*						isBalanced							*
*	Description: Checks whether the (), {}, and [] are		*
*	balanced or not.										*
*	param: 	s pointer to a string							*
*	pre: s is not null										*
*	post:													*
************************************************************/
int isBalanced(char* s)
{		
	assert(s != 0);
	DynArr *stack = newDynArr(2);
	char ch;

	do {											// Iterate through each character in the string:
		ch = nextChar(s);

		if (ch == '{') {							// If "{" is found:
			addDynArr(stack, '}');					// Push it onto the system stack.
		}
		else if (ch == '[') {						// If "[" is found:
			addDynArr(stack, ']');					// Push it onto the system stack.
		}
		else if (ch == '(') {						// If "(" is found:
			addDynArr(stack, ')');					// Push it onto the system stack.
		}
		else if (ch == '}') {						// If "}" is found,
			if (sizeDynArr(stack) == 0) {			// and the stack is empty:
				deleteDynArr(stack);				// Delete the array.
				return 0;
			}
			else if (topDynArr(stack) == '}') {		// If "}" is found:
				popDynArr(stack);					// Pop the top of the system stack.
			}
			else {									// Default case:
				deleteDynArr(stack);				// Delete the array.
				return 0;
			}
		}
		else if (ch == ']') {						// If "]" is found,
			if (sizeDynArr(stack) == 0) {			// and the stack is empty:
				deleteDynArr(stack);				// Delete the array.
				return 0;
			}
			else if (topDynArr(stack) == ']') {		// If "]" is found on the top of the stack:
				popDynArr(stack);					// Remove it.
			}
			else {									// Default case:
				deleteDynArr(stack);				// Delete the array.
				return 0;
			}
		}
		else if (ch == ')') {						// If ")" is found:
			if (sizeDynArr(stack) == 0) {			// And the stack is empty:
				deleteDynArr(stack);				// Delete the array.
				return 0;
			}
			else if (topDynArr(stack) == ')') {		// If ")" is found on the top of the stack:
				popDynArr(stack);					// Remove it.
			}
			else {									// Default case:
				deleteDynArr(stack);				// Delete the array.
				return 0;
			}
		}
		else {

		}
	} while (ch != '\0');						// Until the null terminator is located.
	/* Delete the array once we have reached the end of the array. */
	if (sizeDynArr(stack) == 0) {
		deleteDynArr(stack);
		return 1;
	}
	else {
		deleteDynArr(stack);
		return 0;
	}
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	//char s[] = "(})";
	//char s[] = "}{}{[]}()";
	//char s[] = "{ [}]}";
	//char s[] = "({[]}))()";
	int res;
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

