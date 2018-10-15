#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"


counts_t * countFrFile(FILE * f, kvarray_t * kvPairs){
  char * line = NULL;
  size_t size = 0;
  char * key = NULL;
  char * value =NULL;
  
  counts_t * res = createCounts();

  if(res ==NULL){
    return NULL;
  }
  while(getline(&line, &size, f)>=0){
    int len = strlen(line);
    if(line[len-1] == '\n'){
      key = realloc(key, len*sizeof(*key));
      strncpy(key, line, len-1);
      key[len-1] = '\0';       
    }else{
      key = realloc(key, (len+1)*sizeof(*key));
      strncpy(key, line, len);
      key[len] = '\0';       
    }
    value = lookupValue(kvPairs, key);
    addCount(res, value);
  }
 
  free(line);
  free(key);
  
  return res;
}
counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if(f==NULL){
    return NULL;
  }
  counts_t * ret = countFrFile(f, kvPairs);
  if(ret == NULL){
    return NULL;
  }
  fclose(f);
  return ret;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if(argc < 3){
    fprintf(stderr, "Not enought arguments\n");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kvarray = readKVs(argv[1]);
  if(kvarray == NULL){
    fprintf(stderr, "Error reading pairs");
    return EXIT_FAILURE;
  }
 //count from 2 to argc (call the number you count i)
  for(int i=2; i<argc; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kvarray);
    //comput the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if(f==NULL){
      fprintf(stderr, "Error in outFile");
    }
    //print the counts from c into the FILE f
    printCounts(c,f);
    //close f
    fclose(f);

    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }


 //free the memory for kv
  freeKVs(kvarray);
  return EXIT_SUCCESS;
}
