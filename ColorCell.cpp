#include "ColorCell.h"
#include <iostream>


// Constructeur par défaut : cellule NULLE — composantes à -1
// (impossible pour un RGB valide 0-255). La cellule n'a pas de
// sens tant qu'elle n'a pas été remplie (>>, setters, ou operator+).
ColorCell::ColorCell() : r(-1), g(-1), b(-1) {}

// Constructeur avec valeurs : ColorCell c(0, 127, 127);
ColorCell::ColorCell(int red, int green, int blue) : r(red), g(green), b(blue) {}

int ColorCell::getR() const {
    return r;
}
int ColorCell::getG() const {
    return g;
}
int ColorCell::getB() const {
    return b;
}

// Les setters bloquent les valeurs hors RGB valide [0, 255]
// (ignore silencieusement, même convention que setPaire de ChromoCell)
void ColorCell::setR(int v) {
    if (v < 0 || v > 255) return;
    r = v;
}
void ColorCell::setG(int v) {
    if (v < 0 || v > 255) return;
    g = v;
}
void ColorCell::setB(int v) {
    if (v < 0 || v > 255) return;
    b = v;
}


// Affichage "r g b" (ex: "127 63 63"), sans espace ni saut de ligne à la fin.
// os peut être l'écran (std::cout) ou un fichier : même code pour les deux.
// On retourne os pour pouvoir enchaîner : std::cout << c << std::endl;
std::ostream& operator<<(std::ostream& os, const ColorCell& c) {
    os << c.r << " " << c.g << " " << c.b;
    return os;
}

// Addition : moyenne de chaque composante (division entière).
// Dans a + b : r est le rouge de a (gauche), autre.r est le rouge de b (droite).
// La fonction est const : elle ne modifie ni a ni b, elle crée une nouvelle cellule.
ColorCell ColorCell::operator+(const ColorCell& autre  ) const {
    ColorCell resultat;
    resultat.r = (r + autre.r) / 2;
    resultat.g = (g + autre.g) / 2;
    resultat.b = (b + autre.b) / 2;
    return resultat;
}

// Lecture "r g b" : trois entiers entre 0 et 255,
// c'est une fonction libre, et elle retourne le flux.  
// Si une valeur est hors limites, on met le flux en état d'échec, ce qui
// permet à l'appelant d'écrire : if (flux >> cellule) { ... } else { erreur }
std::istream& operator>>(std::istream& is, ColorCell& c) {
    int r, g, b;
    if (!(is >> r >> g >> b)) {
        return is;          // lecture échouée : flux déjà en échec
    }
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        is.setstate(std::ios::failbit);
        return is;
    }
    // on ne touche c que si TOUT est valide (c intact en cas d'erreur)
    c.setR(r);
    c.setG(g);
    c.setB(b);
    return is;
}
