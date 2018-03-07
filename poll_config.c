#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "polling.h"
#include <unistd.h>
#include <fcntl.h> 
#include<sys/stat.h> 
 
 
 
int main(int argc,char *argv[]){  
int dip1;
int i;
int pid_p,pid_s,pid_t;// variable pour créer les processus
char *tab_param[9];//tableau des paramétres a passer au primaire, seocndaire, trafic

 
   // test le nombre d''arguments
  if(argc!=9 && argc!=10 )
  erreur("Erreur !!  , Usage : poll_config pramire secondaire trafic n nb_polling delai_polling  delai_min_req delai_max_req");
  
  // test si n est dans [1,5]
  if(atoi(argv[4])<1 || atoi(argv[4])>MAX_ST)
  erreur(" le nombre de station secondaires est entre 1 et 5");
  
  // test que Delai_min_requete>0 
  if(atoi(argv[7])<1)
  erreur(" Delai_min_requete>0 ");

  // test que delai_max_requete >= delai_min_requete
  if(atoi(argv[7])>atoi(argv[8]))
  erreur(" delai_max_requete >= delai_min_requete ");

  
    // allocation dynamique pour le tableau de paramétres
    for(i=0;i<9;i++){
    tab_param[i]=malloc(20);
                    }// for
 if(argc==10){ 

   tab_param[0]="poll_config";
   strcpy(tab_param[1],argv[1]);
   strcpy(tab_param[2],argv[2]);
   strcpy(tab_param[3],argv[3]);
   strcpy(tab_param[4],argv[4]);
   strcpy(tab_param[5],argv[5]);
   strcpy(tab_param[6],argv[6]);
   strcpy(tab_param[7],argv[7]);
   strcpy(tab_param[8],argv[8]);
   tab_param[9]=NULL;
   
     dip1= open(argv[9], O_RDWR|O_CREAT|O_TRUNC,"7777"); 
     close(STDOUT_FILENO);
     dup2(dip1, STDOUT_FILENO); 
     close(dip1); 
     dup2(STDOUT_FILENO,dip1);
     close(dip1);
     execv("poll_config",tab_param);
              }// if ficher

    

    //creation de la station primaire        
    pid_p=fork(); 
    
    // test si lz station primaire n'a pas était créer 
    if (pid_p==-1){
      erreur("fork");
      exit(0);
                  } 
    // on est dans la station primaire        
    if(pid_p==0){
         
                

    /*on fait une boucle dontle nombre d'itération est égale au nombre de 
     stations  introduit dans les arguments. on commence de i=4 car 3 premiéres
     case du on les garde pour les paramétres de la station primaires et apartir
     de la 3eme case on sauvgarde des pid des station secondaire pour lrs passer
     en paramétre pour la station primaire  
    */   
    for(i=4;i<atoi(argv[4])+4;i++){ 
       
      

    //creation de la station secondaire 
    pid_s=fork();
         
    // test si la station secondaire n'a pas était créer 
    if (pid_p==-1){
      erreur("fork");
      exit(0);
                  }
    // on est dans la station secondaire 
    if(pid_s==0) {

    //creation des trafics
    pid_t=fork();
  
    // test si le trafic n'a pas était créer 
    if (pid_p==-1){
      erreur("fork");
      exit(0);
                  }
   //on est dans le trafic
   if(pid_t==0){
   
   // on rempli le tableau de paramétre pour trafic 
   tab_param[0]="trafic"; 
   sprintf(tab_param[1],"%d",i-3);
   sprintf(tab_param[2],"%d",getppid()); 
   strcpy(tab_param[3],argv[7]);
   strcpy(tab_param[4],argv[8]);
   tab_param[5]=NULL; 
    
   // on utilise iexecv(const char *path, char *const argv[]); 
   execv("trafic",tab_param); 
               }// fin if(pid_t==0)
                 
   tab_param[0]="secondaire";
   sprintf(tab_param[1],"%d",i-3);
   sprintf(tab_param[2],"%d",getppid());
   tab_param[3]=NULL; 
   execv("secondaire",tab_param);  
	               }// fin if(pid_s==0)
  
       else sprintf(tab_param[i],"%d",pid_s);// on sauvgarde les pid des stations secondaire  
  }// fin for()
   
   tab_param[0]="primaire";
   strcpy(tab_param[1],argv[5]);
   strcpy(tab_param[2],argv[6]);
   strcpy(tab_param[3],argv[4]);
   tab_param[i]=NULL;
   execv("primaire",tab_param); 
  }// fin (pid_p==0)
  
    
 wait(0);//attendre la fin du processus fils

}


