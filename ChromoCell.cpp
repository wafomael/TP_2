#include "ChromoCell.h"
#include <string>

// Rappel du stockage (voir ChromoCell.h) : tableau de 8 lettres
// [g0,d0, g1,d1, g2,d2, g3,d3]. Pour la paire i :
//   lettre de gauche -> case 2*i
//   lettre de droite -> case 2*i + 1
// Seules getGauche, getDroite et setPaire font ce calcul ;
// toutes les autres fonctions passent par elles.

// Constructeur par défaut : "AA AA AA AA" (valeur valide plutôt que des
// caractères au hasard). Utilisé par "ChromoCell c;" avant une lecture.
ChromoCell::ChromoCell() {
    paires.fill('A');
}

// Lettre de gauche de la paire i (0 à 3)
char ChromoCell::getGauche(int i) const {
    return paires[2 * i];
}

// Lettre de droite de la paire i (0 à 3)
char ChromoCell::getDroite(int i) const {
    return paires[2 * i + 1];
}

// Les deux lettres de la paire i ensemble
std::pair<char, char> ChromoCell::getPaire(int i) const {
    return { getGauche(i), getDroite(i) };
}

// Remplace la paire i par les lettres gauche et droite
void ChromoCell::setPaire(int i, char gauche, char droite) {
    paires[2 * i] = gauche;
    paires[2 * i + 1] = droite;
}

// Addition C3 = C1 + C2 : pour chaque paire, la lettre de GAUCHE vient de
// C1 (cette cellule) et la lettre de DROITE vient de C2 (autre).
// Ex: AB CD EF GH + IJ KL AC BD = AJ CL EC GD. L'ordre des opérandes compte.
ChromoCell ChromoCell::operator+(const ChromoCell& autre) const {
    ChromoCell resultat;
    for (int i = 0; i < NB_PAIRES; i++) {
        resultat.setPaire(i, getGauche(i), autre.getDroite(i));
    }
    return resultat;
}

// Affichage "AB CD EF GH" : les 4 paires séparées par un espace,
// sans espace ni saut de ligne à la fin.
std::ostream& operator<<(std::ostream& os, const ChromoCell& c) {
    for (int i = 0; i < ChromoCell::NB_PAIRES; i++) {
        if (i > 0) {
            os << " ";          // un espace avant chaque paire, sauf la première
        }
        os << c.getGauche(i) << c.getDroite(i);
    }
    return os;
}

// Lecture "AB CD EF GH" : quatre mots de 2 lettres majuscules entre A et L.
// On remplit une cellule temporaire "lue" et on ne la copie dans c qu'à la
// fin, quand les 4 paires sont valides. Sinon, le flux est mis en échec,
// ce qui permet à l'appelant d'écrire : if (flux >> cellule) { ... }
std::istream& operator>>(std::istream& is, ChromoCell& c) {
    ChromoCell lue;
    for (int i = 0; i < ChromoCell::NB_PAIRES; i++) {
        std::string mot;
        if (!(is >> mot)) {
            return is;                 // il manque une paire : flux déjà en échec
        }
        bool valide = mot.size() == 2
            && mot[0] >= 'A' && mot[0] <= 'L'
            && mot[1] >= 'A' && mot[1] <= 'L';
        if (!valide) {
            is.setstate(std::ios::failbit);
            return is;
        }
        lue.setPaire(i, mot[0], mot[1]);
    }
    c = lue;
    return is;
}
