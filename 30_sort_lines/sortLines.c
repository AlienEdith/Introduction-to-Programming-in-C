#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char **  readFromStd(char ** lines, size_t * count){
  char * curr = NULL;
  size_t sz = 0;
  
  while(getline(&curr, &sz, stdin)>=0){
    if (curr==NULL){
      return NULL;
    }
    lines = realloc(lines, (*count+1)*sizeof(*lines));
    if(lines==NULL){
      return NULL;
    }
    lines[*count] = curr;
    (*count)++;
    curr = NULL;
  }

  if(*count == 0){
    return NULL;
  }
  free(curr);
  return lines;
}

char **  readFromFiles(char ** lines, char * filename, size_t * count){      
  lines = NULL;
  char * curr = NULL;                            
  size_t sz  = 0;

  FILE * f = fopen(filename, "r");
  if(f==NULL){
    return NULL;
  }
  while(getline(&curr, &sz, f)>=0){         
    if (curr==NULL){                             
      return NULL;                               
    }
    lines = realloc(lines, (*count+1)*sizeof(*lines)); 
    if(lines==NULL){
      return NULL;
    }
    lines[*count] = curr;                             
    (*count)++;
    curr = NULL;                                                
  }                                              
  free(curr);
  int close = fclose(f);
  if(close != 0){
    return NULL;
  }
  return lines;
}

int printArray(char ** lines, size_t count){
  if(count>1){
    sortData(lines, count);
  }else{
    return EXIT_FAILURE;
  }
  for(size_t i=0; i<count; i++){
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
  return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {

  char ** lines = NULL;
  size_t count = 0;
  int printSuc = 0;
  
  if(argc == 1){
    lines = readFromStd(lines, &count);
    if(lines == NULL){
      return EXIT_FAILURE;
    }
    printSuc = printArray(lines, count);
    if(printSuc == EXIT_FAILURE){
      fprintf(stderr, "Print fail\n");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;                 
  }else if(argc > 1){
    for(int i=1; i<argc; i++){
      char * filename = argv[i];
      FILE * f = fopen(filename, "r");
      if(f==NULL){
	fprintf(stderr, "Error in file\n");
	return EXIT_FAILURE;
      }else{
	fclose(f);
      }
    }
    for(int i=1; i<argc; i++){
      char * filename = argv[i];
      lines = readFromFiles(lines, filename, &count);
      if(lines == NULL){                   
        return EXIT_FAILURE;               
      }
       printSuc = printArray(lines, count);
       lines = NULL;
       count = 0;
       if(printSuc == EXIT_FAILURE){         
         fprintf(stderr, "Print fail\n");    
         return EXIT_FAILURE;                
       }                                      
    }                                                  
    
  }
  
  return EXIT_SUCCESS;
}
