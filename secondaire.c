#include "polling.h"
#include "header.h"

void emissionDonnee();
void invitationEmission();
void printState();
void receptionDonnee();
void requeteEmission();
void receptionAcquittement();

int n = 0, pid_primaire = 0, tab=0, nb_data_req_rx = 0;
 void emissionDonnee(){
	kill(pid_primaire, DATA_TX);
	state = W_ACK;
	string_state = string_w_ack;
}

void invitationEmission(){
	printState();
	fprintf(stdout, " Poll_Rx\n");
	state = SD_DATA;
	string_state = string_sd_data;
}

void printState(){
	int i;

	for(i=0;i<=tab;i++)
		fprintf(stdout, "\t");

	fprintf(stdout, "St%d %s", n, string_state);
}

void receptionAcquittement(){
	printState();
	if(nb_data_req_rx > 0){
		nb_data_req_rx--;
		state = W_POLL;
		string_state = string_w_poll;
	}
	if(nb_data_req_rx == 0){
		state = IDLE;
		string_state = string_idle;
	}
	fprintf(stdout, " Ack_Rx %d\n", nb_data_req_rx);
}

void receptionDonnee(int sig){
	printState();
	fprintf(stdout, " Data_rx\n");
}

void requeteEmission(){
	printState();
	if(state == IDLE){
		state = W_POLL;
		string_state = string_w_poll;
	}
	nb_data_req_rx++;
	fprintf(stdout, " Data_Req_Rx %d\n", nb_data_req_rx);
}

//station secondaire
int main (int argc,char *argv[]){
	if (argc != 3) {
		erreur("2 paramètres nécessaires");
	}

	n = atoi(argv[1]);
	pid_primaire = atoi(argv[2]);
	tab=(3*n)+1;

	
	
    state = IDLE;
    string_state = string_idle;

	for EVER{
		  if (kill(pid_primaire,0)==-1){kill(getpid(),SIGKILL);}

		switch(state){
			case IDLE:
				printState();
				fprintf(stdout, "\n");
				signal(DATA_RX, receptionDonnee);
				signal(DATA_REQ_RX, requeteEmission);
				signal(POLL_RX, SIG_IGN);
				signal(ACK_RX, SIG_IGN);
				pause();
			break;
			case W_POLL:
				printState();
				fprintf(stdout, " Attente\n");
				signal(DATA_RX, receptionDonnee);
				signal(DATA_REQ_RX, requeteEmission);
				signal(POLL_RX, invitationEmission);
				signal(ACK_RX, SIG_IGN);
				pause();
			break;
			case SD_DATA:
				printState();
				fprintf(stdout, "\n");
				signal(DATA_RX, receptionDonnee);
				signal(DATA_REQ_RX, requeteEmission);
				signal(ACK_RX, SIG_IGN);
				signal(POLL_RX, SIG_IGN);
				emissionDonnee();
			break;
			case W_ACK:
				printState();
				fprintf(stdout, "\n");
				signal(DATA_RX, receptionDonnee);
				signal(DATA_REQ_RX, requeteEmission);
				signal(ACK_RX, receptionAcquittement);
				signal(POLL_RX, SIG_IGN);
				pause();
			break;
		}
	}

	exit(1);
}


