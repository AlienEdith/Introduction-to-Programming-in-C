#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * res = malloc(sizeof(*res));
  res -> array = NULL;
  res -> sz = 0;
  res -> unknowSz = 0;
  return res;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if(name==NULL){      
    (c -> unknowSz)++;
    return;
  }
  int find_flag = 0;
  size_t size = c->sz;
  for(size_t i=0; i<size; i++){                    
    char * str = c->array[i]->str;
    if(strcmp(str,name) == 0){
      (c->array[i])->counts++;
      find_flag = 1;
      break;
    }
  }
  if(find_flag==0){
    c->array = realloc(c->array, (c->sz+1)*sizeof(*(c->array)));
    one_count_t * ptr = malloc(sizeof(*ptr));
    ptr -> str = NULL;
    ptr -> str = realloc(ptr->str, (strlen(name)+1)*sizeof(*(ptr->str)));
    strcpy(ptr->str, name);
    ptr->counts = 1;
    c->array[c->sz] = ptr;
    c->sz++;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for(size_t i=0; i<c->sz; i++){
    fprintf(outFile, "%s: %d\n", c->array[i]->str, c->array[i]->counts);
  }
  if(c->unknowSz > 0){
    fprintf(outFile, "<unknown> : %d\n", (int)c->unknowSz);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i=0; i<c->sz; i++){
    free(c->array[i]->str);
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
