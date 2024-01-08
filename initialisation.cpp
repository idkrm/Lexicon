/**
* @file initialisation.cpp
* @brief Initialise le debut du jeu
* @author RANDRIANARIMANANA Alicia, CHEN Priscilla
* @version 07/01/2024
*/

#include <iostream>
#include <cstdlib> //pour la fonction atoi

#include "deck.h" //tout ce qui concerne le paquet de carte
#include "player.h" //tout ce qui concerne les joueurs
using namespace std;

/**
* @brief Verifie si les arguments sont valides
* @param [in] argc Nombre d'arguments
* @param [in] argv Arguments
* @return Nombre de joueurs
*/
int argumentsValides(int argc, const char* argv[]) { 
    if (argc != 2) { // vérifie s'il manque des arguments
        cerr << "Veuillez entrer un nombre de joueur (2 a 4)" << endl;
        return 1;
    }

    int nombreDeJoueurs = atoi(argv[1]); // convertis l'argument du nombre de joueur en entier
    if (nombreDeJoueurs < 2 || nombreDeJoueurs > 4) { // vérifie si le nombre de joueur est bien entre 2 et 4
        cerr << "Veuillez entrer un nombre de joueur compris entre 2 et 4" << endl;
        return 1;
    }

    return nombreDeJoueurs;
}

/**
* @brief Melange le paquet de cartes
* @param [in, out] le paquet de cartes
* @param [in] la taille du paquet de cartes
*/
void shuffle(PaquetDeCartes* paquet, const int taille) { 
    int randomPos;
    Cartes temp;
    srand(time(NULL));

    for (int i = taille - 1; i > 0; --i) {
        randomPos = rand() % (i + 1);
        temp = paquet->cartes[i];
        paquet->cartes[i] = paquet->cartes[randomPos];
        paquet->cartes[randomPos] = temp;
    }
}

/**
* @brief Distribue 10 cartes a chaque joueur
* @param [in, out] la liste des joueurs, le paquet de cartes
* @param [in] le nombre de joueurs
*/
void distribuer(Joueur listeJoueurs[], PaquetDeCartes* paquet, const int nombreDeJoueurs) {
    int cartesDistribuees = 0;

    for (int i = 0; i < nombreDeJoueurs; ++i) //initialise le nombre de cartes de chaque joueur a 0
        listeJoueurs[i].nbCartes = 0;

    for (int j = 0; j < NB_CARTES_JOUEURS; j++) { //distribue 10 cartes a chaque joueur
        for (int i = 0; i < nombreDeJoueurs; i++) {
            listeJoueurs[i].main[j] = paquet->cartes[cartesDistribuees];
            cartesDistribuees++;
            listeJoueurs[i].nbCartes++;
        }
    }
    for (int i = 0; i < MAX_CARTES; i++) //decale les cartes du paquet de cartes
        paquet->cartes[i] = paquet->cartes[i + cartesDistribuees];
    paquet->taille -= cartesDistribuees;
}

/** 
* @brief Initialise le jeu 
* @param [in, out] le paquet de cartes, la liste de joueurs
* @param [in] le nombre de joueurs
* */
void initialisationJeu(PaquetDeCartes* paquet, Joueur listeJoueurs[], const int nombreDeJoueurs) {
    for (int i = 0; i < nombreDeJoueurs; i++) //initialisation de la liste de joueur
        listeJoueurs[i].numJoueur = i + 1;

    for (int i = 0; i < MAX_CARTES; i++) { //initialise le paquet de cartes
        paquet->cartes[i].lettre = LETTRES_POINTS[i].lettre;
        paquet->cartes[i].points = LETTRES_POINTS[i].points;
    }

    shuffle(paquet, MAX_CARTES); 
    distribuer(listeJoueurs, paquet, nombreDeJoueurs); 
}