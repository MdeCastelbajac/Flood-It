#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Fonctions_graphe.h"
 
 
int main(int argc,char**argv){

  int dim, nbcl, nivdif, graine, aff, exo;
  Grille *g;
  int i,j;
  int **M;

  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */ 
 
	srand(time(NULL));

  if(argc!=7){
    printf("usage: %s <dimension nb_de_couleurs niveau_difficulte graine exo<5-6-7> affichage \n",argv[0]);
    return 1;
  }

  dim=atoi(argv[1]);
  nbcl=atoi(argv[2]);
  nivdif=atoi(argv[3]);
  graine=atoi(argv[4]);
  exo=atoi(argv[5]);
  aff=atoi(argv[6]);

  //Generation de l'instance 

  M=(int **) malloc(sizeof(int*)*dim);
  for (i=0;i<dim;i++){
    M[i]=(int*) malloc(sizeof(int)*dim);
    if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
  }
	
  Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);

 // Affichage de la grille 
	if(aff == 1){
 		Grille_init(dim,nbcl, 500,&g);
  	Grille_ouvre_fenetre(g);

  	for (i=0;i<dim;i++){
    	for (j=0;j<dim;j++){
      	Grille_attribue_couleur_case(g,i,j,M[i][j]);
    	}
    }
 		Grille_redessine_Grille();
 	}

 	temps_initial = clock ();
 	Graphe_zone *G = creer_graphe_zone(M, dim, nbcl);
	if(exo==5)
 		printf("%d\n", max_bordure(G, g, nbcl, dim, aff));
	
	if(exo==6)
		printf("%d\n", coin_inferieur_droit(G, g, nbcl, dim, aff));
	
	if(exo==7)
		printf("%d\n", sommet_le_plus_distant(G, g, nbcl, dim, aff));
	
	
	temps_final = clock ();
  temps_cpu = (temps_final - temps_initial) * 1e-3;
  printf("%f\n",temps_cpu);
  
  detruit_graphe(G, dim);
  if(aff==1){
  	Grille_ferme_fenetre();
  	Grille_free(&g);
	}
	
  return 0;
}
