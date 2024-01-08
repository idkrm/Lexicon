#ifndef PLAYER_H
#define PLAYER_H

/**
* MAX_JOUEURS : nombre maximum de joueurs
* NB_CARTES_JOUEURS : nombre de cartes que chaque joueur recoit
* MAX_MOT : nombre maximum de lettres dans un mot (le mot le plus long possede 25 lettres)
* MAX_INPUT : nombre maximum de caracteres dans une entree
*/
const enum { MAX_JOUEURS = 4, NB_CARTES_JOUEURS = 10, MAX_MOT = 26, MAX_INPUT = 50 };


/**
* structure qui contient les informations d'un joueur
* main : tableau de cartes qui contient les cartes que le joueur a en main
* nbPoints : nombre de points que le joueur a
* numJoueur : numero du joueur
* nbCartes : nombre de cartes que le joueur a en main
* elimine : booleen qui indique si le joueur est elimine ou non
*/
struct Joueur {
	Cartes main[NB_CARTES_JOUEURS];
	int nbPoints;
	int numJoueur;
	int nbCartes;
	bool elimine = false;
};

#endif PLAYER_H