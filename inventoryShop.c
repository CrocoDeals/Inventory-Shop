#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>

#define MAX_CAPACITE 10

struct Objet{
	char* nom;
	int prix;
	};
typedef struct Objet objet;

struct Chara{
	char* nom;
	char* profession;
	int gold;
	objet inventaire[MAX_CAPACITE];
	int tailleInventaire;
	int inventaireMax;
};
typedef struct Chara chara;

void afficherchara(chara);
void afficherInventaire(chara);
void trierInventaire(chara*, int);
void trierParNom(objet*, int);
void trierParPrix(objet*, int);
void ajouterObjet(chara*, objet);
void enleverObjet(chara*, objet);
void acheter(chara*, chara*, objet);

void color(int t,int f){
  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(H,f*16+t);
}

void afficherchara(chara chara){
	if(chara.nom == "Polo"){
		color(13,0);
		printf("\nVous etes %s, le %s\n", chara.nom, chara.profession);
		printf("Vous avez %d piece de cuivre.\n", chara.gold);
		printf("Ouverture de l'inventaire... \n");
		printf("Inventaire de %s \n", chara.nom);
		for (int i=0; i<chara.tailleInventaire; i++) {
			printf(" %d. %s %d PC\n", i+1, chara.inventaire[i].nom, chara.inventaire[i].prix);
		}
	} else if(chara.nom == "Fernand"){
		color(14,0);
		printf("Vous etes %s, le %s\n", chara.nom, chara.profession);
		printf("Vous avez %d piece de cuivre.\n", chara.gold);
		printf("Ouverture de l'inventaire... \n");
		printf("Inventaire de %s \n", chara.nom);
		for (int i=0; i<chara.tailleInventaire; i++) {
			printf(" %d. %s %d PC\n", i+1, chara.inventaire[i].nom, chara.inventaire[i].prix);
		}
	}

}

void afficherInventaire(chara chara) {
	printf("Inventaire de %s \n", chara.nom);
	for (int i=0; i<chara.tailleInventaire; i++) {
		printf(" %d. %s %d PC\n", i+1, chara.inventaire[i].nom, chara.inventaire[i].prix);
	}
}

void trierInventaire(chara* chara, int choixDeTri) {
	switch (choixDeTri) {
		case 1:
			trierParNom((*chara).inventaire, (*chara).tailleInventaire);
			break;
		case 2:
			trierParPrix((*chara).inventaire, (*chara).tailleInventaire);
			break;
		default:
			trierParNom((*chara).inventaire, (*chara).tailleInventaire);
	}
}

void trierParNom(objet* inventaire, int tailleInventaire) {
	objet echange;
	for (int j=tailleInventaire-1; j>0; j--) {
		for (int i=0; i<j; i++) {
			if (strcmp(inventaire[i].nom, inventaire[i+1].nom) > 0) {
				echange = inventaire[i];
				inventaire[i] = inventaire[i+1];
				inventaire[i+1] = echange;
			}
		}
	}
}

void trierParPrix(objet* inventaire, int tailleInventaire) {
	objet echange;
	for (int j=tailleInventaire-1; j>0; j--) {
		for (int i=0; i<j; i++) {
			if (inventaire[i].prix < inventaire[i+1].prix) {
				echange = inventaire[i];
				inventaire[i] = inventaire[i+1];
				inventaire[i+1] = echange;
			}
		}
	}
}

void ajouterObjet(chara* chara, objet objet) {
	if ((*chara).tailleInventaire < (*chara).inventaireMax) {
		(*chara).inventaire[(*chara).tailleInventaire] = objet;
		(*chara).tailleInventaire++;
		trierInventaire(chara, 1);
	}
}

void enleverObjet(chara* chara, objet objet) {
	bool removed = false;
		for (int i=0; i<(*chara).tailleInventaire; i++) {
			if (removed) {
				(*chara).inventaire[i-1] = (*chara).inventaire[i];
			} else if ( strcmp((*chara).inventaire[i].nom, objet.nom) == 0 ) {
				removed = true;
			}
		}
		if (removed) {
			(*chara).tailleInventaire--;
		}
}

void acheter(chara* acheter, chara* vendre, objet objet) {
	(*acheter).gold -= objet.prix;
	(*vendre).gold += objet.prix;
	ajouterObjet(acheter, objet);
	enleverObjet(vendre, objet);
}

int main() {
	int action = 0;

	chara joueur = {"Polo","heros",50,{{"potion", 10},{"chapeau", 1}},2,MAX_CAPACITE};
	trierInventaire(&joueur, 1);

	chara marchand = {"Fernand","marchand",1000,{{"potion", 25},{"epee", 35},{"baguette", 15},{"baton", 10},{"chaussure", 5}},5,MAX_CAPACITE};
	trierInventaire(&marchand, 2);

	do {
		afficherchara(joueur);
		printf("\n\n");

		afficherchara(marchand);
		printf("\n\n");

		printf("(1) Acheter Objet // (2) Demande d'Ajout d'objet // (0) Retour\n");
		scanf("%d\n", &action);

		// Achat d'objet
		switch (action) {
			case 1:
				do {
					if (marchand.tailleInventaire <= 0) {
						printf("%s n'a plus d'objet a vendre.\n", marchand.nom);
						action = 0;
				} else if (joueur.tailleInventaire >= joueur.inventaireMax) {
						printf("Vos poches sont pleines.\n");
						action = 0;
					} else {
						printf("Porte-Monnaie : %d PC\n", joueur.gold);
						afficherInventaire(marchand);
						printf("\nChoisissez un article a acheter en entrant son numero // (0) Retour\n");
						scanf("%d", &action);
						if (action >= 1 && action <= marchand.tailleInventaire) {
							if (joueur.gold < marchand.inventaire[action-1].prix) {
								printf("C'est beaucoup trop couteux pour vous.\n");
							} else {
								acheter(&joueur, &marchand, marchand.inventaire[action-1]);
							}
						}
					}
				} while (action != 0);
				action = -1;
				break;
			// AJOUTER
			case 2:
			while (true) {
				char newobjet_nom[32];
				int newobjet_prix;
				printf("Nombre d'article du marchant : %d\n", marchand.tailleInventaire);

				printf("Nouvel article\n Nom : ");
				scanf("%31s", &newobjet_nom);
				printf("Prix : ");
				scanf("%d", &newobjet_prix);

				objet newobjet = {newobjet_nom, newobjet_prix};
				ajouterObjet(&marchand, newobjet);
				afficherInventaire(marchand);
			}
			default:;
		}
	} while (action != 0);

	return 0;
}
