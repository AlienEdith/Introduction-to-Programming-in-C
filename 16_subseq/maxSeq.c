#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
  if(n==0)  return 0;
  int maxSeqLen = 1;
  int curSeqLen = 1;
  int * curValp = array;
  int * lastValp = array;
  for(int i=1; i<n; i++){
    curValp = array + i;
    lastValp = curValp - 1;
    if (*curValp > *lastValp){
      curSeqLen++;
      if(curSeqLen > maxSeqLen){
	maxSeqLen = curSeqLen;
      }
    }else{
      curSeqLen = 1;
    }
  }
  return maxSeqLen;
}
