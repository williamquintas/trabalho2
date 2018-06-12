#include "blur.h"
#include "imageprocessing.h"
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define WORKERS 3

int complete[WORKERS];
pthread_mutex_t lock;

void* worker(void *arguments) {
  struct arg_struct *args = (struct arg_struct *)arguments;
  int canal=0;
  while (1) {
    pthread_mutex_lock(&lock);
    while ( (complete[canal]!=0) && (canal < WORKERS)) {
      canal++;
    }
    if (canal >= WORKERS) {
      pthread_mutex_unlock(&lock);
      break;
    }
    complete[canal] = 1;
    pthread_mutex_unlock(&lock);
    for (int i = 0; i < ((args->img)->height); i++) {
      blur_line(args->img, args->filtrada, canal, i);
    }
  }
  return NULL;
}

int main(int argc, char **argv) {
  clock_t t0, t1;
  time_t tempo1, tempo2;
  imagem img;
  imagem *filtrada, *img_compartilhada, *filtrada_compartilhada;
  pthread_t workers[WORKERS];
  pid_t children[WORKERS];
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;
  char saida[255];

  img = abrir_imagem(argv[1]);
  filtrada = (imagem*) malloc(sizeof(imagem));
  (*filtrada).r = malloc(sizeof(float) * img.width * img.height);
  (*filtrada).g = malloc(sizeof(float) * img.width * img.height);
  (*filtrada).b = malloc(sizeof(float) * img.width * img.height);
  (*filtrada).width = img.width;
  (*filtrada).height = img.height;
  struct arg_struct args;
  args.img = &img;
  args.filtrada = filtrada;

  t0=clock();
  for (int i = 0; i < img.height; i++) {
    blur_line(&img, filtrada, RED, i);
    blur_line(&img, filtrada, GREEN, i);
    blur_line(&img, filtrada, BLUE, i);
  }
  t1=clock();

  printf("\nArquivo da imagem: %s\n", argv[1]);
  printf("Resolução: %dpixels x %dpixels\n", img.width, img.height);
  printf("Tamanho da matriz de convolução: 3x3\n");
  printf("Estratégia: linha de execução única\n");
  printf("Tempo gasto: %.3fms\n", 1000*(double)(t1-t0)/CLOCKS_PER_SEC);

  t0=clock();
  time(&tempo1);
  /* Disparando threads */
  for (int i=0; i<WORKERS; i++) {
    pthread_create(&(workers[i]), NULL, worker, (void*)(&args));
  }
  /* Esperando threads */
  for (int i=0; i<WORKERS; i++) {
    pthread_join(workers[i], NULL);
  }
  time(&tempo2);
  t1=clock();

  printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n");
  printf("Arquivo da imagem: %s\n", argv[1]);
  printf("Resolução: %dpixels x %dpixels\n", img.width, img.height);
  printf("Tamanho da matriz de convolução: 3x3\n");
  printf("Estratégia: threads, usando 3 threads\n");
  printf("Tempo gasto: %.3fms\n", 1000*(double)(t1-t0)/CLOCKS_PER_SEC);
  printf("Tempo gasto: %.3fms\n", difftime(tempo1,tempo2)/1000.0);

  /* Create shared memory area */
  img_compartilhada = (imagem*) mmap(NULL, sizeof(imagem), protection, visibility, 0, 0);
  filtrada_compartilhada = (imagem*) mmap(NULL, sizeof(imagem), protection, visibility, 0, 0);
  *img_compartilhada = img;
  filtrada_compartilhada = filtrada;

  t0=clock();
  for (int i=0; i<WORKERS; i++) {
    children[i] = fork();
    if (children[i] == 0) {
      for (int j = 0; j < img_compartilhada->height; j++) {
        blur_line(img_compartilhada, filtrada_compartilhada, i, j);
      }
      exit(0);
    }

    for (int j=0; j<WORKERS; j++) {
      waitpid(children[j], NULL, 0);
    }
  }
  t1=clock();
  printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n");
  printf("Arquivo da imagem: %s\n", argv[1]);
  printf("Resolução: %dpixels x %dpixels\n", img.width, img.height);
  printf("Tamanho da matriz de convolução: 3x3\n");
  printf("Estratégia: processos, usando 3 processos\n");
  printf("Tempo gasto: %.3fms\n", 1000*(double)(t1-t0)/CLOCKS_PER_SEC);

  sprintf (saida, "./results/saida%d.jpg", atoi(argv[2]));
  salvar_imagem(saida, filtrada);
  sprintf (saida, "./results/saida0%d.jpg", atoi(argv[2]));
  salvar_imagem(saida, filtrada_compartilhada);
  liberar_imagem(&img);
  liberar_imagem(filtrada);
  return 0;
}
