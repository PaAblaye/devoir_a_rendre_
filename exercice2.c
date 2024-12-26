#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <fcntl.h>
#include <string.h>

extern char *optarg;
extern int optopt;

int **creationMatAlea(int nb)
{
	int **Mat;
	Mat=(int **)malloc(nb*sizeof(int *));
	for(int i=0;i<nb;i++)
	{
		Mat[i]=(int *)malloc(nb*sizeof(int ));
	}
	for(int i=0;i<nb;i++)
	{
		for(int j=0;j<nb;j++)
		{
			Mat[i][j]=rand()%10;
		}
	}
	return Mat;
}

void sauvegarder(int **mat,char *nomfiche, int nb , int nf)
{
	int fic;
	char textbuff[255];
	if((fic=open(nomfiche,O_WRONLY ))==-1)
	{
		printf("ouverture en lecture ou ecriture a echouee");
		return ;
	}
	if(!nf)
	{
		for(int i=0;i<nb;i++)
		{
			for(int j=0;j<nb;j++)
			{
				sprintf(textbuff, "%d", mat[i][j]);
				if(write(fic,textbuff,strlen(textbuff))==0)
				{
					printf("rien lus");
					close(fic);
					return ;
				
				}
			}
		}
	}else
	{
		for(int i=0;i<nb;i++)
		{
			for(int j=0;j<nb;j++)
			{
				if(write(fic,&mat[i][j],sizeof(int))==0)
				{
					printf("rien lus");
					close(fic);
					return ;
				
				}
			}
		}
	}
	close(fic);
}

void Afficher(char *nomfiche,int nb,int nf)
{
	int fic,a,k;
	char textbuff[255];
	if((fic=open(nomfiche,O_RDONLY ))==-1)
	{
		printf("ouverture en lecture ou ecriture a echouee");
		return ;
	}
	if(!nf)
	{
		for(int i=0;i<nb;i++)
		{
			for(int j=0;j<nb;j++)
			{
				
				if((k=read(fic,textbuff,1))==-1)
				{
					printf("rien lus dans charger");
					close(fic);
					return ;
				
				}
				a=atoi(textbuff);
				printf("%d ",a);
			}
			printf("\n");
			
		}
	}
	else{
		for(int i=0;i<nb;i++)
		{
			for(int j=0;j<nb;j++)
			{
				
				if((k=read(fic,&a,sizeof(int)))==-1)
				{
					printf("rien lus dans charger");
					close(fic);
					return ;
				
				}
				printf("%d ",a);
			}
			printf("\n");
			
		}
	}
	
	close(fic);

}

int main(int argc , char* argv[])
{
	
	if(argc!=6 && argc !=7)
	{
		printf("nombre d'argument insuffisant !\n");
		printf("Format : nom_prog (-c | -a) -d tailleMatrice -f nomFichier [-t | -b]!");
		return -1;
	}
	int opt,d;
	int a=0,c=0,f=0;
	char fiche[50];
	
	while((opt=getopt(argc,argv,":cad:f:"))!=-1)
	{
		switch(opt)
		{
			case 'd': d=atoi(optarg);
				break;
			case 'c' : c=1;
				break;
			case 'a' : a=1;
				break;
			case 'f': strcpy(fiche,optarg);
				break;
			case 't':f=1;
					
		}

	}
	if(c)
	{
		int** maMatrice=creationMatAlea(d);
		sauvegarder(maMatrice,fiche,d,f);
	}
	if(a)
	{
		Afficher(fiche,d,f);
	}
	
	
	
	
	
	return 0;
}
