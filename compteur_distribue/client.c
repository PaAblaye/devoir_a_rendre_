#include "common.h"

int main(int argc, char const *argv[])
{
	if(argc<3)
	{
		printf("Erreur sur le nombre d'arguments\n");
        printf("Format : %s  adresse  num_port", argv[0]);
		return -1;
	}

	int sockC = socket(AF_INET , SOCK_STREAM , 0);
	if(sockC == -1)
	{
		printf("Erreur lors de la creation de socket");
		return -1;
	}

	struct sockaddr_in addrS ;
	memset(&addrS , 0 , sizeof(struct sockaddr_in));

	addrS.sin_family = AF_INET;
	addrS.sin_port = htons(atoi(argv[2]));
	addrS.sin_addr.s_addr = inet_addr(argv[1]);

	// connect

	int result = connect(sockC , (struct sockaddr *) &addrS , sizeof(struct sockaddr_in));
	if(result < 0)
	{
		printf("rreur de connexion");
		return -1;
	}

	//traitement 

	message Mess;

	while(1)
	{

		recv(sockC , &Mess , sizeof(Mess) ,0);
		printf("[# Client #]  --> le Server a envoyé : %d\n",Mess.compteur );

		sleep(1);
		Mess.compteur++;

		send(sockC , &Mess ,  sizeof(Mess), 0);
	}
	
	close(sockC);

	return 0;
}