#include<stdio.h>
#include<stdlib.h>
#include"Fonctions_graphe.h"
#include <unistd.h>

/*    6.1

Posons ceci : il existe un plus court chemin en nombre d'arrête (ie. d'ajacences) 
entre le sommet de départ (contenant la case supérieure gauche) et le sommet 
contenant la case inférieure droite.

Mais notons également que chaque sommet possède une couleur (champs cl).

Ainsi pouvons-nous extrapoler une séquence de couleur, d'une séquence de sommets.

De plus, pour chaque couleur de cette séquence, le sommet correspondant se trouve 
nécessairement dans la bordure de la Zsg, et sera donc ajouté à la Zsg par la fonction 
"update_color(Graphe_zone *G, int cl);".

Enfin, une fois la séquence de couleur effectuée, le sommet d'arrivée contenant la case 
inférieure droite fait partie de la Zsg.

*/
void ajouter_fin(Cellule_som **c, Sommet *s){
	Cellule_som *new = (Cellule_som *)malloc(sizeof(Cellule_som));
	new->sommet =s;
	new->suiv = NULL;
	
	if(c == NULL){
		(*c) = new;
		return;
	}
	Cellule_som *curr = *c;
	while(curr->suiv){
		curr = curr->suiv;
	}
	curr->suiv = new;
}


Sommet *parcours_en_largeur(Graphe_zone *G, int dim){
	
	// Dans un premier temps, on parcourera le graphe en largeur
	// puis on retournera un tableau de taille distance_max, répertoriant la suite de couleur
	Sommet *s_res = NULL;
	Cellule_som *c = NULL;
	Sommet *s = NULL;
	G->mat[0][0]->distance = 0;
	G->mat[0][0]->visite = 1;
	
	Cellule_som *F = NULL; 
	F = ajoute_liste_sommet(G->mat[0][0], F);
	int distance_max = 0;
	
	while(F){		
		s = F->sommet;
		c = s->sommet_adj;
		while(c){	
			if(c->sommet->visite == 0){
				ajouter_fin(&F, c->sommet);	
				c->sommet->distance = s->distance + 1;
				
				if(c->sommet->distance > distance_max){
					distance_max = c->sommet->distance;
					s_res = c->sommet;
				}				
				c->sommet->pere = s;
				c->sommet->visite = 1;
			}		
			c = c->suiv;
		}
		F = F->suiv;
	}
	detruit_liste_sommet(&F);
	return s_res;
}

int *plus_court_chemin(Sommet *s){

	int *sequence = (int *)malloc((s->distance) * sizeof(int));
	Sommet *s_prime = s;
	int i = s_prime->distance - 1;	
	while(s_prime->marque != 0){
		sequence[i] = s_prime->cl;
		s_prime = s_prime->pere;
		i--;
	}
	while(i >= 0){
		sequence[i]=-1;
		i--;
	}
	return sequence;
}


int sequence_couleurs(Graphe_zone* G, Grille *g, int nbcl, int dim, Sommet *s, int aff){
	
	if(s->marque == 0)
		return 0;
	
	
	int *sequence = plus_court_chemin(s);//////////
	int i;
	int cpt = 0;

	for(i=0; i<(s->distance); i++){

		if(sequence[i] != -1){
			update_color(G, g, sequence[i], aff);
			if(aff == 1){
			Grille_redessine_Grille();
			sleep(1);
			}
			cpt++;
		}
	}
	free(sequence);
	
	return i;
}

int coin_inferieur_droit(Graphe_zone* G, Grille *g, int nbcl, int dim, int aff){
	Sommet *s = NULL;
	s = parcours_en_largeur(G, dim);
	return sequence_couleurs(G, g, nbcl, dim, G->mat[dim-1][dim-1], aff) + max_bordure(G, g, nbcl, dim, aff);
}

/*BONUS*/
/*On cherche le sommet le plus éloigné, puis on effectue les stratégies précédentes*/
/* Pour cela on change légèrement la fonction parcours en largeur qui renverra une liste de sommet par trié par distance decroissante*/
int sommet_le_plus_distant(Graphe_zone* G, Grille *g, int nbcl, int dim, int aff){
	Sommet *s = NULL;
	int cpt = 0;
	s = parcours_en_largeur(G, dim);

	return sequence_couleurs(G, g, nbcl, dim, s, aff) + max_bordure(G, g, nbcl, dim, aff);
}
 





