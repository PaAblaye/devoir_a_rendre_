
#include<stdio.h>
#include<sys/types.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include <stdlib.h>
#include <string.h>


void Join(int fd,char *ch)
{
	
	char textbuff[255];
	int nbwrite=0,nbread=0;

	int pt = open(ch, O_RDONLY );
	if(pt==-1)
	{
		perror("Erreur de ouverture du fichier");
		return ;
	}
	while((nbread=read(pt,textbuff,255))>0){
		nbwrite=write(fd,textbuff,strlen(textbuff));
		if(nbwrite<=0)
		{
			printf("Erreur d'ecriture");
			return ;
		}
	}
	close(pt);

}

void Split(int fd, char *taille)
{	
	char car;
	int nb=0;
	while(read(fd,&car,sizeof(char))>0) nb++;
	
	lseek(fd,0,SEEK_SET);
	int nbrPart=atoi(taille);
	nb/=nbrPart;
	char textbuff[nb] ,part[20];
	int nbwrite=0,nbread=0;
	
	if(nbrPart)
	{
		for(int i=0 ; i<nbrPart ;++i)
		{
			printf("part%d nb = %d",i,nb);
			sprintf(part,"part%d.txt",i);
			int pt = open(part, O_WRONLY | O_CREAT ,
						  		S_IRUSR 
						  		|S_IWUSR
						  		|S_IRGRP
						  		|S_IROTH );
			if(pt==-1)
			{
				perror("Erreur de ouverture du fichier");
				return ;
			}
			if((nbread=read(fd,textbuff,nb))>0){
				nbwrite=write(pt,textbuff,strlen(textbuff));
				if(nbwrite<=0)
				{
					printf("Erreur d'ecriture");
					return ;
				}
			}
			if(nbrPart==i+1)
			{
				if((nbread=read(fd,textbuff,nb))>0)
				nbwrite=write(pt,textbuff,strlen(textbuff));
			}
			close(pt);
			printf("part%d",i);
		}
	}
}

int main(int argc , char* argv[])
{
	if(argc<3)
	{
		printf("Erreur : nombre d'arguments insuffusant !");
		exit(-1);
	}
	else if(argc>3)
	{
		int fiche = open(argv[1], O_WRONLY );
		if(fiche==-1)
		{
			perror("Erreur de ouverture du fichier");
			return 0;
		}
		for(int i=2 ; i<argc ;++i)
		{
			Join(fiche,argv[i]);
			
		}
		close(fiche);
	}
	else
	{
		int fiche = open(argv[1], O_RDONLY );
		if(fiche==-1)
		{
			perror("Erreur de ouverture du fichier");
			return 0;
		}
		
		Split(fiche,argv[2]);
		
		close(fiche);
	}
	return 0;
}