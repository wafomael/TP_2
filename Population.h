#pragma once
#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <map>
#include <iostream>
#include "Individu.h"

/*
Classe Population<T> : catalogue d'individus (acces par id = index+1)
L'arbre genealogique emerge des pointeurs parent1/parent2 des Individu.
Pointeurs dans le vector : adresses stables malgre la reallocation
du vector + "tombstones" (nullptr) pour les individus supprimes.
*/

template <typename T>
class Population {
private:
    std::vector<Individu<T>*> individus;   // index = id - 1 ; nullptr = supprime (tombstone)
    int nextId = 1;

    // DFS recursif : remplit la map {ancetre -> distance depuis le node de depart}
    // repasse sur un node seulement si le nouveau chemin est plus court
    void remonterAncetres(Individu<T>* n, int dist,
                          std::map<Individu<T>*, int>& distances) const;

public:
    Population() = default;
    ~Population();                               // delete de tous les nodes restants

    // A : ajoute un individu sans parents, retourne le node cree
    Individu<T>* ajouter(const T& v);

    // + X Y : fusionne valeurs (operator+ de T), enfant avec parents x,y
    Individu<T>* additionner(int x, int y);

    // - X : met a nullptr les liens des enfants, delete, tombstone
    bool supprimer(int x);

    // acces par id (1-based) — retourne nullptr si invalide/supprime
    Individu<T>* get(int id) const;

    // ? X Y : BFS vers les parents, ancetre commun le plus proche (somme min)
    void ancetreCommun(int x, int y) const;

    void afficherIndividu(int x) const;

    // taille du vector (tombstones inclus)
    int taille() const;
};

/*
Implementation de la classe Population*/

template <typename T>
Population<T>::~Population() {
    for (Individu<T>* n : individus) {
        delete n;
    }
}

template <typename T>
Individu<T>* Population<T>::ajouter(const T& v) {
    Individu<T>* n = new Individu<T>(nextId++, v);
    individus.push_back(n);
    return n;
}

template <typename T>
Individu<T>* Population<T>::get(int id) const {
    if (id < 1 || id > (int)individus.size()) {
        return nullptr;
    }
    return individus[id - 1];   // peut etre nullptr (tombstone)
}

template <typename T>
Individu<T>* Population<T>::additionner(int x, int y) {
    Individu<T>* px = get(x);
    Individu<T>* py = get(y);
    if (px == nullptr || py == nullptr) {
        std::cout << "Individu invalide\n";
        return nullptr;
    }
    T fusion = px->valeur + py->valeur;      // operator+ de T fait le travail metier
    Individu<T>* enfant = new Individu<T>(nextId++, fusion, px, py);
    individus.push_back(enfant);
    afficherIndividu(enfant->id);
    return enfant;
}

template <typename T>
bool Population<T>::supprimer(int x) {
    Individu<T>* cible = get(x);
    if (cible == nullptr) {
        return false;
    }
    // ses enfants ont maintenant un parent inconnu
    for (Individu<T>* n : individus) {
        if (n != nullptr) {
            if (n->parent1 == cible) n->parent1 = nullptr;
            if (n->parent2 == cible) n->parent2 = nullptr;
        }
    }
    delete cible;
    individus[x - 1] = nullptr;   // tombstone : les ids ne bougent pas
    return true;
}

template <typename T>
void Population<T>::remonterAncetres(Individu<T>* n, int dist,
                                    std::map<Individu<T>*, int>& distances) const {
    // deja visite par un chemin au moins aussi court -> inutile de repasser
    if (distances.find(n) != distances.end() && distances[n] <= dist) {
        return;
    }
    distances[n] = dist;
    if (n->parent1 != nullptr) remonterAncetres(n->parent1, dist + 1, distances);
    if (n->parent2 != nullptr) remonterAncetres(n->parent2, dist + 1, distances);
}

template <typename T>
void Population<T>::ancetreCommun(int x, int y) const {
    Individu<T>* px = get(x);
    Individu<T>* py = get(y);
    if (px == nullptr || py == nullptr) {
        std::cout << "Individu invalide\n";
        return;
    }

    // map {ancetre -> distance} pour chacun des deux individus
    std::map<Individu<T>*, int> distX, distY;
    remonterAncetres(px, 0, distX);
    remonterAncetres(py, 0, distY);

    // ancetre commun = present dans les DEUX maps, somme des distances minimale
    Individu<T>* meilleur = nullptr;
    int meilleureSomme = -1;
    for (auto& paire : distX) {
        if (distY.find(paire.first) != distY.end()) {
            int somme = paire.second + distY[paire.first];
            if (meilleureSomme == -1 || somme < meilleureSomme) {
                meilleureSomme = somme;
                meilleur = paire.first;
            }
        }
    }

    if (meilleur == nullptr) {
        std::cout << "Aucun ancetre commun entre " << x << " et " << y << ".\n";
    } else {
        std::cout << "Ancetre commun de " << x << " et " << y << " : "
                  << meilleur->id << " (" << meilleur->valeur << ")\n";
        std::cout << x << " est a " << distX[meilleur] << " generation(s) de " << meilleur->id << ".\n";
        std::cout << y << " est a " << distY[meilleur] << " generation(s) de " << meilleur->id << ".\n";
    }
}

template <typename T>
void Population<T>::afficherIndividu(int x) const {
    Individu<T>* n = get(x);
    if (n != nullptr) {
        std::cout << n->id << " : " << n->valeur << "\n";
    }
}

template <typename T>
int Population<T>::taille() const {
    return (int)individus.size();
}

#endif // !POPULATION_H
