
#include <signal.h>
#include "polling.h"

int state=G_REQ;

//traffic
int main (int argc, char *argv[]){
	if(argc != 5){
		erreur("Erreur !! Usage : trafic i pid_sti delai_min_requete delai_max_requete \n");
		exit(1);
	}


	int i = atoi(argv[1]); //numero de la station secondaire
	int pid_Sti = atoi(argv[2]); // pid de la station secondaire

	
	int delai_min_requete = atoi(argv[3]); 	
	int delai_max_requete = atoi(argv[4]);	
	int delai = 0;

	if(delai_min_requete > delai_max_requete){
		perror("Le délai minimum ne doit pas dépasser le délai maximum\n");
		exit(1);
	}
	srand(i);
 for EVER{
 if (kill(pid_Sti,0)==-1){kill(getpid(),SIGKILL);}
switch (state){
	case G_REQ :
                
		delai = rand()%(delai_max_requete - delai_min_requete)+delai_min_requete;
		sleep(delai);
		kill (pid_Sti, DATA_REQ_TX);
                 break;
		
	}
}
	return(EXIT_SUCCESS);
   
}
