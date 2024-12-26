#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include <fcntl.h>
#include<stdlib.h>

sem_t mutex1;
sem_t mutex2;
int m1=0,m2=0;
int b=0;
int n;
int s=0;

void *incre(void *args)
{
	while(1)
	{
		if(m1==0)
		{
			sem_wait(&mutex1);
			m1=1;
		}


		b++;
		printf("%d  %d \n", s , b);

		if(b==n)
		{
			sem_post(&mutex2);
			m1=0;
		}
		s++;
	}
}

void *decre(void *args)
{
	while(1)
	{
		if (m2==0)
		{
			sem_wait(&mutex2);
			m2=1;
		}

		b--;
		printf("%d  %d \n", s , b);

		if (b==-n)
		{
			sem_post(&mutex1);
			m2=0;
		}
		s++;
	}
}

int main(int argc, char* argv[])
{	
	n=atoi(argv[1]);
	
	pthread_t maThread1,maThread2;
	

	sem_init(&mutex1,0,1);
	sem_init(&mutex2,0,0);

	pthread_create(&maThread1,NULL,incre,NULL);
	pthread_create(&maThread2,NULL,decre,NULL);
	
	pthread_join(maThread1, NULL);
	pthread_join(maThread2, NULL);

	return 0;
}
