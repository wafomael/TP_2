// ============================================================
// TP_2.cpp — main : lecture TRANSACTIONS.txt + dispatch
// Dev C : HOUNDETON BOTON Harold
// TP2 — Arborescence génétique
//
// Le main est une COQUILLE : il parse et appelle l'API de
// Population / Affichage / Manager — pas de logique metier.
//
// Type courant : string "COLORCELL" / "CHROMOCELL" ("" = aucune
// population). Il sert directement de nom pour l'en-tête de S.
//
// AFFICHAGE : chaque commande valide est annoncée par "----> OP"
// suivi d'une ligne vide en séparation. Les erreurs sont préfixées
// "> [ERREUR : ...]" pour les distinguer du reste de la sortie.
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include "Population.h"
#include "ColorCell.h"
#include "ChromoCell.h"
#include "Affichage.h"
#include "Manager.h"
#include "OuvrirFichier.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Usage : TP_2.exe TRANSACTIONS.txt" << std::endl;
        return 1;
    }

    std::ifstream transactions = OuvrirFichier(argv[1]);
    if (!transactions.is_open()) {
        return 1;   // message deja affiche par OuvrirFichier
    }

    Population<ColorCell>*  popC  = nullptr;
    Population<ChromoCell>* popCh = nullptr;
    std::string typeCourant;          // "COLORCELL" / "CHROMOCELL" ("" = aucune)
    int nbIndividus = 0;              // nombre lu dans l'en-tete (O)

    char op;
    while (transactions >> op) {
        switch (op) {

        // C TYPE : nouvelle population vide + type courant
        case 'C': {
            std::string type;
            transactions >> type;
            std::cout << "----> C " << type << std::endl;
            delete popC; delete popCh;
            popC = nullptr;
            popCh = nullptr;
            if (type == "COLORCELL") {
                popC = new Population<ColorCell>();
                typeCourant = "COLORCELL";
                std::cout << " > Population COLORCELL creee" << std::endl;
            } else if (type == "CHROMOCELL") {
                popCh = new Population<ChromoCell>();
                typeCourant = "CHROMOCELL";
                std::cout << " > Population CHROMOCELL creee" << std::endl;
            } else {
                std::cout << " > [ERREUR : type inconnu]" << std::endl;
            }
            break;
        }

        // A VALEURS : ajouter un individu sans parents (type courant)
        case 'A': {
            std::cout << "----> A" << std::endl;
            if (typeCourant == "COLORCELL") {
                ColorCell v;
                if (transactions >> v) {
                    Individu<ColorCell>* n = popC->ajouter(v);
                    std::cout << " > Individu ajoute : ";
                    popC->afficherIndividu(n->id);
                } else {
                    std::cout << " > [ERREUR : valeur invalide]" << std::endl;
                }
            } else if (typeCourant == "CHROMOCELL") {
                ChromoCell v;
                if (transactions >> v) {
                    Individu<ChromoCell>* n = popCh->ajouter(v);
                    std::cout << " > Individu ajoute : ";
                    popCh->afficherIndividu(n->id);
                } else {
                    std::cout << " > [ERREUR : valeur invalide]" << std::endl;
                }
            } else {
                std::cout << " > [ERREUR : aucune population courante]" << std::endl;
            }
            break;
        }

        // O POPULATION : charger un fichier -> le type de l'en-tete
        // devient le type courant (l'ancienne population est liberee)
        case 'O': {
            std::string fichier;
            transactions >> fichier;
            std::cout << "----> O " << fichier << std::endl;
            std::ifstream f = OuvrirFichier(fichier);
            if (!f.is_open()) break;

            std::string typeNom;
            if (!lireEntete(f, typeNom, nbIndividus)) {
                std::cout << " > [ERREUR : en-tete invalide]" << std::endl;
                break;
            }

            delete popC; delete popCh;
            popC = nullptr;
            popCh = nullptr;
            if (typeNom == "COLORCELL") {
                popC = new Population<ColorCell>();
                typeCourant = "COLORCELL";
                if (!chargerPopulation(f, *popC)) {
                    std::cout << " > [ERREUR : fichier mal forme]" << std::endl;
                    break;
                }
            } else if (typeNom == "CHROMOCELL") {
                popCh = new Population<ChromoCell>();
                typeCourant = "CHROMOCELL";
                if (!chargerPopulation(f, *popCh)) {
                    std::cout << " > [ERREUR : fichier mal forme]" << std::endl;
                    break;
                }
            } else {
                std::cout << " > [ERREUR : type inconnu dans le fichier]" << std::endl;
                break;
            }
            std::cout << " > Population chargee : " << typeNom
                      << " (" << nbIndividus << " individus)" << std::endl;
            break;
        }

        // S POPULATION : sauvegarder la population courante
        case 'S': {
            std::string fichier;
            transactions >> fichier;
            std::cout << "----> S " << fichier << std::endl;
            bool ok = false;
            if (typeCourant == "COLORCELL") {
                ok = sauvegarderPopulation(fichier, typeCourant, *popC);
            } else if (typeCourant == "CHROMOCELL") {
                ok = sauvegarderPopulation(fichier, typeCourant, *popCh);
            } else {
                std::cout << " > [ERREUR : aucune population courante]" << std::endl;
                break;
            }
            if (ok) std::cout << " > Population sauvegardee dans " << fichier << std::endl;
            else    std::cout << " > [ERREUR : ecriture impossible]" << std::endl;
            break;
        }

        // + X Y : creer un enfant de X et Y (fusion des valeurs)
        case '+': {
            int x, y;
            transactions >> x >> y;
            std::cout << "----> + " << x << " " << y << std::endl;
            if (typeCourant == "COLORCELL")       popC->additionner(x, y);
            else if (typeCourant == "CHROMOCELL") popCh->additionner(x, y);
            else std::cout << " > [ERREUR : aucune population courante]" << std::endl;
            break;
        }

        // - X : supprimer l'individu X (ses enfants -> parent inconnu)
        case '-': {
            int x;
            transactions >> x;
            std::cout << "----> - " << x << std::endl;
            bool ok = false;
            if (typeCourant == "COLORCELL")       ok = popC->supprimer(x);
            else if (typeCourant == "CHROMOCELL") ok = popCh->supprimer(x);
            else {
                std::cout << " > [ERREUR : aucune population courante]" << std::endl;
                break;
            }
            if (ok) std::cout << " > Suppression effectuee" << std::endl;
            else    std::cout << " > [ERREUR : individu inexistant]" << std::endl;
            break;
        }

        // ? X Y : ancetre commun le plus proche
        case '?': {
            int x, y;
            transactions >> x >> y;
            std::cout << "----> ? " << x << " " << y << std::endl;
            if (typeCourant == "COLORCELL")       popC->ancetreCommun(x, y);
            else if (typeCourant == "CHROMOCELL") popCh->ancetreCommun(x, y);
            else std::cout << " > [ERREUR : aucune population courante]" << std::endl;
            break;
        }

        // $ X : afficher l'arbre genetique complet de X
        case '$': {
            int x;
            transactions >> x;
            std::cout << "----> $ " << x << std::endl;
            if (typeCourant == "COLORCELL")       afficherArbre(popC->get(x));
            else if (typeCourant == "CHROMOCELL") afficherArbre(popCh->get(x));
            else std::cout << " > [ERREUR : aucune population courante]" << std::endl;
            break;
        }

        default:
            std::cout << " > [ERREUR : operation inconnue '" << op << "']" << std::endl;
            break;
        }

        std::cout << std::endl;   // separation entre commandes
        // recupere le flux apres un >> en echec (valeur invalide consommee)
        transactions.clear();
    }

    delete popC;
    delete popCh;
    return 0;
}
