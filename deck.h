#ifndef DECK_H
#define DECK_H

/** MAX_CARTES : nombre maximum de cartes dans un paquet de cartes */
const enum { MAX_CARTES = 51 };

/** 
* structure qui contient les informations d'une carte
* lettre : lettre de la carte
* points : nombre de points que la lettre vaut
*/
struct Cartes {
	char lettre;
	int points;
};

/**
* structure qui contient les informations d'un paquet de cartes
* cartes : tableau de cartes qui contient les cartes du paquet
* taille : nombre de cartes que le paquet contient
*/
struct PaquetDeCartes {
	Cartes* cartes;
	int taille;
};

/** 
* structure qui contient les informations d'une table
* mots : tableau de char avec les mots presents sur la table
* nbMots : nombre de mots que la table contient
*/
struct Table {
	char** mots;
	int nbMots;
};

/** const qui contient les lettres du jeu et le nombre de points qu'elles valent */
const Cartes LETTRES_POINTS[] = {
	{'A', 10}, {'A', 10}, {'B', 2}, {'B', 2}, {'C', 8}, {'C', 8}, {'D', 6}, {'D', 6}, {'E', 10}, {'E', 10}, {'E', 10}, {'E', 10}, {'E', 10},
	{'F', 2}, {'G', 4}, {'G', 4}, {'H', 8}, {'H', 8}, {'I', 10}, {'I', 10}, {'I', 10}, {'I', 10}, {'J', 6}, {'K', 8}, {'L', 8}, {'L', 8},
	{'M', 8}, {'N', 8}, {'N', 8}, {'N', 8}, {'O', 8}, {'O', 8}, {'P', 8}, {'Q', 4}, {'R', 8}, {'R', 8}, {'R', 8}, {'S', 8}, {'S', 8},
	{'S', 8}, {'T', 8}, {'T', 8}, {'T', 8}, {'U', 8}, {'U', 8}, {'U', 8}, {'V', 8}, {'W', 8}, {'X', 2}, {'Y', 4}, {'Z', 2}
};
#endif DECK_H