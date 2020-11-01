#include"Fonctions_graphe.h"
#include"Liste_case.h"
#include<stdlib.h>
#include<stdio.h>

int estDansGrille(int dim, int i, int j){
	if(i<0 || j<0 || i>=(dim) || j>=(dim))
		return 0;
	return 1;
}

void detruit_matrice(int **M, int dim){
	
	int i;
	for(i=0;i<dim;i++){
		free(M[i]);
	}
	free(M);
	return;
}

Bordure_graphe *creer_bordure(Graphe_zone *G, int nbcl){
	// Allocation mémoire des différent champs
	Bordure_graphe *Bordure = (Bordure_graphe *)malloc(sizeof(Bordure_graphe));
	Bordure->taille = (int *)malloc(nbcl * sizeof(int));
	int i;
	for(i=0; i<nbcl; i++)
		Bordure->taille[i] = 0;
	
	Bordure->B = (Cellule_som **)malloc(nbcl * sizeof(Cellule_som));
	
	return Bordure;
}




void affiche_graphe(Graphe_zone *G, int dim){
	/* La fonction affiche pour chaque case de la grille, le numéro du sommet auquel elle appartient*/
	int i, j;
	
	for(i=0; i<dim; i++){
		printf("\n");
		printf("|");
		for(j=0; j<dim; j++){
			printf("|%d|", (G->mat[i][j])->cl);
		}
		printf("\n");
	}
	
	return;
}

Graphe_zone *init_graphe(int dim){
	Graphe_zone *G = (Graphe_zone *)malloc(sizeof(Graphe_zone));
	G->som = NULL;
	G->nbsom = 0;
	G->Bordure = NULL;
	G->Zsg = NULL; // Pour l'affichage uniquement
	G->mat = (Sommet ***)malloc(sizeof(Sommet **)*dim);
	int i, j;
	for(i=0; i<dim; i++){
		G->mat[i] = (Sommet **)malloc(dim * sizeof(Sommet *));
		for(j=0; j<dim; j++){
			G->mat[i][j] = NULL;
		}
	}	
	return G;
}


Sommet *creer_sommet(int num, int cl){
	Sommet *s = (Sommet *)malloc(sizeof(Sommet));
	s->num = num;
	s->cl = cl;
	init_liste(&(s->cases));
	s->nbcase_som = 0;
	s->sommet_adj = NULL;
	
	// Max-Bordure
	s->marque = 2;
	
	// Parcours en Largeur
	s->distance = 1000000000;
	s->pere = NULL;
	s->visite = 0;
	return s;
}


Cellule_som *ajoute_liste_sommet(Sommet *s, Cellule_som *cell_som){
	Cellule_som *new_cell = (Cellule_som *)malloc(sizeof(Cellule_som));
	new_cell->sommet = s;
	new_cell->suiv = cell_som;
	return new_cell;
}


void detruit_liste_sommet(Cellule_som **cell_som){
	
	Cellule_som *suppr = NULL;
	while(*cell_som != NULL){
		suppr = *cell_som;
		*cell_som = (*cell_som)->suiv;
		free(suppr);
	}	
	*cell_som=NULL;
	return;
}


void ajoute_voisin(Sommet *s1, Sommet *s2){
	s1->sommet_adj = ajoute_liste_sommet(s2, s1->sommet_adj);
	s2->sommet_adj = ajoute_liste_sommet(s1, s2->sommet_adj);
	return;
}


int adjacent(Sommet *s1, Sommet *s2){
	if(s1->sommet_adj == NULL)
		return 0;
	
	Cellule_som *curr = s1->sommet_adj;
	while(curr){
		if(curr->sommet->num == s2->num)
			return 1;
		curr = curr->suiv;
	}	
	return 0;
}

void sommet_voisin(Graphe_zone *G, int dim, int i, int j, Sommet *s){
	// si la case adjacente appartient à un sommet adjacent non voisin, alors on le met à jour
	if(estDansGrille(dim, i, j)){
		if(G->mat[i][j]->num != s->num){
			if(adjacent(s, G->mat[i][j])==0)
				ajoute_voisin(s, G->mat[i][j]);
		}
	}	
	return;
}

