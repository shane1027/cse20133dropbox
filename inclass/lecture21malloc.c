/*****
 * Name: lecture21malloc.c
 * Purpose: A program to practice with malloc to dynamically 
 * allocatate an array.
 ******/
#include <stdio.h>
#include <stdlib.h>

int main() {
  /** Declare the array, as a pointer **/
  int *dynaArray;

  int userArrSize;  /** To store its size **/

  printf("\n\n Enter an array size between 1 and 10: ");
  scanf("%d", &userArrSize);

  /** Figure how how much space is needed **/
  int arrSize = userArrSize*(int)sizeof(int);

  /** Now, set up the space for the array. 
      Note we're using pointers here, and casting to type "int *" **/
  dynaArray = (int *) malloc(arrSize);

  /** Now, populate our array with some numbers. Let's say, i*10 **/
  int i;
  printf("Creating an array from 1 to %d, where each element is i*10: \n", userArrSize);
  for (i = 0; i < userArrSize; i++) {
    dynaArray[i] = i*10;
    printf("dynaArray[%d] is: %d \n", i, dynaArray[i]);
  }

  /** Free the memory!**/
  free(dynaArray);

  /** Your turn: Allocate space for a second array that is twice as large
      as the first. Initialize to have sequential even numbers, print out **/
}
