#pragma once
#ifndef CHROMOCELL_H
#define CHROMOCELL_H

#include <iostream>
#include <array>
#include <utility>   // std::pair

/*
Classe ChromoCell : quatre paires de chromosomes,
chaque chromosome identifie par une lettre majuscule A-L.
Stockage : std::array<char, 8> -> [g1,d1, g2,d2, g3,d3, g4,d4]
Addition : paire i de C3 = gauche de la paire i de C1
           + droite de la paire i de C2.
           Ex: AB CD EF GH + IJ KL AC BD = AJ CL EC GD
Format texte : "AB CD EF GH"  (couples separes par un espace)
Dev B : FRANCK MARIUS NJIKE NFANGA
*/

class ChromoCell {
	std::array<char, 8> paires;
public:
	static const int NB_PAIRES = 4;

	ChromoCell();

	// i = index de la paire (0 a 3)
	char getGauche(int i) const;
	char getDroite(int i) const;
	std::pair<char, char> getPaire(int i) const;
	void setPaire(int i, char gauche, char droite);

	// [Dev B : FRANCK MARIUS NJIKE NFANGA] paire i = gauche(i) de C1
	//                                     + droite(i) de C2
	//                                     (l'ordre des operandes compte !)
	ChromoCell operator+(const ChromoCell& autre) const;

	// [Dev B : FRANCK MARIUS NJIKE NFANGA] affichage "AB CD EF GH"
	//                                      lecture "AB CD EF GH"
	friend std::ostream& operator<<(std::ostream& os, const ChromoCell& c);
	friend std::istream& operator>>(std::istream& is, ChromoCell& c);
};

#endif // !CHROMOCELL_H
