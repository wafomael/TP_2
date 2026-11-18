#pragma once
#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include "Individu.h"

/*
Classe Population<T> : catalogue d'individus (acces par id = index+1)
L'arbre genealogique emerge des pointeurs parent1/parent2 des Individu.
Pointeurs dans le vector : adresses stables malgre la reallocation
du vector + "tombstones" (nullptr) pour les individus supprimes.
Dev A : WAFO FOKO Franck Mael
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

    // ? X Y : DFS vers les parents, ancetre commun le plus proche (somme min)
    void ancetreCommun(int x, int y) const;

    void afficherIndividu(int x) const;

    // ---- API pour les transactions O / S (utilisee par Dev C) ----

    // taille du vector (tombstones inclus)
    int taille() const;

    // nombre d'individus vivants (non nullptr) — pour l'en-tete du fichier
    int nbVivants() const;

    // iteration lecture seule pour S : sauter les nullptr (tombstones)
    const std::vector<Individu<T>*>& getIndividus() const;

    // O : ajoute un individu en resolvant les ids parents lus dans le fichier
    // (id <= 0 ou inexistant -> parent nullptr). Id doit suivre l'ordre du fichier.
    Individu<T>* ajouterAvecParents(const T& v, int idP1, int idP2);
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

/*
Operateurs flux : la Population sait se (de)serialiser en format FICHIER.
operator<< -> corps du fichier : une ligne "[id] [p1|/] [p2|/] [valeur]"
              par individu vivant (saute les tombstones).
operator>> -> lit les lignes jusqu'a la fin du flux. Une ligne mal
              formee met le flux en echec (failbit).
              Note : ajoute aux individus existants — prevu pour une
              Population fraichement creee (le main delete l'ancienne).
*/
template <typename T>
std::ostream& operator<<(std::ostream& out, const Population<T>& pop) {
    for (Individu<T>* n : pop.getIndividus()) {
        if (n != nullptr) {
            out << *n << '\n';
        }
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Population<T>& population) {
    int id;
    std::string tokP1, tokP2;
    while (in >> id) {
        T valeur;
        if (!(in >> tokP1 >> tokP2 >> valeur)) {
            in.setstate(std::ios::failbit);   // ligne tronquee / valeur invalide
            return in;
        }
        int idP1, idP2;
        try {
            idP1 = (tokP1 == "/") ? -1 : std::stoi(tokP1);
            idP2 = (tokP2 == "/") ? -1 : std::stoi(tokP2);
        } catch (...) {
            in.setstate(std::ios::failbit);   // parent ni "/" ni entier
            return in;
        }
        if (id != population.taille() + 1) {
            in.setstate(std::ios::failbit);   // ids desordonnes / doublons
            return in;
        }
        population.ajouterAvecParents(valeur, idP1, idP2);
    }
    // la boucle sort quand >> echoue : en fin de fichier eofbit ET
    // failbit sont leves -> ce n'est PAS une erreur, on les retire
    if (in.eof()) {
        in.clear();
    }
    return in;
}

template <typename T>
int Population<T>::nbVivants() const {
    int compte = 0;
    for (Individu<T>* n : individus) {
        if (n != nullptr) compte++;
    }
    return compte;
}

template <typename T>
const std::vector<Individu<T>*>& Population<T>::getIndividus() const {
    return individus;
}

template <typename T>
Individu<T>* Population<T>::ajouterAvecParents(const T& v, int idP1, int idP2) {
    Individu<T>* p1 = (idP1 > 0) ? get(idP1) : nullptr;
    Individu<T>* p2 = (idP2 > 0) ? get(idP2) : nullptr;
    Individu<T>* n = new Individu<T>(nextId++, v, p1, p2);
    individus.push_back(n);
    return n;
}

#endif // !POPULATION_H
