#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
/*int f(const void * c, const void * d){
  if( c < d ){
    return -1;
  }else if(c > d){
    return 1;
  }je fais comme ça 
  return 0;
}
*/
heap heap_create(int k, int (*f)(const void *, const void *)) {
  if(k!=0 && f!=NULL){
    heap h=  malloc(sizeof(heap));
    if (h == NULL) {
      fprintf(stderr, "heap malloc error\n");
      return NULL;
    }
    h->array = malloc((k+1)*sizeof(void*));
    if (h->array == NULL) {
      free(h);
      fprintf(stderr, "array malloc error\n");
      return NULL;
    }
    h->n = 0;
    h->nmax = k;
    h->f = f;
    return h;
  }
  return NULL;
  
}

void heap_destroy(heap h) {
    if(h->array!=NULL){
      free(h->array);
    }
    free(h);
}

bool heap_empty(heap h) {
  return (h->n==0);
}


void echanger(heap h,int c, int g){
  void * t= h->array[c];
  h->array[c] = h->array[g];
  h->array[g]=t;
}

void reorganiseTasMontant(heap h, int indice){
  int n_pere = indice/2;
  int n_actual = indice;
  bool signal = true;
  while(n_actual !=1 && signal==true){
    int c = h->f(h->array[n_actual], h->array[n_pere]);
    if(c < 0){
      echanger(h,n_actual,n_pere);
    }else{
      signal = false;
    }
    n_actual = n_pere;
    n_pere = n_pere/2;
  }
}
/*
    void* *ptr1 = realloc(h->array, h->nmax * sizeof(void *));
    if (ptr1 == NULL) {       
      printf("\nExiting!!");
      free(h->array);
      return false;
    }else{
      h->array = ptr1;
      h->nmax *=2; 
    }
  

*/

bool heap_add(heap h, void *object) {
  if(h->n < h->nmax){
    h->n +=1;
    h->array[h->n]= object;
    reorganiseTasMontant(h, h->n);
    return false;
  }
  return true;
}

void *heap_top(heap h) {
  if (heap_empty(h)){
    return NULL;
  }else{
    return h->array[1];
  }
}



void reorganiseTasDesc(heap h, int debut){
  int g = 2*debut;
  int d = 2*debut+1;
  if(g <= h->n ){
    if(d<= h->n ){
      int c = h->f(h->array[d], h->array[g]);
      if(c < 0){
        g=d;
      }
      c= h->f(h->array[debut], h->array[g]);
      if( c > 0){
        echanger(h,debut,g);
        reorganiseTasDesc(h,g);
      }
    }else{
      int c = h->f(h->array[debut], h->array[g]);
      if(c > 0){
        echanger(h,debut,g);
      }
    }
  }
}

void *heap_pop(heap h) {
  if(heap_empty(h)){
    return NULL;
  }
  void* object = h->array[1];
  h->array[1] = h->array[h->n];
  h->array[h->n] = object;
  h->n-=1;

  reorganiseTasDesc(h, 1);
  return object;
}
