#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N_MESURE 10

char* position(char* pos){
  return pos;
}

float moyenne(float x, float y){
    return (x+y)/2;
}
void mode_defaillance(){
  //Attente d'une commande du centre
}
// La commande envoyee depuis le centre qui doit etre executee par le controleur:
char* centre_commande(char* commande,int frequence){

}
int detection_pic(float tab[N_MESURE], float val){

    float moy = 0.0;

    for (int k=0;k<N_MESURE;k++){
        moy=moy+tab[k];
    }
    moy = moy/N_MESURE;//Essayer de changer N_MESURE en 10.0 si ca marche pas

    if (val/moy<=0.5 || val/moy>=1.5)
        //printf("Pic de polution atteint ! \n");
        return -1;
    else
        //printf("pic NON atteint ! \n");
        return 0;
}
int nb_valeurs_aberrantes (float a, float b, float c){
  //Aucune valeur aberrante:
  bool notabe = (c/moyenne(a,b)>0.7 && c/moyenne(a,b)<1.3) && (a/moyenne(c,b)>0.7 && a/moyenne(c,b)<1.3) && (b/moyenne(a,c)>0.7 && b/moyenne(a,c)<1.3);
  //Une SEULE valeur aberrante:
  bool abe1 = (c/moyenne(a,b)<=0.7 || c/moyenne(a,b)>=1.3) && (a/moyenne(c,b)>0.7 && a/moyenne(c,b)<1.3) && (b/moyenne(a,c)>0.7 && b/moyenne(a,c)<1.3)
  || (a/moyenne(c,b)<=0.7 || a/moyenne(c,b)>=1.3) && (c/moyenne(a,b)>0.7 && c/moyenne(a,b)<1.3) && (b/moyenne(a,c)>0.7 && b/moyenne(a,c)<1.3)
  || (b/moyenne(a,c)<=0.7 || b/moyenne(a,c)>=1.3) && (a/moyenne(c,b)>0.7 && a/moyenne(c,b)<1.3) && (c/moyenne(a,b)>0.7 && c/moyenne(a,b)<1.3);
  //Toutes les valeurs sont aberrantes:
  bool allabe = (c/moyenne(a,b)<=0.7 || c/moyenne(a,b)>=1.3) && (a/moyenne(c,b)<=0.7 || a/moyenne(c,b)>=1.3) && (b/moyenne(a,c)<=0.7 || b/moyenne(a,c)>=1.3);

    if (notabe){
      return 0;// 0 valeur aberrante
    }
    else if (abe1){
      return 1;// 1 valeur aberrante
    }
    else if (allabe){
      return 2;// Toutes les valeurs sont aberrantes
    }
    else{
      return -1;//Nothing done
    }
}
float temp[N_MESURE] = {20,20,20,20,20,20,20,20,20,20};
float controlleur(float a, float b, float c){

  if (nb_valeurs_aberrantes(a,b,c)==0){
    return (a+b+c)/3;
  }
  else if (nb_valeurs_aberrantes(a,b,c)==1){
    if(a/moyenne(c,b)<=0.7 || a/moyenne(c,b)>=1.3){
      return moyenne(b,c);
    }
    else if (b/moyenne(a,c)<=0.7 || b/moyenne(a,c)>=1.3){
      return moyenne(a,c);
    }
    else if (c/moyenne(a,b)<=0.7 || c/moyenne(a,b)>=1.3){
      return moyenne(a,b);
    }
  }
  else if (nb_valeurs_aberrantes(a,b,c)==2){
    return -200.0;//Faut refaire les mesures
  }
  else if(detection_pic(temp,40)==-1){
    return -100.0;//mode pic de pollution
  }
  else{
    return 1000.0;//Nothing done
  }
}




int oldmain() {

   //float savedVal[];

   bool mode_defaillance=false;

   int x=0;


   while (!mode_defaillance){
       float a,b,c;

       printf("entrez les 3 valeurs d'un type de capteur \n");
       scanf("%f%f%f",&a,&b,&c);

       printf("le r�sulatat du test d'ab�rance: %d \n",nb_valeurs_aberrantes(a,b,c));

       if (nb_valeurs_aberrantes(a,b,c)==-1){
           x--;
       }
       else
            x=0;

       if (x==-2){
           mode_defaillance=true;
           printf("Passage en Mode D�faillance, attendre le centre de commande \n ");
       }
  }
  return 0;
}
