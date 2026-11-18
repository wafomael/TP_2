<p align="center">
  <img src="https://thumb.wikimedia.org/wikipedia/fr/thumb/3/34/UQAC_Logo.png/330px-UQAC_Logo.png" alt="Logo UQAC" width="220">
</p>

<h1 align="center">TP2 : Arborescence génétique</h1>

<p align="center">
  <b>8INF259 — Structures de données</b><br>
  Enseignant : David Gagnon<br>
  Groupe R  : FRANCK MARIUS NJIKE NFANGA · HOUNDETON BOTON Harold · WAFO FOKO Franck Mael
</p>

---

## Présentation

Ce programme simule une population d'individus et leur généalogie. Chaque individu possède une « cellule » — soit une couleur RGB (`ColorCell`), soit quatre paires de chromosomes (`ChromoCell`). Le programme lit un fichier de transactions passé en paramètre et exécute les opérations demandées : création d'une population (`C`), ajout d'un individu (`A`), chargement d'une population depuis un fichier (`O`), sauvegarde (`S`), croisement de deux individus (`+`), suppression d'un individu (`-`), recherche de l'ancêtre commun le plus proche (`?`) et affichage de l'arbre généalogique d'un individu (`$`).

### Compilation et exécution

L'exécutable prend un seul argument :

```text
TP_2.exe TRANSACTIONS.txt
```

### Répartition

| Dev | Nom | Fichiers |
|---|---|---|
| A | WAFO FOKO Franck Mael | `Individu.h`, `Population.h` |
| B | FRANCK MARIUS NJIKE NFANGA | `ColorCell`, `ChromoCell`, `Affichage.h` |
| C | HOUNDETON BOTON Harold | `TP_2.cpp` (main), `Manager.h`, `OuvrirFichier` |

---

## Démarche de conception

### 1. Identification des entités

La première étape a été d'identifier les entités du problème : la **cellule** (la donnée portée par un individu), l'**individu** et la **population**. Les attributs de chacune ont ensuite été déterminés :

- `ColorCell` : trois entiers pour les composantes RGB ;
- `ChromoCell` : quatre paires de chromosomes (lettres A à L) ;
- `Individu<T>` : un identifiant, une valeur de type `T` et deux pointeurs vers ses parents ;
- `Population<T>` : l'ensemble des individus et les opérations de l'énoncé.

### 2. Deux classes cellules plutôt qu'un héritage

À l'origine, nous voulions partir sur une classe de base `Cellule` dont `ColorCell` et `ChromoCell` hériteraient, ce qui aurait permis une population unique d'un point de vue conceptuel. Le devoir interdisant tout héritage, nous sommes partis sur **deux classes cellules indépendantes** ; la généricité est assurée par les templates `Individu<T>` et `Population<T>`.

Le choix des représentations :

- `ColorCell` : trois `int` pour les canaux R, G et B (0 à 255) — l'addition de deux cellules donne la moyenne composante par composante : `R3 = (R1+R2)/2`, etc. ;
- `ChromoCell` : un `std::array<char, 8>` — la structure la moins coûteuse pour stocker huit caractères fixes `[gauche1, droite1, …, gauche4, droite4]`. L'addition prend le chromosome gauche du premier parent et le droit du second pour chaque paire : `AB CD EF GH + IJ KL AC BD = AJ CL EC GD`.

### 3. Un catalogue indexé plutôt qu'un arbre classique

La généalogie du devoir n'est pas un « vrai » arbre à parcourir comme une structure chaînée : chaque individu possède un **identifiant séquentiel** commençant à 1. Un `std::vector<Individu<T>*>` offre alors un accès direct en **O(1)** (`index = id - 1`) et le tableau s'agrandit de lui-même — chaque nouvel individu est ajouté à la fin avec `push_back`, ce qui garantit que son id correspond toujours à sa position. La structure de données « arbre » émerge simplement des pointeurs `parent1`/`parent2` stockés dans chaque `Individu`.

### 4. Suppression par tombstone

Pour préserver la relation `id = index + 1`, un individu supprimé n'est **pas** retiré du vector (`erase` décalerait tous les indices suivants et casserait les identifiants). Sa case passe simplement à `nullptr` — une « pierre tombale ». Les enfants dont un parent a été supprimé affichent `inconnu` pour cette branche, et `delete nullptr` permet de libérer le vector sans test particulier.

### 5. Surcharge des opérateurs

Comme pour le TP1, les responsabilités de lecture/écriture sont réparties par surcharge d'opérateurs et fonctionnent en cascade : les `<<` / `>>` de `ColorCell` et `ChromoCell` servent ceux d'`Individu`, qui servent à leur tour ceux de `Population`. La population sait ainsi se sérialiser complètement (`out << pop` / `in >> pop`), et le gestionnaire de fichiers `Manager` ne fait que canaliser le flux. La surcharge d'`operator+` sur les cellules implémente les règles d'addition de l'énoncé, utilisée directement par la transaction `+ X Y`.

### 6. Ancêtre commun le plus proche

La recherche remonte les parents par un parcours récursif depuis chacun des deux individus demandés, en mémorisant pour chaque ancêtre rencontré la distance la plus courte. On retient ensuite l'ancêtre commun qui minimise la somme des deux distances.

---

## Points discutés

Certains points laissés flous par l'énoncé ont fait l'objet de choix documentés :

- **Ancêtres ex æquo** : si deux ancêtres communs sont à distance égale, le programme affiche le premier trouvé ;
- **Lecture stricte des transactions** : un fichier mal formé continue d'être lu token par token et chaque symbole non reconnu produit `operation inconnue`, plutôt que d'avaler silencieusement la fin de la ligne ;
- **Sauvegarde après suppressions** : les ids écrits conservent leur valeur d'origine (des « trous » peuvent donc apparaître) ; le format de fichier séquentiel de l'énoncé ne prévoit pas le rechargement de telles sauvegardes.

## Utilisation d'outils d'IA générative

Developer A : WAFO FOKO Franck Mael
-
Les outils d'IA générative ont été utilisés pour :
- Validation de l'implémentation et des choix architecturaux.
- Génération de gros fichiers de transaction pour tester différents cas possibles.

Developer B : FRANCK MARIUS NJIKE NFANGA
Les outils d'IA générative ont été utilisés pour :
- 

Developer C : HOUNDETON BOTON Harold
Les outils d'IA générative ont été utilisés pour :
- 


---
La conception et l'implémentation ont été réalisées et validées par l'équipe.
