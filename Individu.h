// ============================================================
// Individu.h — node générique de l'arborescence  [Dev A]
// TP2 8INF259 — Arborescence génétique
// ============================================================
#ifndef INDIVIDU_H
#define INDIVIDU_H

template <typename T>
struct Individu {
    int id;                          // identifiant (= index+1 dans la population)
    T valeur;                        // la donnée (ColorCell ou ChromoCell)
    Individu* parent1 = nullptr;     // nullptr = parent inconnu (/)
    Individu* parent2 = nullptr;

    Individu(int id_, const T& v, Individu* p1 = nullptr, Individu* p2 = nullptr)
        : id(id_), valeur(v), parent1(p1), parent2(p2) {}
};

#endif // INDIVIDU_H
