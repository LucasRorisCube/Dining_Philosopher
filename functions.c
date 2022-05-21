#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#include "functions.h"

void monitor_Verify(int i) {
    
  if ((monitor_data.p[(i + 4) % 5] != EATING) && (monitor_data.p[i] == HUNGRY) && (monitor_data.p[(i + 1) % 5] != EATING)) {
     monitor_data.p[i] = EATING;
     sem_post(&(monitor_data.semParaComer));
  }

}

void monitor_StartEat(int i) {

  monitor_data.p[i] = HUNGRY;
  monitor_Verify(i);

}

void monitor_EndEat(int i) {

  monitor_data.p[i] = THINKING;

}

int Inicializar(){  
    int returnValue = 1;

    for(int j=0;j<5;j++)
       monitor_data.p[j] = THINKING;
    
    if(sem_init(&(monitor_data.semParaComer), 0, 1) == 0){
        returnValue = 0;
    } else {
      printf("Unable to initialize semaphore\n");
    }
    return returnValue;
}

void Destruir(){

  sem_destroy(&(monitor_data.semParaComer));
  
}

void delay(int seconds){	
	int start = clock();
	// wait n seconds
    	while (((clock()-start)/CLOCKS_PER_SEC)<seconds);         
}

void *main_filosofos(void *pid){

  int *i;
  i = (int *) pid;

  while(1){
    monitor_StartEat(*i);

    int waiting = -1;
    while(monitor_data.p[*i] != EATING) {
      
      waiting += 1;
      if(waiting > 5){

        sem_post(&(monitor_data.semParaComer));
        while(!((monitor_data.p[(*i + 4) % 5] != EATING) && (monitor_data.p[*i] == HUNGRY) && (monitor_data.p[(*i + 1) % 5] != EATING)));
        monitor_data.p[*i] = EATING;

      } else {

        sem_wait(&(monitor_data.semParaComer));
        monitor_Verify(*i);

      }
    }

    printf("Philosopher %d is eating!\n", *i + 1);
    delay(rand()%5+1);
    
    monitor_EndEat(*i);
    
    printf("Philosopher %d finished eating!\n", *i + 1);
    sem_post(&(monitor_data.semParaComer));
    delay(rand()%11+1);
  }

  pthread_exit(0);
}