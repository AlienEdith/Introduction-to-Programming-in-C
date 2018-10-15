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

int main(int argc, char ** argv){
  if(argc!=2){
    fprintf(stderr, "Usage: Wrong amount of Arguments\n");
    return EXIT_FAILURE;
  }
  
  FILE * f = fopen(argv[1], "r");
  if(f == NULL){
    fprintf(stderr,"Usage: Couldn't open file\n");
    return EXIT_FAILURE;
  }

  int ch = fgetc(f);
  if(ch==EOF){
    fprintf(stderr,"Usage: Empty File\n");
    return EXIT_FAILURE;                          
  }

  char mat[10][10];
  int row = 0;
  int col = 0;
  while(ch != EOF){
    if(row > 9){
      fprintf(stderr,"Usage: Higher number of rows\n");
      return EXIT_FAILURE;                          
    }
    
    if(col==10){
      col = 0;
      row++;
      if(ch != '\n'){
	fprintf(stderr,"Usage: Missing new line at the end of the row\n");
	return EXIT_FAILURE;                          
      }
    }else{
      if(ch == '\n'){
        fprintf(stderr,"Usage: Less columns than expected\n");
        return EXIT_FAILURE;                          
      }
      mat[row][col] = ch;
      col ++;
    }
    ch = fgetc(f);
   }
  fclose(f);

  if(row<10){
    fprintf(stderr,"Usage: Lower number of rows\n");
    return EXIT_FAILURE;                          
  }

  rotate(mat);

  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
      printf("%c",mat[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
