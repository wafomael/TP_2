#pragma once
#ifndef COLORCELL_H
#define COLORCELL_H

#include <iostream>

/*
Classe ColorCell : trois entiers pour les composantes RGB (0-255)
Addition : R3 = (R1+R2)/2, G3 = (G1+G2)/2, B3 = (B1+B2)/2
Format texte : "r g b"  (ex: 100 255 0)
Dev B : FRANCK MARIUS NJIKE NFANGA
*/

class ColorCell {
private:
	int r, g, b;
public:
	ColorCell();
	ColorCell(int red, int green, int blue);

	int getR() const;
	int getG() const;
	int getB() const;
	void setR(int v);
	void setG(int v);
	void setB(int v);

	// [Dev B : FRANCK MARIUS NJIKE NFANGA] moyenne composante par composante
	ColorCell operator+(const ColorCell& autre) const;

	// [Dev B : FRANCK MARIUS NJIKE NFANGA] affichage "r g b" / lecture "r g b"
	friend std::ostream& operator<<(std::ostream& os, const ColorCell& c);
	friend std::istream& operator>>(std::istream& is, ColorCell& c);
};

#endif // !COLORCELL_H
