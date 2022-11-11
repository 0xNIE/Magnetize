#include <stdlib.h>
#include <stdio.h>
#include "adrbook.h"

const char *_bst_todo_format = "TODO [bst]: %s\nhalting\n";

bst *bst_singleton(vcard *c)
{
  fprintf(stderr,_bst_todo_format,"bst_singleton");
  exit(1);
}

int bst_insert(bst *t, vcard *c)
{
  fprintf(stderr,_bst_todo_format,"bst_insert");
  exit(1);
}

unsigned int bst_num_entries(bst *t)
{
  fprintf(stderr,_bst_todo_format,"bst_num_entries");
  exit(1);  
}

unsigned int bst_height(bst *t)
{
  fprintf(stderr,_bst_todo_format,"bst_height");
  exit(1);
}

vcard *bst_search(bst *t, char *cnet, int *n_comparisons)
{
  fprintf(stderr,_bst_todo_format,"bst_search");
  exit(1);
}

/* note: f is the destination of the output, e.g. the screen;
 * our code calls this with stdout, which is where printfs are sent;
 * simply use fprintf rather than printf in this function, and pass in f
 * as its first parameter
 */
unsigned int bst_c(FILE *f, bst *t, char c)
{
  fprintf(stderr,_bst_todo_format,"bst_c");
  exit(1);
}

void bst_free(bst *t)
{
  fprintf(stderr,_bst_todo_format,"bst_free");
  exit(1);
}
