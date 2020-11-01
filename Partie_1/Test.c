#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Entete_Fonctions.h"
#include "Liste_case.h"
 
#define DiffFixe 33
// test 1
#define NbclMax 101
#define NbclFixe 10
#define PasNbcl 10
// test 2
#define DimMax 1001
#define DimFixe 10
#define PasDim 100

int main(int argc,char**argv){

  int nbcl, test, graine, aff, exo, dim, diff;
  Grille *g = NULL;
  int i,j;
  int **M;
	
  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */ 
 
	srand(time(NULL));  
  if(argc!=3){
    printf("usage: %s <exo 1-2-3> <test 1-2>\n",argv[0]);
    return 1;
  }
  
  exo=atoi(argv[1]);
  test=atoi(argv[2]);
	aff = 0;
	graine = 0;
	diff = DimFixe;
	
	// Variations DIM
	if(test == 1){
		nbcl = NbclFixe;
		int cpt = 10;
		while(cpt < TailleMax){
			
			M=(int **) malloc(sizeof(int*)*cpt);
			
			for (i=0;i<cpt;i++){
				M[i]=(int*) malloc(sizeof(int)*cpt);
				if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
			}
			
			Gene_instance_genere_matrice(cpt, nbcl, diff, graine, M);
			temps_initial = clock();
			printf("%d\n", cpt);
			
			if(exo==1)
				sequence_aleatoire_rec(M, g, cpt, nbcl, aff);

			if(exo==2)
				sequence_aleatoire_imp(M, g, cpt, nbcl, aff);
			
			if(exo==3)
				sequence_aleatoire_rapide(M, g, cpt, nbcl, aff);
				
			temps_final = clock();
			temps_cpu = (temps_final - temps_initial) * 1e-3;
			printf("%.3f\n\n", temps_cpu);
			
			detruit_matrice(M, cpt);
			
			cpt += PasDim;
			if(cpt == PasDim + 10)
				cpt = PasDim;
		}
	}
	
	// Variations de NBCL
	if(test == 2){
		dim = DimFixe;
		int cpt = 10;
		while(cpt < NbclMax){
			
			M=(int **) malloc(sizeof(int*)*dim);
			
			for (i=0;i<dim;i++){
				M[i]=(int*) malloc(sizeof(int)*dim);
				if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
			}
			
			Gene_instance_genere_matrice(dim, cpt, diff, graine, M);
			
			temps_initial = clock();
			printf("%d\n", cpt);
			
			if(exo==1)
				sequence_aleatoire_rec(M, g, dim, cpt, aff);

			if(exo==2)
				sequence_aleatoire_imp(M, g, dim, cpt, aff);
			
			if(exo==3)
				sequence_aleatoire_rapide(M, g, dim, cpt, aff);
				
			temps_final = clock();
			temps_cpu = (temps_final - temps_initial) * 1e-3;
			printf("%.3f\n\n", temps_cpu);
			
			detruit_matrice(M, dim);
			
			cpt += PasNbcl;
		}
	}
	
	
  return 0;
}
