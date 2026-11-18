#include "OuvrirFichier.h"
#include <iostream>

std::ifstream OuvrirFichier(const std::string& nom) {
	std::ifstream is(nom);

	if (!is.is_open()) {
		std::cout << "Fichier " << nom << " introuvable." << std::endl;
	}

	return is;
}