void caseAdjacenteGraphe(Graphe_zone *G, Sommet *S, int **M, int dim, int *taille, int cl, int i, int j, ListeCase *L){

	if(estDansGrille(dim, i, j) == 1){
		if(M[i][j]==cl){		
			trouve_zone_graphe(G, S, M, dim, taille, i, j, L);
		}
	}	
	return ;
}

void trouve_zone_graphe(Graphe_zone *G, Sommet *S, int **M, int dim, int *taille, int i, int j, ListeCase *L){
	
	int cl = M[i][j];
	
	ajoute_en_tete(L,i,j);
	*taille = *taille + 1;
	M[i][j] = -1;

	
	// On gère directement l'attribution des sommets par la ligne suivante
	G->mat[i][j] = S;
	
	// Récursion
	caseAdjacenteGraphe(G, S, M, dim, taille, cl, i-1, j, L);
	caseAdjacenteGraphe(G, S, M, dim, taille, cl, i+1, j, L);
	caseAdjacenteGraphe(G, S, M, dim, taille, cl, i, j-1, L);
	caseAdjacenteGraphe(G, S, M, dim, taille, cl, i, j+1, L);
		
	return;
}


void creer_sommets_graphe(Graphe_zone *G, int **M, int dim){
	int num = 0;
	int i, j;
	for(i=0; i<dim; i++){
		for(j=0; j<dim; j++){
			if(G->mat[i][j]==NULL){
				Sommet *new_som = creer_sommet(num, M[i][j]);
				
				G->som = ajoute_liste_sommet(new_som, G->som);
				trouve_zone_graphe(G, new_som, M, dim, &new_som->nbcase_som, i, j, &new_som->cases); 	
				num ++;
				
				// On s'occupe aussi de déterminer les sommets voisins
				// Pour cela, il faut et il suffit de regarder les cases en haut et à gauche (en partant de la case haut-gauche), pour chaque case. A la terminaison, on aura déterminé toutes les adjacences de sommets possibles.
				// En effet, on n'a pas besoin de regarder les 4 cases adjacentes et de reparcourir toute la matrice.
	
				sommet_voisin(G, dim, i-1, j, new_som);
				sommet_voisin(G, dim, i, j-1, new_som);
			}
			else{
				sommet_voisin(G, dim, i-1, j, G->mat[i][j]);
				sommet_voisin(G, dim, i, j-1, G->mat[i][j]);
			}
		}
	}
	return ;
}

void detruit_graphe(Graphe_zone *G, int dim){
 int i;
 for(i=0;i<dim;i++)
  	free(G->mat[i]); 
 free(G->mat);
 
 detruit_liste_sommet(&G->Zsg);
 
 // detruire les sommets 
 Cellule_som *tmp = NULL;
 while(G->som){
  	tmp = G->som;
  	G->som = G->som->suiv;
  	detruit_liste(&tmp->sommet->cases);
  	detruit_liste_sommet(&tmp->sommet->sommet_adj);
  	free(tmp->sommet);
  	free(tmp);
 }
 detruire_Bordure(G);
 free(G);
}

Graphe_zone *creer_graphe_zone(int **M, int dim, int nbcl){
	Graphe_zone *G = init_graphe(dim);
	
	// création des sommets & attribution des sommets dans G->mat & détermination des sommets voisins
	creer_sommets_graphe(G, M, dim);
	
	
	// Creation et MAJ de la bordure
	G->Bordure = creer_bordure(G, nbcl);
	update_Bordure(G, G->mat[0][0]);
	
		
	G->mat[0][0]->marque = 0;
	// Pour l'affichage uniquement
	G->Zsg = ajoute_liste_sommet(G->mat[0][0], G->Zsg);
	
	detruit_matrice(M, dim);
	return G;
}


