#include "common.h"

int main(int argc, char const *argv[])
{
	if(argc<2)
	{
		printf("Erreur sur le Nomre d'arguments");
		printf("Format : %s num_port", argv[0]);
		return -1;
	}

	int sockS = socket(AF_INET , SOCK_STREAM , 0);
	if(sockS == -1)
	{
		printf("Erreur creation socket");
		return -1;
	}

	struct sockaddr_in addrS;
	memset(&addrS , 0 , sizeof(struct sockaddr_in));

	addrS.sin_family = AF_INET;
	addrS.sin_port = htons(atoi(argv[1]));
	addrS.sin_addr.s_addr = inet_addr("0.0.0.0");

	int resultat = bind(sockS , (struct sockaddr *) &addrS , sizeof(struct sockaddr_in));
	if(resultat==-1)
	{
		perror("Erreur de lancement de bind");
		return 0;
	}

	listen(sockS , 5);

	printf("En attente de connexion ...\n");

	struct sockaddr_in addrC;
	int taille  = sizeof(struct sockaddr_in);

	int sockDes = accept(sockS , (struct sockaddr *) &addrC ,&taille);
	if(sockDes == -1)
	{
		printf("Erreur d'etablissement de la connexion");
		return -1;
	}

	printf("connexion avec le client a reussi\n");

	message Mess;
	Mess.compteur = 0;

	while(1)
	{
		send(sockDes , &Mess ,  sizeof(Mess), 0);

		recv(sockDes , &Mess , sizeof(Mess) ,0);
		printf("[# Server #]  --> le client a envoyé : %d\n",Mess.compteur );

		sleep(1);
		Mess.compteur++;
	}
	

	close(sockDes);
	close(sockS);

	return 0;
}