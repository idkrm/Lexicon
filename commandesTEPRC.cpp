/**
* @file commandesTEPRC.cpp
* @brief Toutes les fonctions utiles pour executer les commandes T, E, P, R et C
* @author RANDRIANARIMANANA Alicia, CHEN Priscilla
* @version 07/01/2024
*/

#include <iostream>
#include <fstream> // pour ifstream
#include <iomanip> // pour setw
#pragma warning(disable : 4996) // pour pouvoir utiliser strcpy

#include "deck.h" // tout ce qui concerne le paquet de carte
#include "player.h" // tout ce qui concerne les joueurs
#include "declarerFonctions.h"
using namespace std;


/**
* @brief Demande au joueur de rejouer
* @param [in, out] la liste de joueurs, le talon, la pile exposee, la table
* @param [in] l'index du joueur qui joue, le fichier ods4, le nombre de joueurs
*/
void invalideRejoue(Joueur* listeJoueurs, PaquetDeCartes* talon, PaquetDeCartes* exposee, Table* table, int index, const char* ods4, const int nombreDeJoueurs) { 
    cout << "Coup invalide, recommencez" << endl;
    coupJoueur(listeJoueurs, talon, exposee, table, index, ods4, nombreDeJoueurs);
}

/**
* @brief Execute le coup T : prend une carte du talon et l'echange avec une carte du joueur qu'il pose dans la pile exposee
* @param [in, out] la liste des joueurs, le talon, la pile exposee, la table
* @param [in] l'argument de la commande, l'index du joueur qui joue, le fichier ods4, le nombre de joueurs
*/
void coupT(char arg, Joueur* joueur, PaquetDeCartes* talon, PaquetDeCartes* exposee, Table* table, int index, const char* ods4, const int nombreDeJoueurs) {
    bool carteTrouvee = false;

    while (!carteTrouvee) {
        for (int i = 0; i < joueur[index].nbCartes; i++) {
            if (joueur[index].main[i].lettre == arg) {
                carteTrouvee = true;

                // place la carte au-dessus des cartes exposees
                exposee->cartes[exposee->taille - 1] = joueur[index].main[i];
                exposee->taille++;

                // remplace la carte par la premiere carte du talon
                joueur[index].main[i] = talon->cartes[0];
                break;
            }
        }
        if (!carteTrouvee) { // si la carte n'est pas trouvee, on demande au joueur de rejouer
            invalideRejoue(joueur, talon, exposee, table, index, ods4, nombreDeJoueurs);
            break;
        }
    }
}

/**
* @brief Execute le coup E : prend une carte de la pile exposee et l'echange avec une carte du joueur
* @param [in, out] la liste des joueurs, la pile exposee, le talon, la table
* @param [in] l'argument de la commande, l'index du joueur qui joue, le fichier ods4, le nombre de joueurs
*/
void coupE(char arg, Joueur* joueur, PaquetDeCartes* exposee, PaquetDeCartes* talon, Table* table, int index, const char* ods4, const int nombreDeJoueurs) {
    bool carteTrouvee = false;
    Cartes temp;

    while (!carteTrouvee) {
        for (int i = 0; i < joueur[index].nbCartes; i++) {
            if (joueur[index].main[i].lettre == arg) {
                carteTrouvee = true;

                temp = exposee->cartes[exposee->taille - 1];
                exposee->cartes[exposee->taille - 1] = joueur[index].main[i];
                joueur[index].main[i] = temp;
                break;
            }
        }

        if (!carteTrouvee) {
            invalideRejoue(joueur, talon, exposee, table, index, ods4, nombreDeJoueurs);
            break;
        }
    }
}

/**
* @brief Verifie si le mot est dans le fichier ods4 (qui est le dictionnaire, donc si le mot existe)
* @param [in] le mot a verifier, le fichier ods4
* @return true si le mot est dans le fichier, false sinon
*/
bool rechercheMot(const char* arg, const char* ods4) {
    bool motTrouve = false;
    char mot[MAX_MOT];

    ifstream in("ods4.txt"); // ouvre le fichier

    in >> setw(MAX_MOT) >> mot; // essaie de lire le premier mot

    while (in) {
        if (strcmp(mot, arg) == 0) // si le mot est trouve, on arrete la recherche
            motTrouve = true;

        in >> setw(MAX_MOT) >> mot; // essaie de lire le mot suivant
    }
    in.close(); // ferme le fichier

    return motTrouve;
}

