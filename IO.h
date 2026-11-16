// ============================================================
// IO.h — chargement (O) / sauvegarde (S) de population  [Dev C]
// TP2 8INF259 — Arborescence génétique
//
// FORMAT FICHIER (POPULATION_TYPE.txt) :
//   ligne 1 : TYPE nbIndividus        (ex: "COLORCELL 6")
//   lignes  : [Id] [IdP1|/] [IdP2|/] [valeur]   ("/" = parent inconnu)
//
// ECRIRE = trivial grace a operator<< de Individu :
//   for (Individu<T>* n : pop.getIndividus())
//       if (n != nullptr) out << *n << '\n';    // format fichier garanti
//
// LIRE = symetrique : lire id, puis token "/" ou entier pour chaque
// parent, puis "in >> valeur" (operator>> de la cellule).
// Puis pop.ajouterAvecParents(valeur, idP1, idP2) — les ids sont
// resolus via get() (les parents precedent toujours les enfants).
// ============================================================
#ifndef IO_H
#define IO_H

#include <string>
#include "Population.h"

// TODO [Dev C] : O <fichier> — charge une population depuis un fichier
// (remplace la population courante : le main delete l'ancienne).
// Retourne false si fichier invalide/introuvable.
// Note : templates → implementation dans le .h (pas de IO.cpp).
template <typename T>
bool chargerPopulation(const std::string& chemin, Population<T>& pop);

// TODO [Dev C] : S <fichier> — sauvegarde la population courante
// Ecrire l'en-tete (type + pop.nbVivants()) puis les lignes via
// "out << *n" en sautant les nullptr de getIndividus().
template <typename T>
bool sauvegarderPopulation(const std::string& chemin, const Population<T>& pop);

#endif // IO_H
