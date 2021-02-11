// Online C compiler to run C program online
#include <stdio.h>
#include "station.h"
#include <stdlib.h>
#include <stdbool.h>  

#define N_MESURE 20
#define TAILLE_MAX 100 // 

float moyenne(float x, float y){
    return (x+y)/2;
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


void mode_defaillance(){

    
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

float tableauValeur1[20];
float tableauValeur2[20];
float tableauValeur3[20];


void lecture_fichier1(){
    FILE* fichier1 = NULL; 
    fichier1 = fopen("capteur1.txt", "r");
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX

    if (fichier1 != NULL)
    {   int x=0;
        while (x<20){
            fgets(chaine, TAILLE_MAX, fichier1); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
            tableauValeur1[x] = atof(chaine);
            //printf("%s", chaine); // On affiche la chaîne
            x++;
        }
            fclose(fichier1);


    }
}

void lecture_fichier2(){  
    char chaine[TAILLE_MAX] = "";
    FILE* fichier2 = NULL;  
    fichier2 = fopen("capteur2.txt", "r");
    if (fichier2 != NULL)
    {   int x=0;
        while (x<20){
            fgets(chaine, TAILLE_MAX, fichier2); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
            tableauValeur2[x] = atof(chaine);
            //printf("%s", chaine); // On affiche la chaîne
            x++;
        }
            fclose(fichier2);


    }
}

void lecture_fichier3(){
    char chaine[TAILLE_MAX] = "";
    FILE* fichier3 = NULL;    
    fichier3 = fopen("capteur3.txt", "r");
    if (fichier3 != NULL)
    {   int x=0;
        while (x<20){
            fgets(chaine, TAILLE_MAX, fichier3); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
            tableauValeur3[x] = atof(chaine);
            //printf("%s", chaine); // On affiche la chaîne
            x++;
        }
            fclose(fichier3);


    }


}
 int main(int argc, char *argv[])
{
    lecture_fichier1();
    lecture_fichier2();
    lecture_fichier3();

    
    FILE* fresults = NULL;
    float temp[N_MESURE];
    fresults = fopen("results.txt", "w");
 
    
        for(int k=0;k<N_MESURE;k++){

    	        float a= tableauValeur1[k];
    	        float b= tableauValeur2[k];
    	        float c= tableauValeur3[k];

                printf("la valeur de k: %d \t",k);

                printf("a= %f    b= %f     c= %f \n",a,b,c);

    		    if (nb_valeurs_aberrantes(a,b,c)==0){
    		    	fprintf(fresults, "Aquisition %d --> \t %f\n ",k,(a+b+c)/3 );
    		    	temp[k]=(a+b+c)/3;
    		  	}
        		else if (nb_valeurs_aberrantes(a,b,c)==1){
        		    	if(a/moyenne(c,b)<=0.7 || a/moyenne(c,b)>=1.3){
        			    	fprintf(fresults, "Aaquisition %d --> \t %f\n ",k,moyenne(b,c) );
        		      		temp[k]=moyenne(b,c);
        		    	}
        		    	else if (b/moyenne(a,c)<=0.7 || b/moyenne(a,c)>=1.3){
        		      		fprintf(fresults, "Aquisition %d --> \t %f\n ",k,moyenne(a,c) );
        		      		temp[k]=moyenne(a,c);
        		    	}
        		    	else if (c/moyenne(a,b)<=0.7 || c/moyenne(a,b)>=1.3){
        		    		fprintf(fresults, "Aquisition %d -->\t %f\n ",k,moyenne(a,b) );
        		      		temp[k]=moyenne(a,b);
        		    	}
    		  	}
    		  	else if (nb_valeurs_aberrantes(a,b,c)==2){
    		  		fprintf(fresults, "Aquisition %d --> Les valeurs sont abérantes. \n ",k);
    		  	}
    		  	else if(detection_pic(temp,40)==-1){
                    fprintf(fresults, "detection pic \n");
    		  	}
    			else{
                    fprintf(fresults, "detection pic bisousss");   
    			}
            
		}
    fclose(fresults);
    return 0;
    /*printf("Les valeurs du tableau 1: \n");
    for ( int j=0; j<20;j++){
        printf("%f \n",tableauValeur1[j]);    
    }
   printf("Les valeurs du tableau 2:  \n");
    for ( int j=0; j<20;j++){
        printf("%f \n",tableauValeur2[j]);    
    }


    printf("Les valeurs du tableau 3:  \n");
    for ( int j=0; j<20;j++){
        printf("%f \n",tableauValeur3[j]);    
    }
*/
}


