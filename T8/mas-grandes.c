#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pss.h"
       
// Defina aca la estructura para guardar nombre y tamanno

typedef struct {
  char *nom;
  int tam;
} Auxiliar;

// Agregue aca las funciones y variables globales adicionales que necesite

Queue *cola;



int cmpArchivos(void *arr, int i, int j){
  Auxiliar **a = arr;
  int x = a[i] -> tam;
  int y = a[j] -> tam;
  if (x != y){
    return y - x;
  }
  else{
    char *c = a[i] -> nom;
    char *d = a[j] -> nom;
    return strcmp(c,d);
  }
}


void masGrandes(char *n){
  struct stat st_nom;
  int rc;
  rc= stat(n, &st_nom);

  if (rc!=0) {
    printf("%s no existe\n", n);
    exit(0);
  }
  if (S_ISREG(st_nom.st_mode)) {
    // Es un archivo regular
    char *copia = strdup(n);
    Auxiliar *arch = malloc(sizeof(Auxiliar));
    arch -> nom = copia;
    arch -> tam = st_nom.st_size;
    put(cola, arch);
  }
  else if (S_ISDIR(st_nom.st_mode)) {
    // Es un directorio
    DIR *dir = opendir(n);
    if (dir == NULL) {
      perror(n);
      exit(1);
    }
    for (struct dirent *entry = readdir(dir);
         entry != NULL;
         entry = readdir(dir)) {
      if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) {
        continue;
      }
      char *nom_arch= malloc(strlen(n)+strlen(entry->d_name)+2);
      strcpy(nom_arch, n);
      strcat(nom_arch, "/");
      strcat(nom_arch, entry->d_name);
      masGrandes(nom_arch);
      free(nom_arch);
      
    }
    closedir(dir);
  }
  else {
    // Podria ser un dispositivo, un link simbolico, etc.
    fprintf(stderr, "Archivo %s es de tipo desconocido\n", n);
    exit(1);
  }
}


int main(int argc, char *argv[]) {
  if (argc!=3) {
    fprintf(stderr, "uso: %s <arch|dir>\n", argv[0]);
    exit(1);
  }
  cola = makeQueue();
  masGrandes(argv[1]); 
  int largo = queueLength(cola); 
  Auxiliar *archivos[largo];   
  for (int i = 0; i < largo; i++){
    Auxiliar *archivo = get(cola);
    archivos[i] = archivo;
  }
  sortPtrArray(archivos, 0, largo - 1, cmpArchivos);
  int t = strlen(argv[2]);
  char *ptr = argv[2] + t - 1;
  int n = 0;
  int m = 1;
  while(argv[2] <= ptr){
    int num = *ptr - '0';
    num = num * m;
    n += num;
    m *= 10;
    ptr--;
  }
  int j = 0;
  while(j < n){
    char *nombre = archivos[j] -> nom;
    int tamano = archivos[j] -> tam;
    fprintf(stdout, "%s %d\n", nombre, tamano);
    j = j + 1;
  }
  for (int k = 0; k < largo; k++){
    char *nombre = archivos[k] -> nom;
    free(nombre);
    free(archivos[k]);
  }
  return 0;
}
