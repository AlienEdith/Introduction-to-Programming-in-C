#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double calculate(double initial, retire_info info, int startAge){
  double res = initial;
  for(int i=0; i<info.months; i++){
    printf("Age %3d month %2d you have $%.2lf\n", startAge/12, startAge%12, res);
    res += res * (info.rate_of_return/12) + info.contribution;
    startAge++;
  }
  return res;
}

void retirement (int startAge, double initial,   
                 retire_info working, retire_info retired){

  double worked = calculate(initial, working, startAge);
  calculate(worked, retired,startAge+working.months);

}

int main(void){
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;
  retirement(327, 21345, working, retired);
  return 0;
}
