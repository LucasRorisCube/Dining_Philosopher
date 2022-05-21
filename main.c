#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "functions.h"

int main() {

  if(Inicializar() == 0){
    printf("Inicializando o programa...\n");
     
    pthread_t filosofos[5];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    int pids[] = {0, 1, 2, 3, 4, 5};

    for(int i = 0 ; i < 5 ; i++){
      pthread_create(&filosofos[i], &attr, main_filosofos, (void*) &(pids[i]));
    }

    for(int i = 0 ; i < 5 ; i++){
      pthread_join(filosofos[i],NULL);
    }
    
    Destruir();
   }

  return 0;
}