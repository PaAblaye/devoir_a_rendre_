#include<stdio.h>
#include<sys/socket.h>
#include<ctype.h>
#include<stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define debut  0 
#define fin  3000

int main(int argc, char const *argv[])
{
	if(argc <2)
	{
		printf("Erreur sur le nombre d'arguments \n");
		printf("format : %s adresseIP \n",argv[0]);
		return -1;
	}

	struct sockaddr_in addrS;
	memset(&addrS , 0 , sizeof(struct sockaddr_in));


	addrS.sin_addr.s_addr = inet_addr(argv[1]);
	addrS.sin_family = AF_INET ;

	int sockC;
	int x=0;
	
	printf("\nPORT          etat  \n");

	for(int i= debut ; i <= fin ; i++)
	{
		sockC = socket(AF_INET , SOCK_STREAM , 0);
		if(sockC == -1)
		{
			printf("Erreur sur la creation de la socket TCP\n");
			return -1;
		}

		addrS.sin_port = htons(i);

		int resultat = connect(sockC , (struct sockaddr *) &addrS , sizeof(struct sockaddr_in));
		if(resultat == -1)
		{
			close(sockC);
			continue;
		}
		x++;
		printf("%d          open\n", ntohs(addrS.sin_port));
		
		close(sockC);
	}
	if(x==0)
		printf("\nAucun port ouvert sur l'addresse %s\n", inet_ntoa(addrS.sin_addr));

	
	return 0;
}