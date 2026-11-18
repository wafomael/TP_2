// ============================================================
// Affichage.h — affichage arbre généalogique ($ X)
// Dev B : FRANCK MARIUS NJIKE NFANGA
// TP2 8INF259 — Arborescence génétique
//
// Format de l'énoncé : individu en haut, parents en dessous,
// décalés à droite à chaque génération. Exemple :
//   $ 6
//   6 : 127 63 63
//      4 : 0 127 127
//          1 : 0 0 255
//          2 : 0 255 0
//      3 : 255 0 0
// ============================================================
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <iostream>
#include "Individu.h"

// Nombre d'espaces par niveau de génération
const int INDENT_PAR_NIVEAU = 4;

// Ecrit l'indentation correspondant a la profondeur
inline void indent(int profondeur) {
    for (int i = 0; i < profondeur * INDENT_PAR_NIVEAU; i++) {
        std::cout << ' ';
    }
}

// Affichage recursif de l'arbre :
// - nullptr -> "inconnu" (parent supprime ou absent alors que
//   l'autre parent existe)
// - sinon : "id : valeur" puis parent1 et parent2 a profondeur+1
// - un node sans AUCUN parent n'affiche pas de "inconnu"
//   (feuille de l'arbre, comme dans l'exemple de l'énoncé)
// - un individu apparaissant 2 fois dans l'arbre est affiche 2 fois
//   (pas d'optimisation, comme le montre l'énoncé)
template <typename T>
void afficherArbre(Individu<T>* n, int profondeur = 0) {
    indent(profondeur);
    if (n == nullptr) {
        std::cout << "inconnu\n";
        return;
    }
    std::cout << n->id << " : " << n->valeur << "\n";
    if (n->parent1 != nullptr || n->parent2 != nullptr) {
        afficherArbre(n->parent1, profondeur + 1);
        afficherArbre(n->parent2, profondeur + 1);
    }
}

#endif // AFFICHAGE_H
