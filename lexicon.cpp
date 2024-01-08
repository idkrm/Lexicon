/**
* @file commandesTEPRC.cpp
* @brief fichier principal du programme, contient la fonction main
* @author RANDRIANARIMANANA Alicia, CHEN Priscilla
* @version 07/01/2024
*/

#include <iostream>
#include <sstream> // pour istringstream

#include "deck.h" // tout ce qui concerne le paquet de carte
#include "player.h" // tout ce qui concerne les joueurs
#include "declarerFonctions.h"
using namespace std;

/**
* @brief Recupere la premiere carte du talon pour la mettre dans le paquet expose
* @param [in, out] le paquet de cartes, le paquet expose, l'index de la premiere carte du talon
* @return la premiere carte du talon
*/
Cartes premiereCarteExposee(PaquetDeCartes* paquet, PaquetDeCartes* exposee, int &index) { // recupere la premiere carte du paquet
    
    if (exposee->taille == 1) { // si le paquet expose est vide, prendre la premiere carte du talon
        exposee->cartes[exposee->taille - 1] = paquet->cartes[index];
        exposee->taille++;
    }

    Cartes premiereCarte = exposee->cartes[exposee->taille - 2]; // recupere la premiere carte du paquet expose

    for (int i = 0; i < paquet->taille - 1; i++) // decale les cartes du talon
        paquet->cartes[i] = paquet->cartes[i + 1];
	paquet->taille--;
    
	return premiereCarte;
}

/**
* @brief Affiche la situation de la partie
* @param [in, out] la liste des joueurs, le paquet de cartes, le paquet expose
* @param [in] la table, l'index du joueur qui joue, le nombre de joueurs
*/
void situation(Joueur listeJoueurs[], PaquetDeCartes* paquet, PaquetDeCartes* exposee, Table table, int index, const int nombreDeJoueurs) { //affiche la situation de la partie
    Cartes carteExposee = premiereCarteExposee(paquet, exposee, index);
    cout << endl;
    cout << "* Joueur " << listeJoueurs[index].numJoueur;
    cout << " (" << carteExposee.lettre << ") ";

    for (int j = 0; j < listeJoueurs[index].nbCartes; j++)
        if (listeJoueurs[index].elimine == false) {
            cout << listeJoueurs[index].main[j].lettre;
        }
    cout << endl;

    if (table.nbMots > 0) {
        for (int j = 0; j < table.nbMots; j++)
            cout << j + 1 << " - " << table.mots[j] << endl;
    }
    cout << "> ";
}

/**
* @brief recupere la commande du joueur et execute le coup correspondant
* @param [in, out] le tableau des joueurs, le talon, la pile exposee, la table
* @param [in] l'index du joueur qui joue, le fichier ods4, le nombre de joueurs
*/
void coupJoueur(Joueur* listeJoueurs, PaquetDeCartes* talon, PaquetDeCartes* exposee, Table* table, int index, const char* ods4, const int nombreDeJoueurs) {
    situation(listeJoueurs, talon, exposee, *table, index, nombreDeJoueurs);

    char input[MAX_INPUT];
    cin.getline(input, MAX_INPUT);

    istringstream is(input); //convertis la chaine de caractere en flux d'entree

    char commande[MAX_MOT];
    char arg[MAX_MOT];
    char arg2[MAX_MOT];

    is >> commande;
    is >> arg;
    is >> arg2;

    int i = 0;
    switch (commande[i]) {
    case 'T':
        if (strlen(arg) != 1 || strlen(commande) != 1 || strlen(arg2) > 0)
            invalideRejoue(listeJoueurs, talon, exposee, table, index, ods4, nombreDeJoueurs);
        else
            coupT(arg[i], listeJoueurs, talon, exposee, table, index, ods4, nombreDeJoueurs);
        break;

    case 'E':
        if (strlen(arg) != 1 || strlen(commande) != 1 || strlen(arg2) > 0)
            invalideRejoue(listeJoueurs, talon, exposee, table, index, ods4, nombreDeJoueurs);
        else
            coupE(arg[i], listeJoueurs, exposee, talon, table, index, ods4, nombreDeJoueurs);
        break;

    case 'P':
        if (strlen(commande) != 1 || strlen(arg2) > 0)
            invalideRejoue(listeJoueurs, talon, exposee, table, index, ods4, nombreDeJoueurs);
        else
            coupP(arg, ods4, table, &listeJoueurs[index], nombreDeJoueurs);
        break;

    case 'R':
        if (atoi(arg) > 0 && atoi(arg) <= table->nbMots && strlen(arg2) > 0)
            coupR(&listeJoueurs[index], table, atoi(arg), arg2, ods4);
        else
            invalideRejoue(listeJoueurs, talon, exposee, table, index, ods4, nombreDeJoueurs);
        break;

    case 'C':
        if (atoi(arg) > 0 && atoi(arg) <= table->nbMots && strlen(arg2) > 0)
            coupC(table, &listeJoueurs[index], arg2, atoi(arg));
        else
            invalideRejoue(listeJoueurs, talon, exposee, table, index, ods4, nombreDeJoueurs);
        break;
    }
}

