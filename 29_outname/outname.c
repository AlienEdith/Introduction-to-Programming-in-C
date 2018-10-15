#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  int len = strlen(inputName);
  char * OutNameptr = malloc((len+8) * sizeof(*OutNameptr));
  char * ptr = OutNameptr;

  while(*inputName != '\0'){
    *ptr = *inputName;
    ptr++;
    inputName++;
  }
  
  char * suffix = ".counts";
  while(*suffix != '\0'){
    *ptr = *suffix;
    ptr++;
    suffix++;
  }
  *ptr = '\0';
  
  return OutNameptr;
}
