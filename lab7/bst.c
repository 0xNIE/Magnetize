#include <stdlib.h>
#include <stdio.h>
#include "adrbook.h"

const char *_bst_todo_format = "TODO [bst]: %s\nhalting\n";

bst *bst_singleton(vcard *c)
{
  bst* leaf = (bst*)malloc(sizeof(bst));
  leaf->c = c;
  leaf->left = NULL;
  leaf->right = NULL;
  return leaf;
}

int bst_insert(bst *t, vcard *c)
{
  if (t == NULL|| t->c == NULL) {
    fprintf(stderr, "ERROR: Empty BST as input"); 
    return 0;
  }
  int x = strcmp(c->cnet, t->c->cnet);
  if (x == 0) {
    return 0;
  }
  else if (x < 0) {
    if (t->left == NULL) {
      t->left = bst_singleton(c);
      return 1; 
    } else {
      return bst_insert(t->left, c);
    }
  }
  else {
    if (t->right == NULL) {
      t->right = bst_singleton(c);
      return 1;
    } else {
      return bst_insert(t->right, c);
    }
  }
}

unsigned int bst_num_entries(bst *t)
{
  if (t == NULL) {
    return 0;
  }
  else {
    return bst_num_entries(t->left) + bst_num_entries(t->right) + 1;
  }

}

unsigned int bst_height(bst *t)
{
  if (t == NULL) {
    return 0;
  }
  else {
    int l_height = bst_height(t->left);
    int r_height = bst_height(t->right);
    if (l_height > r_height){
      return l_height + 1;
    }
    else {
      return r_height + 1;
    }
  }
}

vcard *bst_search(bst *t, char *cnet, int *n_comparisons)
{
  if (t == NULL) {
    return NULL;
  } else {
    int x = strcmp(cnet, t->c->cnet);
    if (x < 0) {
      ++(*n_comparisons);
      return bst_search(t->left, cnet, n_comparisons);
    }
    else if (x == 0) {
      ++(*n_comparisons);
      return t->c;
    }
    else {
      return bst_search(t->right, cnet, n_comparisons);
    }
  }
}

/* note: f is the destination of the output, e.g. the screen;
 * our code calls this with stdout, which is where printfs are sent;
 * simply use fprintf rather than printf in this function, and pass in f
 * as its first parameter
 */
unsigned int bst_c(FILE *f, bst *t, char c)
{
  if (t == NULL) {
    return 0;
  }
  char comp = t->c->cnet[0];
  if (comp < c) {
    return bst_c(f, t->left, c);
  }
  else if (comp == c) {
    fprintf(f, "%s\n", t->c->cnet);
    return 1 + bst_c(f, t->left, c) + bst_c(f, t->right, c);
  }
  else {
    return bst_c(f, t->right, c);
  }
}

void bst_free(bst *t)
{
  if (t == NULL) {
    free(t);
  }
  else {
    vcard_free(t->c);
    bst_free(t->left);
    bst_free(t->right);
    free(t);
  }
}
