#pragma once
#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <iostream>

/*
Classe Individu<T> qui permet de stocker une valeur de type T
(ColorCell ou ChromoCell), un identifiant et des pointeurs
vers les deux parents (nullptr = parent inconnu)
*/

template <typename T>
class Individu {
public:
	int id;                    // identifiant (= index+1 dans la population)
	T valeur;                  // la donnée
	Individu<T>* parent1;      // nullptr = parent inconnu (/)
	Individu<T>* parent2;

	Individu(int identifiant, const T& v, Individu<T>* p1 = nullptr, Individu<T>* p2 = nullptr);
};

/*
Implementation de la classe Individu*/

template <typename T>
Individu<T>::Individu(int identifiant, const T& v, Individu<T>* p1, Individu<T>* p2)
	: id(identifiant), valeur(v), parent1(p1), parent2(p2) {}

/*
operator<< : format FICHIER (pas le format ecran "$" qui est "id : valeur")
Ecrit une ligne au format POPULATION_TYPE.txt :
    [Id] [IdParent1|/] [IdParent2|/] [valeur]
Lecture symetrique : id, puis "/" ou int pour chaque parent, puis >> valeur.
*/

template <typename T>
std::ostream& operator<<(std::ostream& os, const Individu<T>& n) {
	os << n.id << ' ';
	if (n.parent1 != nullptr) os << n.parent1->id; else os << '/';
	os << ' ';
	if (n.parent2 != nullptr) os << n.parent2->id; else os << '/';
	os << ' ' << n.valeur;
	return os;
}

#endif // !INDIVIDU_H
