#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(){
  int array1[] = {-1,1,0,1};
  int array2[] = {1, 6, 10, 1, -3, 4, 5, 10};
  // int array3[] = {};
  int array4[] = {-1,-2,-3};
  int array5[] = {1,1,1,1,1};
  int array6[] = {0,2,5,7,8};
  
  if(maxSeq(array1,4) != 2){
    return EXIT_FAILURE;
  }

  if(maxSeq(array2,8) != 4){ 
   return EXIT_FAILURE;     
  }

  //if(maxSeq(array3,0) != 0){ 
  // return EXIT_FAILURE;      
  //}                          
  if(maxSeq(array4,3) != 1){ 
   return EXIT_FAILURE;      
  }
  if(maxSeq(array5,5) != 1){ 
   return EXIT_FAILURE;      
  }
  if(maxSeq(array6,5) != 5){ 
   return EXIT_FAILURE;      
  }                          
  
}                                                   
