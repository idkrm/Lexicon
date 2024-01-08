/**
* @file finDeJeu.cpp
* @brief compte les points, elimine les joueurs et libere la mémoire en fin de manche
* @author RANDRIANARIMANANA Alicia, CHEN Priscilla
* @version 07/01/2024
*/

#include <iostream>

#include "deck.h" // tout ce qui concerne le paquet de carte
#include "player.h" // tout ce qui concerne les joueurs
using namespace std;

/**
* @brief Compte les points de chaque joueur
* @param [in, out] tableau des joueurs
* @param [in] le nombre de joueurs
*/
void compterPoints(Joueur* joueur, const int nombreDeJoueurs) {
    for (int i = 0; i < nombreDeJoueurs; i++) {
        for (int j = 0; j < joueur[i].nbCartes; j++) {
            if (joueur[i].elimine == false) {
                joueur[i].nbPoints += joueur[i].main[j].points;
            }
        }
        if (joueur[i].elimine == false)
            cout << "Joueur " << joueur[i].numJoueur << " : " << joueur[i].nbPoints << " points" << endl;
    }
}

/**
* @brief Elimine les joueurs qui ont atteint 100 points
* @param [in, out] tableau des joueurs, le nombre de joueurs en jeu
* @param [in] le nombre de joueurs
*/
void eliminerJoueur(Joueur* listeJoueurs, const int nombreDeJoueurs, int& joueursEnJeu) { // elimine un joueur de la liste de joueur
    for (int i = 0; i < nombreDeJoueurs; i++) {
        if (listeJoueurs[i].nbPoints >= 100 && listeJoueurs[i].elimine == false) {
            listeJoueurs[i].elimine = true;
            joueursEnJeu--;
        }
    }
}

/**
* @brief Libere la memoire en fin de manche
* @param [in, out] la table, la pile exposee, le talon, la liste de joueurs
* @param [in] le nombre de joueurs
*/
void libererMemoire(Table*& table, PaquetDeCartes*& pileExposee, PaquetDeCartes*& talon, Joueur*& joueur, const int nombreDeJoueurs) {
    delete table;
    delete pileExposee;
    delete talon;

    table = new Table();
    table->nbMots = 0;
    table->mots = new char* [table->nbMots];

    pileExposee = new PaquetDeCartes();
    pileExposee->taille = 0;
    pileExposee->cartes = new Cartes[pileExposee->taille];

    talon = new PaquetDeCartes();
    talon->taille = MAX_CARTES;
    talon->cartes = new Cartes[talon->taille];
}