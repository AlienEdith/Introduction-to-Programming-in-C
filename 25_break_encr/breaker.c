#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void getFreqArray(int *freqArr, FILE * f){
  int c;
  while((c=fgetc(f)) != EOF){
    if(isalpha(c)){
      c = tolower(c);
      c = c - 'a';
      freqArr[c] = freqArr[c]+1;
    }
  }
}

int maxFreqIdx(int * freqArr){
  int max = freqArr[0];
  int maxIdx = 0;
  for(int i=0; i<26; i++){
    if(freqArr[i]>max){
      max = freqArr[i];
      maxIdx = i;
    }
  }
  return maxIdx;
}

int main(int argc, char ** argv){
  if(argc!=2){
    fprintf(stderr, "Usage: Wrong amount of Arguments\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if(f==NULL){
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int freqArr[26] = {0};
  getFreqArray(freqArr, f);
  int maxIdx = maxFreqIdx(freqArr);
  int key = (maxIdx + 'a' - 'e' + 26)%26;
  printf("%d\n", key);
}
