#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"

void eliminar(char *str, char *pat) {
  char *w = str;
  char *r = str;
  char *b = str;
  char *p = pat;
  char *a = pat;
  while(*r){
    if (*r == *p){
      b = r;
      while(*p){
        if (*r == 0){
          r = b;
          *w = *r;
          w++;
          r++;
          break;
        }
        if (*r != *p){
          r = b;
          *w = *r;
          w++;
          r++;
          break;
        }
        p++;
        r++;
      }
      *w = *r;
      p = a;
    }
    else{
      *w = *r;
      w++;
      r++;
    }
  }
  *w = 0; 
}

char *eliminados(char *str, char *pat){
  char *aux = malloc(strlen(str)+1);
  char *s = str;
  char *d = aux;
  while(*s){
    *d = *s;
    d++;
    s++;
  }
  *d = *s;
  char *w = aux;
  char *r = aux;
  char *b = aux;
  char *p = pat;
  char *a = pat;
  while(*r){
    if (*r == *p){
      b = r;
      while(*p){
        if (*r == 0){
          r = b;
          *w = *r;
          w++;
          r++;
          break;
        }
        if (*r != *p){
          r = b;
          *w = *r;
          w++;
          r++;
          break;
        }
        else{
          p++;
          r++;
        }
      }
      *w = *r;
      p = a;
    }
    else{
      *w = *r;
      w++;
      r++;
    }
  }
  *w = 0;
  char *res = malloc(strlen(aux)+1);
  char *f = aux;
  char *g = res;
  while(*f){
    *g = *f;
    g++;
    f++;
  }
  *g = *f;
  free(aux);
  return res;
}
