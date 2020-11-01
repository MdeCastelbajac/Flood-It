#include"Liste_case.h"
#include"API_Grille.h"


typedef struct sommet Sommet;
typedef struct cellule_som{
	Sommet *sommet;
	struct cellule_som *suiv;
} Cellule_som;

struct sommet{
	int num;
	int cl;
	ListeCase cases;
	int nbcase_som;
	Cellule_som *sommet_adj;
	
	// Max-Bordure
	int marque;
	
	// Parcours en largeur
	int distance;
	Sommet *pere;
	int visite;
};

typedef struct bordure_graphe{
	int *taille; // taille de chaque liste de sommets
	Cellule_som **B; // Tableau de listes de sommets
} Bordure_graphe;

typedef struct graphe_zone{
	int nbsom;
	Cellule_som *som;  
	Sommet ***mat;
	Cellule_som *Zsg; // Pour l'affichage uniquement
	Bordure_graphe *Bordure;
} Graphe_zone;



int estDansGrille(int dim, int i, int j); // vérifie que la case (i,j) est dans la grille

Bordure_graphe *creer_bordure(Graphe_zone *G, int nbcl); // génère la bordure du nouveau graphe

void affiche_graphe(Graphe_zone *G, int dim); // Affiche le graphe dans le terminal

Sommet *creer_sommet(int num, int cl); // Alloue la mémoire d'un nouveau sommet

Cellule_som *ajoute_liste_sommet(Sommet *s, Cellule_som *cell_som); // Ajoute un sommet à une liste de sommets

void detruit_liste_sommet(Cellule_som **cell_som); // Libère la mémoire d'une liste de sommets.
// !!! Ne supprime aucun sommet

void ajoute_voisin(Sommet *s1, Sommet *s2); // Ajoute chaque sommet dans la liste d'adjacence de l'autre

int adjacent(Sommet *s1, Sommet *s2); // Prédicat d'adjacence des deux sommets

void sommet_voisin(Graphe_zone *G, int dim, int i, int j, Sommet *s); // Vérifie que le sommet de la case(i,j) et le sommet S sont voisins, si adjacents, appelle ajoute_voisin
void detruit_matrice(int **M, int dim);// detruit la matrice


// trouve_zone permettant d'effectuer les opérations spécifiques aux graphes
void trouve_zone_graphe(Graphe_zone *G, Sommet *S, int **M, int dim, int *taille, int i, int j, ListeCase *L);
// Permet d'agréger au sommet une case adjacente
void caseAdjacenteGraphe(Graphe_zone *G, Sommet *S, int **M, int dim, int *taille, int cl, int i, int j, ListeCase *L);
// Algorithme de création des sommets qui utilise les fonctions ci-dessus
void creer_sommets_graphe(Graphe_zone *G, int **M, int dim);
// Algorithme de création du graphe qui utilise les algorithmes et fonctions ci-dessus
Graphe_zone *creer_graphe_zone(int **M, int dim, int nbcl);
void detruit_graphe(Graphe_zone *G, int dim);//detruit le graphe

void affiche_graphe2(Graphe_zone *G);


/* STRATEGIE MAX-BORDURE */
void update_color_grille(Sommet *s, Grille *g, int cl); // Affichage de la grille

void update_color(Graphe_zone *G, Grille *g, int cl, int aff); // MAJ de la couleur de la nouvelle Zsg et assimilation de la bordure

void update_Bordure(Graphe_zone *G, Sommet *s); // MAJ de la Bordure à partir d'un sommet

int pick_color(Graphe_zone *G, int nbcl); // Renvoie la couleur la plus représentée dans la bordure, si la bordure est vide, renvoie -1 et signe la fin de la partie.

void detruire_Bordure(Graphe_zone *G); // Supprime la Bordure

int max_bordure(Graphe_zone *G, Grille *g, int nbcl, int dim, int aff); // Algorithme de Résolution du jeu selon la stratégie de Max-Bordure : renvoye le nombre de tours de jeu.


/* STRATEGIE PARCOURS EN LARGEUR */
void ajouter_fin(Cellule_som **f, Sommet *s); // ajoute en fin de liste
Sommet *parcours_en_largeur(Graphe_zone *G, int dim); // parcours le graphe en largeur en attribuant un sommet père à chaque sommet selon le plus court chemin à la racine (aka le sommet supérieur droit), retourne le sommet le plus distant
int *plus_court_chemin(Sommet *s); // Renvoie la séquence de couleur nécéssaire à l'inondation du sommet s selon le plus court chemin
int sequence_couleurs(Graphe_zone* G, Grille *g, int nbcl, int dim, Sommet *s, int aff); // renvoie la sequence de couleur nécessaire à l'inondation d'un sommet s
int coin_inferieur_droit(Graphe_zone* G, Grille *g, int nbcl, int dim, int aff);// Algorithme de résolution du jeu selon la stratégie d'inondation du coin inférieur droit selon le plus court chemin.


/* STRATEGIE BONUS */

int sommet_le_plus_distant(Graphe_zone* G, Grille *g, int nbcl, int dim, int aff);// effectue la sequence de couleur nécessaire à inonder le sommet le plus distant
