#ifndef functions
#define functions

#include <semaphore.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

// Define the data we need to create the monitor
struct monitor_DataType {
  sem_t semParaComer;
  int p[5]; //philosophers
};
struct monitor_DataType monitor_data; 

void *main_filosofos(void *pid);
int Inicializar();
void Destruir();

#endif