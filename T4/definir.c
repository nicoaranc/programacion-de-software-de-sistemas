#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

int main(int argc, char *argv[]) {

  if (argc != 4){
    fprintf(stderr, "Uso: ./definir <diccionario> <llave> <definicion>\n");
    exit(1);
  }

  char *nomArch = argv[1];
  char *llave = argv[2];
  char *definicion = argv[3];
  int tamLlave = strlen(llave);
  int tamDef = strlen(definicion);

  FILE *f = fopen(nomArch, "r+");
  if (f == NULL){
    perror(nomArch);
    exit(2);
  }
  fseek(f,0,SEEK_END);
  int tamArch = ftell(f);
  int numLin = tamArch/81;
  int pos = hash_string(llave) % numLin;
  char buf[82];
  fseek(f, (pos)*81, SEEK_SET);
  while(fread(buf,1,81,f) > 0){
    char *c = buf;
    if (*c == ' '){
      while(*c == ' '){
        c++;
      }
      if (*c == '\n'){
        fseek(f,-81,SEEK_CUR);
        fwrite(llave,tamLlave,1,f);
        fputc(':',f);
        fwrite(definicion,tamDef,1,f);
        fclose(f);
        return 0;
      }
    }
    else{
      while(*c != ':'){
        c++;
      }
      *c = 0;
      if (strncmp(buf,llave,tamLlave) == 0){
        fprintf(stderr,"%s %s %s\n", "La llave", llave, "ya se encuentra en el diccionario");
        fclose(f);
        exit(3);
      }
    }
  }
  int j = 0;
  fseek(f,0,SEEK_SET);
  while(fread(buf,1,81,f) > 0 && j < pos){
    char *c = buf;
    if (*c == ' '){
      while(*c == ' '){
        c++;
      }
      if (*c == '\n'){
        fseek(f,-81,SEEK_CUR);
        fwrite(llave,tamLlave,1,f);
        fputc(':',f);
        fwrite(definicion,tamDef,1,f);
        fclose(f);
        return 0;
      }
    }
    else{
      while(*c != ':'){
        c++;
      }
      *c = 0;
      if (strncmp(buf,llave,tamLlave) == 0){
        fprintf(stderr,"%s %s %s\n", "La llave", llave, "ya se encuentra en el diccionario");
        fclose(f);
        exit(4);
      }
      j++;
    }
  }
  fprintf(stderr, "%s: el diccionario esta lleno\n", argv[1]);
  fclose(f);
  exit(5);
}
