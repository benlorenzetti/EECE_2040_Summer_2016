// namespace.h

#ifndef NAMESPACE_H
#define NAMESPACE_H
#include <stdio.h>  // for printf()
#include <stdlib.h> // for EXIT_SUCCESS

#define UNIQUE_PREFIX_DEFAULT_NAMESPACE vector

#ifdef UNIQUE_PREFIX_NAMESPACE
  #define UNIQUE_PREFIX_DOT_NAMESPACE UNIQUE_PREFIX_NAMESPACE
#endif
#ifndef UNIQUE_PREFIX_NAMESPACE
  #define UNIQUE_PREFIX_DOT_NAMESPACE UNIQUE_PREFIX_DEFAULT_NAMESPACE
#endif

static int unique_prefix_push_back (void*, const void*);
static void* unique_prefix_at (void*, int);

typedef struct {
  int (*const push_back)(void*, const void*);
  void* (*const at)(void*, int);
} unique_prefix_namespace_struct;

extern unique_prefix_namespace_struct const UNIQUE_PREFIX_DOT_NAMESPACE;

unique_prefix_namespace_struct const UNIQUE_PREFIX_DOT_NAMESPACE = {
  unique_prefix_push_back, unique_prefix_at
};

// From this point on could be in an implementation file.

static int unique_prefix_push_back (void* dest, const void* src) {
  printf("in unique_prefix_push_back().\n");
  return EXIT_SUCCESS;
}

static void* unique_prefix_at (void* dest, int n) {
  printf ("in unique_prefix_at().\n");
}

#endif
