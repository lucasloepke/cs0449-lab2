/*
 * pointer.c - Source file with your solutions to the Lab.
 *             This is the file you will hand in to your instructor.
 */
#ifndef COMMON_H
#include "common.h"
#endif

/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

#if 0
You will provide your solution to this lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Function arguments and local variables (no global variables).
  2. Integer literals.

  Some of the problems restrict the set of allowed operators.

  You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions (unless otherwise stated).
  4. Use any operators not "allowed" at the top of the method you are writing.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has *undefined* behavior when shifting by a negative amount or an amount
     greater than or equal to the number of bits in the value being shifted.
     e.g. For x >> n, shifts by n < 0 or n >= *size of x* are undefined
     e.g. if x is a 32-bit int, shifts by >= 32 bits are undefined
     Undefined means you do not know what result you will get from the operation.
#endif

/*
 * STEP 2: Modify the following functions according the coding rules.
 */

/*
 * Return the size of an integer in bytes.
 *
 *  Calculate the size of an int using only arithmetic and casts!
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Any non arithmetic operatror
 */
int intSize() {
  /* I cast to char* in order to do pointer arithmetic since char is defined as 1 byte */
  int intArray[2];
  int *intPtr1 = intArray;
  int *intPtr2 = intArray + 1;
  return (char*) intPtr2 - (char*) intPtr1;
}


/*
 * Swap the 2 ints.
 *
 * Write code that swaps the contents of the 2 ints
 *   Kudos if you do it without a temp variable 
 *   ( But you need to know your bitwises! :)
 *   
 */
void swapInts(int *i1, int *i2){
  /* I cave and create a temp variable, storing the value of what i1 points to. Then I set the value
  at i1 equal to the value at i2, and then set the value of i2 equal to temp*/
  int temp = *i1;
  *i1 = *i2;
  *i2 = temp;
}


/*
 * Write the 4 Bytes that compose the integer "value" (little-endian)
 *   into the char array "array". They should be written 
 *   in big-endian byte order.
 *   Assume the char* points at a memory location with 4B available
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 */
void serializeBE(unsigned char *array, int value) {
  /* I cast the pointer of hte value to an unsigned char pointer to access individual bytes.
  Then I assign the bytes to the array in big-endian order*/
  unsigned char *ptr = (unsigned char*)&value;
  *(array+0) = *(ptr+3);
  *(array+1) = *(ptr+2);
  *(array+2) = *(ptr+1);
  *(array+3) = *(ptr);
}

/*
 * Write the 4 Bytes in the char array "array" (big-endian byte order) 
 *   into the integer "value" in little-endian byte order
 *   Assume the char* points at a memory location with 4B available
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 */
void deserializeBE(int* value, const unsigned char *array) {
  /* I obtain the numbes from array*/
  unsigned char one, two, three, four;
  one = *(array+0);
  two = *(array+1);
  three = *(array+2);
  four = *(array+3);

  unsigned int jeb, bob, henry, luis;
  jeb = ((int) one << 24);
  bob = ((int) two << 16);
  henry = ((int) three << 8);
  luis = ((int) four);

  *value = jeb | bob | henry | luis;
}

/*
 * Return 1 if ptr points to an element within the specified intArray, 0 otherwise.
 * Pointing anywhere in the array is fair game, ptr does not have to
 * point to the beginning of an element. Check the spec for examples if you are 
 * confused about what this method is determining.
 * size is the number of elements of intArray. Assume size != 0.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 */
int withinArray(int *intArray, int size, int *ptr) {
  /* I check if ptr appears after the beginning of intArray but also before its end. True returns 1*/
  return (intArray <= ptr && ptr < intArray + size);
}

/*
 * In C characters are are terminated by the null character ('\0')
 * given a pointer to the start of the string return the length of this string.
 * (The null character is not counted as part of the string length.)
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 */
int stringLength(char *s) {
  /* I increment the pointer until it reacher the null character, and then return the increment count*/
  int i = 0;
  while (*s != '\0') {
    i++;
    s++;
  }
  return i;
}

/*
 * Returns the length of the initial portion of str1 which consists only of characters that are part of str2.
 * The search does not include the terminating null-characters of either strings, but ends there.
 * 
 * Example, stringSpan("abcdefgh", "abXXcdeZZh"); // returns 5
 *  
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 */
int stringSpan(char * str1, char * str2) {
  /* For each character in str1 I check if it is found in str2. End when str1 char not found in
  str2 or when str1 ends.*/
  char* s1 = str1;
  int count = 0;
  while (*s1) {
    char* s2 = str2;
    int found = 0;
    while (*s2) {
      if (*s1 == *s2) {
          found = 1;
          break;
      }
      s2++;
    }
    if (!found) break;
    count++;
    s1++;
  }
  return count;
}

/*
 * Selection sort is a sorting algorithim that works by partitioning the array into
 * a sorted section and unsorted section. Then it repeatedly selects the minimum element
 * from the unsorted section and moves it to the end of the sorted section.
 *
 * So the pseudo-code might look something like this:
 * arr - an array
 * n - the length of arr
 *
 * for i = 0 to n - 1
 *   minIndex = i
 *   for  j = i + 1 to n
 *       if arr[minIndex] > arr[j]
 *           minIndex = j
 *       end if
 *   end for
 *   Swap(arr[i], arr[minIndex])
 * end for
 *
 * Implement selection sort below, it might be helpful to use the swapInts function you
 * defined earlier.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 */
void selectionSort(int *array, int arrLength) {
  /* I implemented selection sort as specified in the pseudo code */
  for (int i = 0; i < arrLength - 1; i++) {
    int *minPtr = array + i;
    for (int j = i + 1; j < arrLength; j++) { // find minimum element
      if (*(array + j) < *minPtr)
        minPtr = array + j;
    }
    if (minPtr != array + i) { // swap
      int temp = *(array + i);
      *(array + i) = *minPtr;
      *minPtr = temp;
    }
  }
}
