/* oop.c - Object Oriented Programming with "square" and "rect_angle" Classes
 *
 * $ gcc oop.c
 * $ ./a.out
*/

// Define MACRO Constructors for all the Classes
#define SQUARE_CONSTRUCTOR(length)      {SQUARE, length}
#define RECT_CONSTRUCTOR(length, width) {RECTANGLE, length, width}

// Enumerate and Define All Classes for Subtype Polymorphism
typedef enum class {SQUARE, RECTANGLE} class;

typedef struct square {
  class type; // shares type field with all enumerated classes
  double side_length;
} square;

typedef struct rect_angle {
  class type; // shares type field with all enumerated classes
  double length;
  double width;
} rect_angle;

square square_constructor(double side_length);

rect_angle rect_constructor(double length, double width);

// destructor function for a square or rect_angle structure 
void (*)destructor (void *obj)
{
  printf("destrut %s.\n", ((square*)obj)->type == SQUARE ? "square":"rectangle");
}

// Returns the area of a square or rect_angle structure
double get_area (const void *);


rect_angle rect_constructor (double length, double width)
