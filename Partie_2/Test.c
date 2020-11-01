#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Fonctions_graphe.h"
 
// test 1
#define NbclMax 101
#define NbclFixe 10
#define PasNbcl 10
// test 2
#define DimMax 1001
#define DimFixe 10
#define PasDim 100

// test 3
#define DiffFixe 33
#define DiffMax 31
#define PasDiff 5
#define DimFixeGrand 500

int main(int argc,char**argv){

  int nbcl, test, graine, aff, exo, dim, diff;
  Grille *g = NULL;
  int i,j;
  int **M;
	Graphe_zone *G;
	
  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */ 
 
	srand(time(NULL));  
  if(argc!=3){
    printf("usage: %s <exo 5-6-7> <test 1-2-3>\n",argv[0]);
    return 1;
  }
  
  exo=atoi(argv[1]);
  test=atoi(argv[2]);
	aff = 0;
	graine = 0;
	
	// Variations de DIM
	if(test == 1){
		nbcl = NbclFixe;
		diff = DiffFixe;
		int cpt = 10;
		while(cpt < DimMax){
			
			M=(int **) malloc(sizeof(int*)*cpt);
			
			for (i=0;i<cpt;i++){
				M[i]=(int*) malloc(sizeof(int)*cpt);
				if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
			}
			
			Gene_instance_genere_matrice(cpt, nbcl, diff, graine, M);
			
			G = creer_graphe_zone(M, cpt, nbcl);
			
			printf("%d\n", cpt);
			temps_initial = clock();
			if(exo==5)
				printf("%d\n", max_bordure(G, g, nbcl, cpt, aff));
		
			if(exo==6)
				printf("%d\n", coin_inferieur_droit(G, g, nbcl, cpt, aff));
			
			if(exo==7)
				printf("%d\n", sommet_le_plus_distant(G, g, nbcl, cpt, aff));
			
			temps_final = clock();
			temps_cpu = (temps_final - temps_initial) * 1e-3;
			printf("%.3f\n\n", temps_cpu);
			
			detruit_graphe(G, cpt);
			
			cpt += PasDim;
			if(cpt == 10 + PasDim)
				cpt = PasDim;
		}
	}
	
	// Variation de NBCL
	if(test == 2){

		dim = DimFixe;
		int cpt = PasNbcl;
		diff = DiffFixe;
			
		while(cpt < NbclMax){
		
			M=(int **) malloc(sizeof(int*)*dim);
			
			for (i=0;i<dim;i++){
				M[i]=(int*) malloc(sizeof(int)*dim);
				if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
			}
			
			Gene_instance_genere_matrice(dim, cpt, diff, graine, M);
			
			G = creer_graphe_zone(M, dim, cpt);
			
			printf("%d\n", cpt);
			
			temps_initial = clock();
			
			if(exo==5)
				printf("%d\n", max_bordure(G, g, cpt, dim, aff));
			
			if(exo==6)
				printf("%d\n", coin_inferieur_droit(G, g, cpt, dim, aff));
				
			if(exo==7)
				printf("%d\n", sommet_le_plus_distant(G, g, cpt, dim, aff));
			
			
			temps_final = clock();
			temps_cpu = (temps_final - temps_initial) * 1e-3;
			printf("%.3f\n\n", temps_cpu);
			
			detruit_graphe(G, dim);
			
			cpt += PasNbcl;
		}
	}
	
	// Variations de DIFF
	if(test == 3){
		dim = DimFixeGrand;
		nbcl = NbclFixe;
		int cpt = 1;
		while(cpt < DiffMax){
		
			M=(int **) malloc(sizeof(int*)*dim);
			
			for (i=0;i<dim;i++){
				M[i]=(int*) malloc(sizeof(int)*dim);
				if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
			}
			
			Gene_instance_genere_matrice(dim, nbcl, cpt, graine, M);
			
			G = creer_graphe_zone(M, dim, nbcl);
			
			printf("%d\n", cpt);
			temps_initial = clock();
			if(exo==5)
				printf("%d\n", max_bordure(G, g, nbcl, dim, aff));
		
			if(exo==6)
				printf("%d\n", coin_inferieur_droit(G, g, nbcl, dim, aff));
			
			if(exo==7)
				printf("%d\n", sommet_le_plus_distant(G, g, nbcl, dim, aff));
			
			temps_final = clock();
			temps_cpu = (temps_final - temps_initial) * 1e-3;
			printf("%.3f\n\n", temps_cpu);
			
			detruit_graphe(G, cpt);
			
			cpt += PasDiff;
			if(cpt == 1 + PasDiff)
				cpt = PasDiff;
		}
	
	}
  return 0;
}
