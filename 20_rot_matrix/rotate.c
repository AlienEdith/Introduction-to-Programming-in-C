#include <stdio.h>
#include <stdlib.h>

void rotate(char matrix[10][10]){
  int range = 9;
  for(int i=0; i<5; i++){
    for(int j=i; j<9-i; j++){
      char temp = matrix[i][j];
      matrix[i][j] = matrix[range-j][i];
      matrix[range-j][i] = matrix[range-i][range-j];
      matrix[range-i][range-j] = matrix[j][range-i];
      matrix[j][range-i] = temp;
    }
  }
  
}
