#include <stdio.h>

#include "suma.h"

Bcd extract(Bcd x, int i, int k){ // es casi exacta a la función vista en el relator, pero no se considera el largo k
  return (x << i) >> (64-k); // pues para este caso se busca extraer numeros de solo de largo 1
}

Bcd sumaBcd(Bcd x, Bcd y) {
  // Programe aca la funcion pedida
  Bcd suma = 0;
  int j = 0; // numero auxiliar para la suma
  int n = 4; // indice que indica la posición de la cifra decimal
  while(n <= 64){
    Bcd a = extract(x,64-n,4); // cifra decimal de x
    Bcd b = extract(y,64-n,4); // cifra decimal de y
    Bcd c = a + b + j; // realiza la suma
    if(c < 10){
      j = 0;
      c = c << (n - 4); // realiza desplazamiento segun el indice de cifra decimal
      suma |= c;
    }
    else{
      j = 1; // se produjo un "desborde" de la suma de base 10, se extrae el decimal correspondiente
      c = c - 10; // se trabaja solamente con el decimal de menor importancia
      c = c << (n - 4);
      suma |= c;
    }
    n = (n + 4); // se sigue con la siguiente cifra decimal
  }
  if(j != 0){ // se encuentra un desborde
    return 0xffffffffffffffff;
  }
  else {
    return suma;
  }
}