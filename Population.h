// ============================================================
// Population.h — catalogue d'individus + opérations  [Dev A]
// TP2 8INF259 — Arborescence génétique
// ============================================================
#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "Individu.h"

template <typename T>
class Population {
    std::vector<Individu<T>*> pop;   // index = id - 1 ; nullptr = supprimé (tombstone)
    int prochainId = 1;

public:
    Population() = default;
    ~Population();                               // delete de tous les nodes restants

    // A : ajoute un individu sans parents, retourne le node créé
    Individu<T>* ajouter(const T& v);

    // + X Y : fusionne valeurs (operator+ de T), enfant avec parents x,y
    Individu<T>* additionner(int x, int y);

    // - X : met à nullptr les liens des enfants, delete, tombstone
    bool supprimer(int x);

    // accès par id (1-based) — retourne nullptr si invalide/supprimé
    Individu<T>* get(int id) const;

    // ? X Y : BFS vers les parents, ancêtre commun le plus proche (somme min)
    void ancetreCommun(int x, int y) const;

    void afficherIndividu(int x) const;

    // parcours pour S (sauvegarde) et debug
    int taille() const;                          // taille du vector (tombstones inclus)

    // TODO [Dev A] : implémenter toutes les méthodes ci-dessus
};

#endif // POPULATION_H
