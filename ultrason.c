//librairies
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 2048

// constantes
#define TRIGGER 8// connecté sur la broche physique 3 du Raspberry
#define ECHO 9 // connecté sur la broche physique 5 du Raspberry


// prototypes de fonctions
FILE* acquisitionTemperature(int nombreAcquisition);
void socketTransmission (FILE* information);

int main(){
	// démarrage traitement
	int valeur;
	FILE * returnFile = NULL;
	
	
	printf("combien de valeur voulez vous prendre\n");
	scanf("%d", &valeur);
	
	returnFile = acquisitionTemperature(valeur);
	//socketTransmission(&returnFile);
	
}


/*
 * Fonction de mesure de température.
 * Param : nombre de mesures à effectuer
 * return : fichier avec les valeurs
 */
FILE* acquisitionTemperature(int nombreAcquisition){
	
	// variables
	// variables
	time_t debutEcho;
	time_t finEcho;
	char prenom[20], nom[20], rep[5];
	//int valeur;
	FILE* dataStock = NULL;
	char cmd[10];
	wiringPiSetup(); // initialise les broches GPIO du Raspberry Pi
	// configuration fichier
	dataStock = fopen("data.txt", "w");
	
	float distance[nombreAcquisition];
	

	//Initialisation des PINS I/O
	pinMode(TRIGGER,OUTPUT);     //TRIGGER est une sortie
	pinMode(ECHO,INPUT);        //ECHO est une entrée
	delay(1);
	
	for(int i = 0; i<nombreAcquisition; i++){
		
		digitalWrite(TRIGGER,LOW);
		digitalWrite(TRIGGER, HIGH);
		delayMicroseconds(10);
		digitalWrite(TRIGGER, LOW);
		delay(1);
		
		// Impulsion du signal ECHO & acquisition de la distance
		while(digitalRead(ECHO)==0) // émission du signal ECHO
		{
			
		}debutEcho = micros();
		while(digitalRead(ECHO)==1) // retour du signal ECHO
		{
			
		}finEcho = micros();

		//traitement et affichage de la distance
		distance[i] = (((finEcho - debutEcho)*0.0343)/2); //Calcul
		printf("la distance est de : %f cm \n", distance[i]); //Affichage 
		delay(1000); //Acquisition toute les secondes
		if(dataStock !=NULL){
			
			fprintf(dataStock, "%f\n", distance[i]); // stock dans un fichier
		} else{
			printf("fichier pas crée");
		}
	}
	
		printf("capture de la photo ..\n");
		strcpy(cmd,"sudo python photo.py"); // commande python excécute
		system(cmd);
		printf("photo prise\n");


	return dataStock;
}


/*
 * configure client TCP
 * param : fichier avec les informations
 * mode : TCP
 */
socketTransmission(FILE* information){
	
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp = information;
  //char *filename = information;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]socket non crée");
    exit(1);
  }
  printf("[+]le socket a été crée\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Problème dans le socket");
    exit(1);
  }
	printf("[+]Connecter au serveur\n");

  fp = fopen("data.txt", "r");
  if (fp == NULL) {
    perror("[-]Errreur dans la lecture du fichier");
    exit(1);
  }

  send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");
	
   printf("[+]Closing the connection.\n");
   close(sockfd);
  
}

/*
 * Envoie fichier vers le serveur
 * Param : fichier
 * return : null
 */
void send_file(FILE *fp, int sockfd){
  //int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}
