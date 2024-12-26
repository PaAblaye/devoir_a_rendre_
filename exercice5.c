#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

int n;

sem_t *tabMutex;


void* unParUn(void* args)
{
	int id = *(int *) args;
	while(1){
		sem_wait(&tabMutex[id]);
		
		printf("thread numero %d \n",id + 1);
		
		sem_post(&tabMutex[(id+1)%n]);
	}
}

int main(int argc ,char* argv[])
{
	if(argc!=2)
	{
		printf("Erreur Sur Le Nombre d'argument\n");
		printf("! Format : nom_prog n(entier)\n");
		exit(-1);
	}
	
	n=atoi(argv[1]);
	tabMutex= malloc(n*sizeof(sem_t));
	pthread_t TH[n];
	
	sem_init(&tabMutex[0],0,1);
	for(int i=1 ; i<n ; i++)
	{
		sem_init(tabMutex+i,0,0);
	}
	
	for(int i=0 ; i<n ; i++)
	{
		int *val = malloc(sizeof(int));
		*val=i;
		pthread_create(TH+i,NULL,unParUn,val);
	}
	
	for(int i=1 ; i<n ; i++)
	{
		pthread_join(TH[i], NULL);
	}
	
	for(int i=0 ; i<n ; i++)
	{
		sem_destroy(tabMutex+i);
	}
	

	return 0;
}

