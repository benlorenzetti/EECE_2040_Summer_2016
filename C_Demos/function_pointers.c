/* function_pointers.c
 *
 * gcc function_pointers.c
 * ./a.out
*/

#include <stdio.h>
#include <stdlib.h>

typedef void (*dest_f)(void *);
/* creates the type "dest_f" for "pointer to function with 1 void* argument
 * whose return is type void." */

void object_destructor(int *object)
{
  printf ("destructor called on object %d\n", *object);
}

void pop_back(int* object, dest_f destructor_function)
{
  (*destructor_function)( (void*)object );
  /* dereferences the function pointer and calls that function. */
}

int main()
{
  dest_f fptr;
  fptr = (void (*)(void*)) object_destructor;
  /* store a pointer to the function class1_destructor() (and cast it to the
     correct type first) */

  int instance = 1;
  
  pop_back(&instance, fptr);
}

