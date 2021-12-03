/*Delineare un frammento di codice in cui un processo padre crea 
N processi figli ed invia a tali processi figli un segnale. 
Ciascun processo figlio deve gestire tale segnale 
con una funzione di Signal Handler. Lo studente scelga a 
piacere il segnale da inviare ai figli (può essere sempre lo stesso o 
possono essere diversi) e la funzione di Signal Handler per gestire il 
segnale (la funzione può essere sempre la stessa o possono 
essere implementate diverse funzioni).
Il processo padre DEVE attendere la terminazione 
dei processi figli con le API opportune.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#define N 3


void sigChild (int sig){
 printf("\t\t\tSono il processo figlio n.%d e ho ricevuto il segnale SIGUSR1 dal processo padre\n",getpid());
}

int main(void){ 
  pid_t pid[N];
  int i=0;

  for (i=0; i<N; i++) {
       if ((pid[i] = fork()) < 0) {
            perror("Fork Error\n");
            exit(EXIT_FAILURE);
       }
       if (pid[i] == 0) { /* child */
           printf("\t\t\tProcesso Figlio PID=%d: ",getpid());
           printf("Aspetto che il proceso padre n.%d mi mandi un segnale \n",getppid());
           signal(SIGUSR1,sigChild); 
           pause();  
           exit(EXIT_SUCCESS);
       }
  }

  for (i=0; i<N; i++) {
        printf("Processo Padre PID=%d: premi un tasto per inviare il segnale SIGUSR1 al processo figlio con PID=%d\n",getpid(),pid[i]);
        getchar();
        kill(pid[i],SIGUSR1);
        printf("Processo Padre PID=%d: processo figlio con PID=%d, terminato !\n", getpid(), wait((int *)0)); 
  }
  exit(EXIT_SUCCESS);
}

