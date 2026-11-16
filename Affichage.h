// ============================================================
// Affichage.h — affichage arbre généalogique ($ X)  [Dev B]
// TP2 8INF259 — Arborescence génétique
// Récursion + indentation : individu en haut, parents en dessous
// décalés à droite à chaque génération.
// ============================================================
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <iostream>
#include "Individu.h"

// TODO [Dev B] : indentation selon la profondeur (espaces/tabs)
inline void indent(int profondeur);

// TODO [Dev B] : affichage récursif
// - nullptr → "inconnu"
// - sinon : "id : valeur" puis parent1 et parent2 à profondeur+1
// - un individu présent 2 fois dans l'arbre s'affiche 2 fois (pas d'optimisation)
template <typename T>
void afficherArbre(Individu<T>* n, int profondeur = 0);

#endif // AFFICHAGE_H
