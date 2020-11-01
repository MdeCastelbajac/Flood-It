#include<stdio.h>
#include"Entete_Fonctions.h"
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

/* EXERCICE 1 */

void detruit_matrice(int **M, int dim){
	
	int i;
	for(i=0;i<dim;i++){
		free(M[i]);
	}
	free(M);
	return;
}
/* FONCTIONS DETERMINANT L'APPARTENANCE A LA ZONE, DES CASES ADJACENTES A LA CASE (i, j) */

void recherche_case_haut(int **M, int nbcase, int i, int j, int cl, int *taille, ListeCase *L){
	if(i > 0){
		if(M[i-1][j] == cl){
			trouve_zone_rec(M, nbcase, i-1, j, taille, L);
		}
	}
	return;
}

void recherche_case_bas(int **M, int nbcase, int i, int j, int cl, int *taille, ListeCase *L){
	if(i+1 < nbcase){
		if(M[i+1][j] == cl){
			trouve_zone_rec(M, nbcase, i+1, j, taille, L);
		}
	}
	return;
}

void recherche_case_gauche(int **M, int nbcase, int i, int j, int cl, int *taille, ListeCase *L){
	if(j > 0){
		if(M[i][j-1] == cl){
			trouve_zone_rec(M, nbcase, i, j-1 , taille, L);
		}
	}
	return;
}

void recherche_case_droite(int **M, int nbcase, int i, int j, int cl, int *taille, ListeCase *L){
	if(j+1 < nbcase){
		if(M[i][j+1] == cl){
			trouve_zone_rec(M, nbcase, i, j+1 , taille, L);
		}
	}
	return;
}

void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){
	
	int cl = M[i][j];
	
	/* On ajoute la case courrante à la liste */
	ajoute_en_tete(L,i,j);
	*taille = *taille + 1;
	M[i][j] = -1;
	
	/* On cherche les cases adjacentes de même couleur (aka la zone autour de (i,j))*/
	/* Aucune crainte d'ajouter les cases déjà visitées, elles sont sans couleur */
	
	recherche_case_bas(M, nbcase, i, j, cl, taille, L);
	recherche_case_gauche(M, nbcase, i, j, cl, taille, L);
	recherche_case_haut(M, nbcase, i, j, cl, taille, L);
	recherche_case_droite(M, nbcase, i, j, cl, taille, L);

	return;
}


int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){
	
	/* Choisissons une couleur aléatoire différente de celle de notre Zsg */
	int cl;
	do{
		cl = rand()%nbcl;
	}
	while(cl == M[0][0]);
	
	
	/* Déterminons notre Zsg */
	ListeCase *L = (ListeCase *)malloc(sizeof(ListeCase));
	init_liste(L);
	int taille = 0;
	
	trouve_zone_rec(M, dim, 0, 0, &taille, L);
	
	/* Condition de victoire */
	if(taille == dim * dim)
		return 0; 
	
	/* Affectons la nouvelle couleur à toutes les cases de notre Zsg */
	int i=0, j=0;
	
	/* Suppression de la liste et attribution de la couleur */
	detruit_liste(L);
	free(L);
	
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			if(M[i][j] == -1){
				M[i][j] = cl;
				if(aff == 1)
					Grille_attribue_couleur_case(G, i, j, cl);
			}
		}
	}
		
	
	/* Actualisons l'affichage */
	if(aff == 1){
		Grille_redessine_Grille();
		sleep(1);	
	}
	return 1 + sequence_aleatoire_rec(M, G, dim, nbcl, aff);
}

