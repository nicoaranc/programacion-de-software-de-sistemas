#include <stddef.h>

#include "prev.h"

void asignarPrev(Nodo *t, Nodo **pprev) {
  if (t == NULL){
    return;
  }
  else{
    asignarPrev(t -> izq, pprev);
    t -> prev = *pprev;
    t -> prox = NULL;
    if ((t -> prev) != NULL){
      (t -> prev) -> prox = t;
    }
    *pprev = t;
    asignarPrev(t -> der, pprev);
  }
}
