// ============================================================
// TP_2.cpp — main : lecture TRANSACTIONS.txt + dispatch  [Dev C]
// TP2 8INF259 — Arborescence génétique
//
// Principe : le main est une COQUILLE. Il parse les lignes et
// appelle l'API de Population — jamais de logique metier ici.
//
// Type courant : Population<ColorCell> et Population<ChromoCell>
// sont deux classes differentes -> on garde deux pointeurs + un
// enum pour savoir lequel est actif. Un seul est non-null a la fois
// (C et O remplacent la population courante : delete + new).
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include "Population.h"
#include "ColorCell.h"
#include "ChromoCell.h"
#include "Affichage.h"
#include "IO.h"

enum TypeCourant { AUCUN, COLOR, CHROMO };

// TODO [Dev C] : dispatcher les appels selon le type courant.
// Chaque transaction devra faire :
//   if (type == COLOR) { /* travail sur popC */ }
//   else               { /* travail sur popCh */ }

int main(int argc, char* argv[])
{
    // TODO [Dev C] : verifier argc, ouvrir argv[1] (TRANSACTIONS.txt)

    Population<ColorCell>*  popC  = nullptr;
    Population<ChromoCell>* popCh = nullptr;
    TypeCourant type = AUCUN;

    // TODO [Dev C] : boucle de lecture ligne par ligne, decouper en tokens
    //
    // switch (op) {
    //   case 'C': // creer population vide + fixer type (delete ancien!)
    //   case 'A': // parser valeur via >> -> pop->ajouter(v)
    //   case 'O': // chargerPopulation(fichier, *pop) (voir IO.h)
    //   case 'S': // sauvegarderPopulation(fichier, *pop)
    //   case '+': // pop->additionner(x, y)
    //   case '-': // pop->supprimer(x) -> "Suppression effectuee"
    //   case '?': // pop->ancetreCommun(x, y)
    //   case '$': // afficherArbre(pop->get(x))
    // }

    delete popC;
    delete popCh;
    return 0;
}
