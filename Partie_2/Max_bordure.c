#include<stdio.h>
#include<stdlib.h>
#include"Fonctions_graphe.h"
#include <unistd.h>

void update_color_grille(Sommet *s, Grille *g, int cl){
	ListeCase c = s->cases;
	
	while(c){
		Grille_attribue_couleur_case(g, c->i, c->j, cl);
		c = c->suiv;
	}
	return;
}

void update_color(Graphe_zone *G, Grille *g, int cl, int aff){
	
	// Changement de couleur de la Zsg si affichage
	if(aff == 1){

		Cellule_som *z = G->Zsg;
		while(z){
			update_color_grille(z->sommet, g, cl);
			z = z->suiv;
		}
	}

	// Ajout de la Bordure[cl]
	Cellule_som *b = G->Bordure->B[cl];

	while(b){
		if(b->sommet)
			b->sommet->marque = 0;	
		update_Bordure(G, b->sommet);
		if(aff == 1)
			G->Zsg = ajoute_liste_sommet(b->sommet, G->Zsg);
		b = b->suiv;
	}
	if(G->Bordure->B[cl])
		detruit_liste_sommet(&(G)->Bordure->B[cl]); // Suppression de la Bordure[cl]
	G->Bordure->taille[cl] = 0;
	
	return;
}

void update_Bordure(Graphe_zone *G, Sommet *s){

	Cellule_som *b = s->sommet_adj;
	
	while(b){
		if(b->sommet->marque == 2){
			G->Bordure->taille[b->sommet->cl] += b->sommet->nbcase_som; // MAJ de la taille de la bordure
			G->Bordure->B[b->sommet->cl] = ajoute_liste_sommet(b->sommet, G->Bordure->B[b->sommet->cl]); // On ajoute le sommet à la bordure
			b->sommet->marque = 1; // Marque d'appartenance à la bordure
		}
			b = b->suiv;
	}
	return;
}

int pick_color(Graphe_zone *G, int nbcl){
	int cl = -1;
	int taille_max = 0;	
	int i;
	
	for(i=0; i<nbcl; i++){
		if(G->Bordure->taille[i] > taille_max){
			taille_max = G->Bordure->taille[i];
			cl = i;
		}	
	}
	
	// Definit la condition victoire => Aucune bordure
	if(taille_max == 0)
		return -1;
	return cl;
}

void detruire_Bordure(Graphe_zone *G){
	free(G->Bordure->taille);
	free(G->Bordure->B);
	free(G->Bordure);
}

int max_bordure(Graphe_zone *G, Grille *g, int nbcl, int dim, int aff){

	int cpt = 0; // Nombre de tours de jeu, valeur renvoyée par la fonction
	int cl;
	cl = pick_color(G, nbcl);
	while(cl != -1){
		update_color(G, g, cl, aff);
		cpt ++;
		cl = pick_color(G, nbcl);
		if(aff == 1){
			Grille_redessine_Grille();
			sleep(1);
		}
	}
	return cpt;
}




