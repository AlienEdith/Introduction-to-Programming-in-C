#include <stdio.h>
#include <stdlib.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  size_t size = 0;
  if(fc==NULL){
    fc = (future_cards_t *)realloc(fc, sizeof(*fc));
    fc->decks = NULL;
    fc->n_decks = 0;
  }
  if(index >= fc->n_decks){
    fc->decks = (deck_t *)realloc(fc->decks, (index+1)*sizeof(*(fc->decks)));
    size = fc->n_decks;
    fc->n_decks = index + 1;
    for(size_t i=size; i<fc->n_decks; i++){
      (fc->decks[i]).cards = (card_t **)malloc(sizeof(*(fc->decks[i].cards)));
      (fc->decks[i]).cards = NULL;
      (fc->decks[i]).n_cards = 0;
    }
  }
  size_t nw_n_cards = (fc->decks[index]).n_cards + 1;
  (fc->decks[index]).cards = (card_t **)realloc((fc->decks[index]).cards, nw_n_cards*sizeof(*(fc->decks[index].cards)));
  (fc->decks[index]).n_cards++;
  (fc->decks[index]).cards[nw_n_cards-1] = ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  if(fc==NULL){
    fprintf(stderr, "Null future cards");
  }
  if(fc->n_decks > deck->n_cards){
    fprintf(stderr, "Not enough cards in deck");
  }
  deck_t d;
  card_t *c;
  for(size_t i=0; i<fc->n_decks; i++){
    c = deck->cards[i];
    d = fc->decks[i];
    for(size_t j=0; j<d.n_cards; j++){
      (*(d.cards[j])).value = (*c).value;
      (*(d.cards[j])).suit = (*c).suit;
    }
  }
}
