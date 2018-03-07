/*
 *
 *polling.h
 * 
 */

#ifndef EXIT_H
	#define EXIT_H
	#include <unistd.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <sys/types.h>
	#include <string.h>
#endif

#define EVER (;;)
#define MAX_ST     5// nombre maximal de station 
#define POLL_RX 	SIGUSR1  //arrivée d'une invitation à emettre des données 
#define POLL_TX 	SIGUSR1	 //envoi d'une invitation à emettre des données 
#define DATA_RX 	SIGUSR2  //RECEPTION DE DONNÉES 
#define DATA_TX		SIGUSR2  //emission de données
#define ACK_RX		SIGPIPE	 //reception acquitement de données émises
#define ACK_TX		SIGPIPE  //envoi acquittement de données émises 
#define DATA_REQ_RX 	SIGALRM  //arrivée d"une requète d'émission de données
#define DATA_REQ_TX 	SIGALRM  //envoie d'une requête d'émisson de données 

//Valeurs numériques associées aux états des automates
#define IDLE	1 //aucune données à difffuser
#define W_REQ 	2 //WAIT_REQUEST: attente d'une demande d'émission
		  // de donneées de la part de la station i
#define W_POLL 	3 //WAIT_POLL: attente d'invitation à émettre 
		  // des données de la part de la station primaire
#define W_ACK	4 //WAIT_ACK:attente d'un accquittement de données
		  // de la part de la station primaire
#define BC_DATA 5 //BROADCASTING_DATA: diffusion de données
#define SD_DATA 6 //SENDING_DATA: envoi d'une données 
#define G_REQ   7 //GENERATING_REQUEST: génération d'une requête d'envoi de donnée


//chaine de caratères associées aux états des automates
char *string_idle	= "IDLE";
char *string_g_req	= "G_REQ";
char *string_w_req 	= "W_REQ";
char *string_w_ack	= "W_ACK";
char *string_w_poll	= "W_POLL";
char *string_bc_data	= "BC_DATA";
char *string_sd_data	= "SD_DATA";


//--------------------------------------------
	void erreur (char *message) {
//--------------------------------------------
	perror(message);
	exit(EXIT_FAILURE);
}// erreur


 

