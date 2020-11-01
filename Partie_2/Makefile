all: Flood-It_Partie2 Test

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc -c API_Gene_instance.c

API_Grille.o: API_Grille.c API_Grille.h
	gcc -c API_Grille.c

Liste_case.o: Liste_case.c Liste_case.h
	gcc -c Liste_case.c
		
Fonctions_graphe.o: Fonctions_graphe.c Fonctions_graphe.h Liste_case.h
	gcc -c Fonctions_graphe.c

Max_bordure.o: Max_bordure.c Fonctions_graphe.c Fonctions_graphe.h 
	gcc -c Max_bordure.c

Parcours_en_largeur.o: Parcours_en_largeur.c Fonctions_graphe.h
	gcc -c Parcours_en_largeur.c
	
Flood-It_Partie2.o: Flood-It_Partie2.c
	gcc -c Flood-It_Partie2.c 

Flood-It_Partie2: Flood-It_Partie2.o Liste_case.o API_Grille.o API_Gene_instance.o Fonctions_graphe.o Max_bordure.o Parcours_en_largeur.o
	gcc -o Flood-It_Partie2 Flood-It_Partie2.o Liste_case.o API_Grille.o API_Gene_instance.o Fonctions_graphe.o Max_bordure.o Parcours_en_largeur.c -lSDL

Test.o: Test.c
	gcc -c Test.c

Test: Test.o Liste_case.o API_Grille.o API_Gene_instance.o Fonctions_graphe.o Max_bordure.o Parcours_en_largeur.o
	gcc -o Test Test.o Liste_case.o API_Grille.o API_Gene_instance.o Fonctions_graphe.o Max_bordure.o Parcours_en_largeur.c -lSDL

clean:
	rm -f *.o Flood-It_Partie2 Test
