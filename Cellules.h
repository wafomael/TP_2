// ============================================================
// Cellules.h — types de données ColorCell / ChromoCell  [Dev B]
// TP2 8INF259 — Arborescence génétique
// Règle d'or : ces classes ne connaissent RIEN de la généalogie.
// Elles savent se lire (>>), s'afficher (<<) et se fusionner (+).
// ============================================================
#ifndef CELLULES_H
#define CELLULES_H

#include <iostream>

// ------------------------------------------------------------
// ColorCell : couleur RGB
// ------------------------------------------------------------
struct ColorCell {
    int r = 0, g = 0, b = 0;

    // TODO [Dev B] : fusion = moyenne composante par composante
    ColorCell operator+(const ColorCell& o) const;

    // TODO [Dev B] : affichage "r g b"  (ex: "127 63 63")
    friend std::ostream& operator<<(std::ostream& os, const ColorCell& c);

    // TODO [Dev B] : lecture "r g b"
    friend std::istream& operator>>(std::istream& is, ColorCell& c);
};

// ------------------------------------------------------------
// ChromoCell : 4 paires de 2 lettres (A–L)
// ------------------------------------------------------------
struct ChromoCell {
    // TODO [Dev B] : représentation des 4 paires (ex: char paires[4][2])

    // TODO [Dev B] : fusion = gauche de C1 + droite de C2 pour chaque paire
    ChromoCell operator+(const ChromoCell& o) const;

    // TODO [Dev B] : affichage "IJ KL AC BD"
    friend std::ostream& operator<<(std::ostream& os, const ChromoCell& c);

    // TODO [Dev B] : lecture "IJ KL AC BD"
    friend std::istream& operator>>(std::istream& is, ChromoCell& c);
};

#endif // CELLULES_H
