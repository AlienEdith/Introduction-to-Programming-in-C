#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

int findEqIdx(char * line){
  char c = *line;
  int count = 0;
  while(c!='='){
    count++;
    c = *(line+count);
    if(c=='='){
      return count;
    }
  }
  return -1;
}


char * getKey(char * line){
  int eq_idx = findEqIdx(line);
  if(eq_idx == -1){
    return NULL;
  }                                
  char * key = malloc((eq_idx+1)*sizeof(*key));
  strncpy(key, line, eq_idx);
  key[eq_idx] = '\0';
  return key;
}

char * getValue(char * line){
  int eq_idx = findEqIdx(line);
  if(eq_idx == -1){            
    return NULL;               
  }
  char * value = NULL;
  size_t len = strlen(line);
  if(line[len-1] != '\n'){
    value = realloc(value, ((int)len - eq_idx)*sizeof(*value));
    strcpy(value,(line+eq_idx+1));
    value[(int)len-eq_idx-1] = '\0';                           
  }else{
    value = realloc(value, ((int)len - eq_idx)*sizeof(*value));
    strncpy(value,(line+eq_idx+1),(int)len-eq_idx-1);                          
    value[(int)len-eq_idx-2] = '\0';                           
  }
  return value;
}

kvpair_t * parseKV(char * line){
  kvpair_t * pair = malloc(sizeof(*pair));
  pair -> key = getKey(line);
  if(pair->key == NULL){
    return NULL;
  }
  pair -> value = getValue(line);
  if(pair->value == NULL){
    return NULL;
  }
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if(f==NULL){
    return NULL;
  }

  kvarray_t * arr = malloc(sizeof(*arr));
  arr -> array = NULL;
  char * line = NULL;
  size_t size = 0;
  size_t sz = 0;
  while((getline(&line, &size, f))>=0){
    arr -> array = realloc(arr->array, (sz+1)*sizeof(arr->array));
    arr -> array[sz] = parseKV(line);
    if(arr -> array[sz] == NULL){
      return NULL;
    }
    sz++;
  }
  free(line);
  arr -> sz = sz;
  fclose(f);
  return arr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  int sz = pairs -> sz;
  for(int i=0; i<sz; i++){
    free((pairs -> array[i])-> key);
    free((pairs -> array[i])-> value);
    free(pairs -> array[i]);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t sz = pairs -> sz;
  kvpair_t * temp_kvp;
  for(size_t i=0; i<sz; i++){
    temp_kvp = pairs->array[i];
    printf("key = '%s' value = '%s'\n", temp_kvp->key, temp_kvp->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  size_t sz = pairs->sz;
  for(size_t i=0; i<sz; i++){
    if(strcmp(key, (pairs->array[i])->key)==0){
      return (pairs->array[i])->value;
    }
  }
  return NULL;
}
