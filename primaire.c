#include<stdio.h>
#include<signal.h>
#include<errno.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include"polling.h"

char *string_state;
struct  sigaction action;
int state=W_REQ;
int nb_req_rx=0;
int POLL_DELAI;
  
 // handler pour mettre a 1 nb_req_rx si la sation secondaire envoie une donné 
 void hand(int signal){
nb_req_rx=1; 
                     }// fin hand

int main(int argc, char *argv[]){
 

 // vérification que le nombre d'argument et bon
  if(argc <0){
    
    // affiche a lutilsateur comment appeler le programme 
    erreur("Erreur !!, Usage : primaire nb_polling delai_polling n pid_st1...pid_stn \n");
    exit(EXIT_FAILURE);
  }

int nb_polling=atoi(argv[1]); 
int POLL_DELAI=atoi(argv[2]);
int n=atoi(argv[3]);// nombre de sation secondaire
int numero_station;
int i;


while (nb_polling!=0){

for (numero_station=0;numero_station<n;numero_station++){

switch(state){
		case W_REQ :
			string_state=string_w_req;
			printf("Prim %s St%d %ds\n", string_state,numero_station+1,POLL_DELAI); // l'afichage qui se produit quand on est dans l'etat W_REQ
			kill(atoi(argv[numero_station+4]),POLL_TX);// la station primaire envoi linvitation a émétre 
                        signal(DATA_RX,hand); // on installe le gestionaire pour la réception de donné 
             		sleep(POLL_DELAI);//la satio primaire attend le delai_polling  
                        // testé si la sattion secondaire a envoyé une donné 
                        if (nb_req_rx==1){
                           printf("Prim %s St%d Data_Rx\n",string_state,numero_station+1);// affichage a produire en cas ou il ya reception de conné 
			   state=BC_DATA;// passage a létat ou ma primaire envois la donné a toute les station
			   
                                        }else{
                                              printf("Prim %s St%d No_Data\n",string_state,numero_station+1);// affichage si ya pas de donné recptioné 
					      state=W_REQ;
                                              break;
                                             }
		case BC_DATA :
			string_state=string_bc_data;
			printf("Prim %s St%d\n", string_state,numero_station+1);// affichage a produire dans l'etat BC_DATA
                         // la station primaire envoi la donné reçu a toute les sation secondaire apart celle qui lui a envoyé la donné 
			 for(i=0;i<n;i++)if(i!=numero_station)
                         kill(atoi(argv[i+4]),DATA_TX);
                         kill(atoi(argv[numero_station+4]),ACK_TX);// envoie de l'aquitement a la sation secondaire 
                         nb_req_rx=0; // remet le nombre de donné a 0
                         state=W_REQ; break;     

	   }// fin swith
   
  }// fin for
   nb_polling--; // décrémentation de de nb_polling
 }// fin while

exit(EXIT_SUCCESS); 
  
}// main
