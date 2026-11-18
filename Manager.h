// ============================================================
// Manager.h — chargement (O) / sauvegarde (S)
// Dev C : HOUNDETON BOTON Harold
// TP2 8INF259 — Arborescence génétique
//
// FORMAT FICHIER (POPULATION_TYPE.txt) :
//   ligne 1 : TYPE nbIndividus        (ex: "COLORCELL 6")
//   lignes  : [Id] [IdP1|/] [IdP2|/] [valeur]   ("/" = parent inconnu)
//
// PHILOSOPHIE : ce fichier est un TUYAU BETE — aucune logique de
// parsing, la serialisation vit dans les operateurs << et >> de
// Population. Ici : gestion du FICHIER (ouverture/fermeture) +
// en-tete + "out << pop" / "in >> pop".
//
// ROLES (découpage avec le main) :
//   O : le main ouvre le fichier, lireEntete() -> type + nb,
//       détermine T, crée la Population<T> et passe le FLUX
//       positionné après l'en-tête à chargerPopulation().
//   S : le main passe juste le CHEMIN + le nom du type (enum->
//       string) — le file manager ouvre/écrit/ferme tout seul.
// ============================================================
#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <iostream>
#include <fstream>
#include "Population.h"

// Lit la ligne d'en-tête : remplit typeNom ("COLORCELL"/"CHROMOCELL")
// et nbIndividus. Le main s'en sert pour choisir T avant de créer
// sa Population<T>. Retourne false si l'en-tête est mal formée.
inline bool lireEntete(std::istream& in, std::string& typeNom, int& nbIndividus) {
    return (bool)(in >> typeNom >> nbIndividus);
}

// O : lit les individus depuis le flux (positionné APRES l'en-tête,
//     lu par le main). Toute la validation est dans operator>> de
//     Population — ici on fait juste transférer l'état du flux.
template <typename T>
bool chargerPopulation(std::istream& in, Population<T>& population) {
    return (bool)(in >> population);
}

// S : prend le CHEMIN — le file manager ouvre/écrit/ferme tout seul.
//     En-tête (type + nbVivants) puis le corps via operator<< de
//     Population. Retourne false si le fichier n'a pas pu s'ouvrir
//     ou si l'écriture a échoué.
template <typename T>
bool sauvegarderPopulation(const std::string& chemin, const std::string& typeNom,
                           const Population<T>& population) {
    std::ofstream out(chemin);
    if (!out.is_open()) {
        return false;
    }
    out << typeNom << ' ' << population.nbVivants() << '\n';
    out << population;
    return out.good();
}

#endif // MANAGER_H
