#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);

int main(void){

  if(power(2,2) != 4){
    return EXIT_FAILURE;
  }                      

  if(power(0,0) != 1){   
   return EXIT_FAILURE; 
  }

  if(power(0,1) != 0){   
   return EXIT_FAILURE; 
  }

  if(power(-2,1) != (-2)){   
    return EXIT_FAILURE; 
  }

  if(power(-2,2) != 4){   
    return EXIT_FAILURE; 
  }
  
  return EXIT_SUCCESS;
}