int main(int argc, const char* argv[]) {
    const char* ods4 = "ods4.txt";
    int nombreDeJoueurs = argumentsValides(argc, argv);
    int joueursEnJeu = 0, index = 0;

    Joueur* listeJoueurs = new Joueur[nombreDeJoueurs];
    PaquetDeCartes* talon = new PaquetDeCartes;
    talon->taille = MAX_CARTES;
    talon->cartes = new Cartes[talon->taille];

    PaquetDeCartes* pileExposee = new PaquetDeCartes;
    pileExposee->taille = 1;
    pileExposee->cartes = new Cartes[pileExposee->taille];

    Table* table = new Table;
    table->nbMots = 0;
    table->mots = new char* [table->nbMots];


    if (nombreDeJoueurs == 1) // si le nombre de joueur est invalide, le programme s'arrete
        return 1;

    for (int i = 0; i < nombreDeJoueurs; i++) { //initialisation du nombre de joueurs qui ne sont pas encore elimines
        if (listeJoueurs[i].elimine == false)
            joueursEnJeu++;
    }

    cout << "(Commandes valides : TEPRC)" << endl;

    int cartesDistribuees = 0;
    initialisationJeu(talon, listeJoueurs, nombreDeJoueurs);

    for (int i = 0; i < nombreDeJoueurs; i++) //initialise le nombre de points de chaque joueur a 0
        listeJoueurs[i].nbPoints = 0;


    while (joueursEnJeu > 1) { // tant qu'il reste plus d'un joueur en jeu, le jeu continue

        for (int i = 0;;i++) { // recupere l'index du joueur qui doit jouer
            if (listeJoueurs[index % nombreDeJoueurs].elimine == false) {
                index %= nombreDeJoueurs;
                break;
            }
            else index++;
        }

        if (listeJoueurs[index].nbCartes > 0) { // tant que les joueurs ont des cartes, les tours continuent
            coupJoueur(listeJoueurs, talon, pileExposee, table, index, ods4, nombreDeJoueurs);
        }

        if (listeJoueurs[index].nbCartes == 0) { // si un joueur n'a plus de cartes, le tour est fini
            cout << endl;
            cout << "Le tour est fini" << endl;
            cout << "* Scores" << endl;

            compterPoints(listeJoueurs, nombreDeJoueurs);
            eliminerJoueur(listeJoueurs, nombreDeJoueurs, joueursEnJeu);

            libererMemoire(table, pileExposee, talon, listeJoueurs, nombreDeJoueurs);
            initialisationJeu(talon, listeJoueurs, nombreDeJoueurs);
        }
        index++;
    }

    if (joueursEnJeu == 1) // s'il ne reste plus qu'un joueur en jeu, la partie est finie
        cout << "La partie est finie" << endl;

    delete[] listeJoueurs;
    delete[] talon->cartes;
    delete talon;
    delete pileExposee;
    delete table;

    return 0;
}