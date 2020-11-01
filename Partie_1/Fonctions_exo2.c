#include<stdlib.h>
#include<stdio.h>
#include"Entete_Fonctions.h"
#include<time.h>
#include<unistd.h>
/* EXERCICE 2 */

/* Prédicat d'appartenance à la grille*/
int estDansGrille(int dim, int i, int j){
	if(i<0 || j<0 || i>=(dim) || j>=(dim))
		return 0;
	return 1;
}

/* Algorithme dérecursifié */
void trouve_zone_imp(int **M, int dim){
	

	ListeCase *L = (ListeCase *)malloc(sizeof(ListeCase));
	init_liste(L);
	ajoute_en_tete(L, 0, 0);
	int i, j;
	int cl = M[0][0];	
		
	while(test_liste_vide(L) == 0){
		enleve_en_tete(L, &i, &j);
		M[i][j] = -1;
		
		if(estDansGrille(dim, i-1, j) == 1){
			if(M[i-1][j] == cl){
				ajoute_en_tete(L, i-1, j);	
			}
		}
	
		if(estDansGrille(dim, i+1, j)==1){
			if(M[i+1][j] == cl){
				ajoute_en_tete(L, i+1, j);
			}
		}
		
		if(estDansGrille(dim, i, j-1)==1){
			if(M[i][j-1] == cl){
				ajoute_en_tete(L, i, j-1);
			}
		}
		
		if(estDansGrille(dim, i, j+1)==1){
			if(M[i][j+1] == cl){
				ajoute_en_tete(L, i, j+1);
			}
		}	
	}
	
	detruit_liste(L);
	free(L);
	return;
}



int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff){
	
	srand(time(NULL));
	int cpt = 0;
	int taille;
	int cl; 
	int i, j;
	
	
	do{
		// SELECTION DE LA COULEUR
		do{
		cl = rand()%nbcl;
		}
		while(cl == M[0][0]);
		
		// DETERMINATION DE LA ZSG  
		trouve_zone_imp(M, dim);
		taille = 0;
		for(i=0; i<dim; i++){
			for(j=0; j<dim; j++){
				if(M[i][j] == -1){
					taille++;
					M[i][j] = cl;
					if(aff == 1)
						Grille_attribue_couleur_case(G, i, j, cl);
				}
			}
		}
		// AFFICHAGE
		if(aff == 1){
			Grille_redessine_Grille();
			sleep(1);	
		}
		cpt ++;
	}
	while(taille < (dim * dim)); // CONDITION DE VICTOIRE

	return cpt;
}



