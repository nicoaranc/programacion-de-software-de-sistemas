#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "viajante.h"

int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double viajante_par(int z[], int n, double **m, int nperm, int p) {
  // Complete esta funcion
  // Puede invocar a su version secuencial: viajante
  // Use la funcion leer para que el padre reciba la ruta del hijo.
  // Use fork() para crear p nuevos procesos.  El padre solo obtiene los
  // resultados de los procesos hijos a traves de pipes, entierra a los
  // los hijos y calcula el resultado final.
  // Despues de invocar fork() agregue: srandom(getUSecsOfDay()*getpid());
  // Esto es para que cada proceso genere secuencias de numeros aleatorios
  // diferentes.

  int pids[p];
  int infds[p];
  double minim[p];
  double minimo = -1;
  for (int i = 0; i < p; i++){
    int fds[2];
    int fd[2];
    pipe(fds); // arreglos
    pipe(fd); // minimos
    pid_t pid = fork();
    srandom(getUSecsOfDay()*getpid());
    if(pid == 0){
      close(fds[0]);
      close(fd[0]);
      int a = nperm/p;
      double b = viajante(z, n, m, a);
      write(fds[1], &z[0], (n+1)*sizeof(int));
      write(fd[1], &b, sizeof(double));
      exit(0);
    }
    else{
      close(fds[1]);
      close(fd[1]);
      infds[i] = fds[0];
      minim[i] = fd[0];
      pids[i] = pid;
    }
  }
  for (int i = 0; i < p; i++){
    double res;
    leer(minim[i], &res, sizeof(double));
    if (minimo == -1){
      minimo = res;
      leer(infds[i], &z[0], (n+1)*sizeof(int));
      close(infds[i]);
      close(minim[i]);
      waitpid(pids[i], NULL, 0);
    }
    else{
      if (minimo <= res){
        close(infds[i]);
        close(minim[i]);
        waitpid(pids[i], NULL, 0);
      }
      else{
        minimo = res;
        leer(infds[i], &z[0], (n+1)*sizeof(int));
        close(infds[i]);
        close(minim[i]);
        waitpid(pids[i], NULL, 0);
      }
    }
  }
  return minimo;
}
