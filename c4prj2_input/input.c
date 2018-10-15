#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "input.h"

size_t strToInt(char * str){
  size_t len = strlen(str);
  size_t res = 0;
  size_t delta = 0;
  for(size_t i=0; i<len; i++){
    delta = str[i] - '0';
    for(size_t j=0; j<len-i-1; j++){
      delta = delta * 10;
    }
    res = res + delta;
  }
  return res;
}

void lineToStr(char * line){
  size_t len = strlen(line);
  if(line[len-1] == '\n'){
    line[len-1] = '\0';
  }
}

int getLastIndex(const char * str, int fstIdx){
  char c = str[fstIdx];
  int count = 0;
  while(isalpha(c) || isdigit(c) || (c=='?')){
    count++;
    c = str[fstIdx + count];
  }
  if(count <=1 ){
    return -1;
  }
  return fstIdx+count;
}

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  char * c_name = NULL;
  int count = 0;
  int lstIdx = 0;
  int g_count = 0;
  size_t idx = 0;
  card_t * add_card;
  deck_t * ret_d = (deck_t*)malloc(sizeof(*ret_d));
  ret_d->n_cards = 0;
  ret_d->cards = NULL;

  while(str[count]!='\0'){
    if(!isalpha(str[count]) && !isdigit(str[count]) && (str[count] != '?')){
      count++;
    }else{
      lstIdx = getLastIndex(str,count);
      if(lstIdx == -1){
	return NULL;
      }
      if(str[count]=='?'){
	c_name = (char *)realloc(c_name,(lstIdx-count+1)*sizeof(*c_name));
	c_name = strncpy(c_name, str+count, (size_t)(lstIdx-count));
	c_name[lstIdx-count] = '\0';
	idx = strToInt(c_name+1);
	add_card = add_empty_card(ret_d);
	add_future_card(fc, idx, add_card);
	count = lstIdx;
      }else{
	add_card_to(ret_d, card_from_letters(str[count],str[count+1]));
	count += 2;
      }
      g_count++;
    }
  }
  free(c_name);
  if(count<5){
    fprintf(stderr, "Not enough cards");
    return NULL;
  }
  return ret_d;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  char *line = NULL;
  size_t n = 0;
  deck_t ** ret = NULL;
  while(getline(&line, &n, f)>=0){
    ret = (deck_t **)realloc(ret, (*n_hands+1)*sizeof(ret));
    lineToStr(line);
    ret[*n_hands] = hand_from_string(line, fc);
    (*n_hands)++;
  }
  free(line);
  return ret;
}