/**
* @brief Verifie si le joueur a les lettres necessaires pour former le mot
* @param [in, out] le joueur qui joue
* @param [in] le mot a verifier
*/
bool atilLesLettres(const char* arg, Joueur* joueur) { // "a t-il les lettres"
    bool motValide = true;
    for (int i = 0; i < strlen(arg); i++) {
        bool lettreTrouvee = false;
        for (int k = 0; k < joueur->nbCartes; k++) {
            if (joueur->main[k].lettre == arg[i]) {
                lettreTrouvee = true;
                break;
            }
        }
        if (!lettreTrouvee) {
            joueur->nbPoints -= 3;
            motValide = false;
            cout << "Mot invalide, vous passez votre tour" << endl;
            break;
        }
    }
    return motValide;
}

/**
* @brief Supprime les lettres du mot forme de la main du joueur
* @param [in, out] le joueur qui joue
* @param [in] le mot a verifier
*/
void supprLettreCoupP(const char* arg, Joueur* joueur) {
    for (int i = 0; i < strlen(arg); i++) {
        for (int j = 0; j < joueur->nbCartes; j++) {
            if (joueur->main[j].lettre == arg[i]) {
                for (int k = j; k < joueur->nbCartes - 1; k++) {
                    joueur->main[k] = joueur->main[k + 1];
                }
                joueur->nbCartes--;
                break;
            }
        }
    }
}

/**
* @brief Execute le coup P : forme un mot avec les lettres du joueur et le pose sur la table
* @param [in, out] la table, la liste des joueurs
* @param [in] l'argument de la commande, le fichier ods4, le nombre de joueurs
*/
void coupP(char* arg, const char* ods4, Table* table, Joueur* joueur, const int nombreDeJoueurs) {
    char* nouveauMot = new char[strlen(arg) + 1];
    strcpy(nouveauMot, arg); // copie la chaîne de caractères arg dans la mémoire allouée

    if (rechercheMot(arg, ods4)) {
        // Vérifie si le joueur a les lettres nécessaires pour former le mot
        bool motValide = atilLesLettres(arg, joueur);

        if (motValide) {
            supprLettreCoupP(arg, joueur);
            table->mots[table->nbMots] = nouveauMot; // on ajoute le mot à la table
            table->nbMots++;
        }
        else
            delete[] nouveauMot;
    }
    else {
        delete[] nouveauMot;
        joueur->nbPoints += 3;
        cout << "Mot invalide, vous passez votre tour" << endl;
    }
}

/**
* @brief Verifie si le mot est valide
* @param [in, out] le mot a verifier, le mot de la table
* @return true si le mot est valide, false sinon
*/
bool coupRValideOuPas(char* arg2, char* nouveauMot) {
    bool motValide = true;

    for (int i = 0; i < strlen(arg2); i++) {
        bool lettreValide = false;
        for (int j = 0; j < strlen(nouveauMot); j++) {
            if (arg2[i] == nouveauMot[j]) {
                lettreValide = true;
                break;
            }
        }
        if (!lettreValide) {
            motValide = false;
            break;
        }
    }
    return motValide;
}

/**
* @brief Supprime les lettres du mot de la main d'un joueur
* @param [in, out] le mot a verifier, le joueur qui joue, la table
* @param [in] l'argument de la commande
*/
void supprLettreCoupR(char* arg2, int arg, Joueur* joueur, Table* table) {
    for (int i = 0; i < strlen(arg2); i++) {
        for (int j = 0; j < joueur->nbCartes; j++) {
            // si la lettre est dans la main du joueur et qu'elle n'est pas deja dans le mot sur la table, on la supprime
            if (joueur->main[j].lettre == arg2[i] && table->mots[arg - 1][i] != arg2[i]) {
                for (int k = j; k < joueur->nbCartes - 1; k++) {
                    joueur->main[k] = joueur->main[k + 1];
                }
                joueur->nbCartes--;
                break;
            }
        }
    }
}

/**
* @brief Remplace les lettres du mot sur la table par les lettres du joueur
* @param [in, out] le mot a verifier, le joueur qui joue, la table
* @param [in] l'argument de la commande
*/
void coupRMotValide(char* arg2, int arg, Joueur* joueur, Table* table) {
    supprLettreCoupR(arg2, arg, joueur, table);

    // on échange les lettres de sa main par les lettres de la table
    for (int i = 0; i < strlen(arg2); i++) {
        if (arg2[i] != table->mots[arg - 1][i])
            joueur->main[joueur->nbCartes++].lettre = table->mots[arg - 1][i];
    }

    delete[] table->mots[arg - 1];
    table->mots[arg - 1] = new char[strlen(arg2) + 1];
    strcpy(table->mots[arg - 1], arg2);
}

