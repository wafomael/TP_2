// ============================================================
// IO.h — chargement (O) / sauvegarde (S) de population  [Dev C]
// TP2 8INF259 — Arborescence génétique
// ============================================================
#ifndef IO_H
#define IO_H

#include <string>
#include "Population.h"

// TODO [Dev C] : O <fichier> — charge une population depuis un fichier
// (remplace la population courante). Retourne false si fichier invalide.
// Note : templates → implémentation dans le .h (pas de IO.cpp pour
// les fonctions template ; IO.cpp possible pour les utilitaires non-template)
template <typename T>
bool chargerPopulation(const std::string& chemin, Population<T>& pop);

// TODO [Dev C] : S <fichier> — sauvegarde la population courante
// (sauter les individus supprimés / nullptr)
template <typename T>
bool sauvegarderPopulation(const std::string& chemin, const Population<T>& pop);

#endif // IO_H
