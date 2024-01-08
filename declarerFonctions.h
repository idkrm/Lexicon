#ifndef DECLARERFONCTIONS_H
#define DECLARERFONCTIONS_H

/**
* @brief Prend les arguments et execute le coup correspondant
* @param [in, out] le tableau des joueurs, le talon, la pile exposee, la table
* @param [in] l'index du joueur qui joue, le fichier ods4, le nombre de joueurs
*/ 
void coupJoueur(Joueur* listeJoueurs, PaquetDeCartes* talon, PaquetDeCartes* exposee, Table* table, int index, const char* ods4, const int nombreDeJoueurs);


/** 
* @brief Verifie si les arguments sont bons, si oui recupere le nombre de joueurs
* @param [in] argc Nombre d'arguments
* @param [in] argv Arguments
* @return Nombre de joueurs
*/ 
int argumentsValides(int argc, const char* argv[]);


/**
* @brief Initialise le jeu en melangeant le paquet de cartes et en distribuant 10 cartes a chaque joueur
* @param [in, out] le paquet de cartes, la liste de joueurs
* @param [in] le nombre de joueurs
*/
void initialisationJeu(PaquetDeCartes* paquet, Joueur listeJoueurs[], const int nombreDeJoueurs);


/**
* @brief Execute le coup T : prend une carte du talon et l'echange avec une carte du joueur qu'il pose dans la pile exposee
* @param [in, out] la liste des joueurs, le talon, la pile exposee, la table
* @param [in] l'argument de la commande, l'index du joueur qui joue, le fichier ods4, le nombre de joueurs
*/
void coupT(char arg, Joueur* joueur, PaquetDeCartes* talon, PaquetDeCartes* exposee, Table* table, int index, const char* ods4, const int nombreDeJoueurs);


/**
* @brief Execute le coup E : prend une carte de la pile exposee et l'echange avec une carte du joueur
* @param [in, out] la liste des joueurs, la pile exposee, le talon, la table
* @param [in] l'argument de la commande, l'index du joueur qui joue, le fichier ods4, le nombre de joueurs
*/
void coupE(char arg, Joueur* joueur, PaquetDeCartes* exposee, PaquetDeCartes* talon, Table* table, int index, const char* ods4, const int nombreDeJoueurs);


/**
* @brief Execute le coup P : pose un mot sur la table
* @param [in, out] la table, la liste des joueurs
* @param [in] l'argument de la commande, le fichier ods4, le nombre de joueurs
*/
void coupP(char* arg, const char* ods4, Table* table, Joueur* joueur, const int nombreDeJoueurs);


/**
* @brief Execute le coup R : remplace une ou plusieurs lettre(s) d'un mot sur la table par des lettres que le joueur a en main
* @param [in, out] la liste des joueurs, la table
* @param [in] l'argument de la commande, le fichier ods4
*/
void coupR(Joueur* joueur, Table* table, int arg, char* arg2, const char* ods4);


/**
* @brief Execute le coup C : complete un mot sur la table avec des lettres que le joueur a en main
* @param [in, out] la table, le joueur qui joue
* @param [in] l'argument de la commande, l'index du mot a completer
*/
void coupC(Table* table, Joueur* joueur, char* arg2, const int arg);


/**
* @brief Le coup est invalide, on demande au joueur de rejouer
* @param [in, out] la liste de joueurs, le talon, la pile exposee, la table
* @param [in] l'index du joueur qui joue, le fichier ods4, le nombre de joueurs
*/
void invalideRejoue(Joueur* listeJoueurs, PaquetDeCartes* talon, PaquetDeCartes* exposee, Table* table, int index, const char* ods4, const int nombreDeJoueurs);


/**
* @brief Compte les points de chaque joueur
* @param [in, out] tableau des joueurs
* @param [in] le nombre de joueurs
*/
void compterPoints(Joueur* joueur, const int nombreDeJoueurs);

/**
* @brief Elimine un joueur de la liste de joueur
* @param [in, out] tableau des joueurs
* @param [in, out] le nombre de joueurs en jeu
* @param [in] le nombre de joueurs
*/
void eliminerJoueur(Joueur* listeJoueurs, const int nombreDeJoueurs, int& joueursEnJeu);

/**
* @brief Libere la memoire allouee dynamiquement
* @param [in, out] la table, la pile exposee, le talon, la liste de joueurs
* @param [in] le nombre de joueurs
*/
void libererMemoire(Table*& table, PaquetDeCartes*& pileExposee, PaquetDeCartes*& talon, Joueur*& joueur, const int nombreDeJoueurs);

#endif DECLARERFONCTIONS_H