/**
* @brief Execute le coup R : remplace une ou plusieurs lettre(s) d'un mot sur la table par des lettres que le joueur a en main
* @param [in, out] la liste des joueurs, la table, le mot par lequel on remplace
* @param [in] l'argument de la commande, le fichier ods4
*/
void coupR(Joueur* joueur, Table* table, int arg, char* arg2, const char* ods4) {
    char* nouveauMot = new char[joueur->nbCartes + strlen(arg2) + 1];

    // copie le mot de la table et les lettres du joueur dans la mémoire allouée
    strcpy(nouveauMot, table->mots[arg - 1]); 
    unsigned int longueurMot = strlen(nouveauMot);
    for (int i = 0; i < joueur->nbCartes; i++)
        nouveauMot[i + longueurMot] = joueur->main[i].lettre;

    nouveauMot[longueurMot + joueur->nbCartes] = '\0';


    if (rechercheMot(arg2, ods4)) {
        bool motValide = coupRValideOuPas(arg2, nouveauMot);

        if (motValide)
            coupRMotValide(arg2, arg, joueur, table);
        else {
            joueur->nbPoints += 3;
            cout << "Mot invalide, vous passez votre tour" << endl;
        }
        delete[] nouveauMot;
    }

    else {
        delete[] nouveauMot;
        joueur->nbPoints += 3;
        cout << "Mot invalide, vous passez votre tour" << endl;
    }
}

/**
* @brief Verifie si les lettres du mot sont dans le meme ordre que les lettres du mot sur la table
* @param [in] le mot a verifier, le mot de la table
* @return true si les lettres sont dans le meme ordre, false sinon
*/
bool memeOrdre(const char* arg2, const char* arg) { 
    int indexMot1 = 0;
    int indexMot2 = 0;

    while (indexMot1 < strlen(arg) && indexMot2 < strlen(arg2)) {
        if (arg[indexMot1] == arg2[indexMot2]) // si les lettres sont identiques, on passe a la lettre suivante
            indexMot2++;
        indexMot1++;
    }
    return indexMot2 == strlen(arg2);
}

/**
* @brief Supprime les lettres du mot de la main du joueur
* @param [in, out] le mot a verifier, le joueur qui joue, la table
* @param [in] l'argument de la commande
*/
void supprLettreCoupC(Table* table, Joueur* joueur, int arg, char* arg2) {
    char* nouvelleMain = new char[joueur->nbCartes + strlen(arg2) + 1];
    int index = 0;

    // on copie le mot de la table et les lettres du joueur dans la mémoire allouée
    strcpy(nouvelleMain, table->mots[arg - 1]); 
    unsigned int longueurMot = strlen(nouvelleMain);
    for (int i = 0; i < joueur->nbCartes; i++) {
        nouvelleMain[i + longueurMot] = joueur->main[i].lettre;
    }
    nouvelleMain[longueurMot + joueur->nbCartes] = '\0';

    // on compare les lettres de arg2 avec les lettres de nouvelleMain, si elles sont identiques, on les supprime
    while (index != strlen(arg2)) {
        for (int j = 0; j < strlen(nouvelleMain) + 1; j++) {
            if (arg2[index] == nouvelleMain[j]) {
                for (int k = j; k < strlen(nouvelleMain); k++) {
                    nouvelleMain[k] = nouvelleMain[k + 1];
                }
                index++;
                break;
            }
        }
    }
    
    // on remplace les lettres du joueur par les lettres de nouvelleMain
    joueur->nbCartes = strlen(nouvelleMain);
    for (int i = 0; i < joueur->nbCartes; i++)
        joueur->main[i].lettre = nouvelleMain[i];

    delete[] nouvelleMain;
}

/**
* @brief Execute le coup C : complete un mot sur la table avec des lettres que le joueur a en main
* @param [in, out] la table, le joueur qui joue, le mot par lequel on complete
* @param [in] l'index du mot a completer
*/
void coupC(Table* table, Joueur* joueur, char* arg2, const int arg) {
    char* mot = new char[MAX_MOT];
    strcpy(mot, table->mots[arg - 1]);

    if (memeOrdre(mot, arg2)) {
        supprLettreCoupC(table, joueur, arg, arg2);
        strcpy(table->mots[arg - 1], arg2); 
        
    }
    else {
        joueur->nbPoints += 3;
        cout << "Mot invalide, vous passez votre tour" << endl;
    }
    delete[] mot;
}