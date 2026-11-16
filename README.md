# TP_2 — Arborescence génétique (8INF259)

Travail pratique 2 — Structures de données, UQAC, Automne 2026.
**Remise : 18 novembre 2026, 23h55** (zip `nom_prenom_nom_prenom.zip` sur Moodle).

## Équipe et répartition

| Dev | Fichiers | Rôle |
|---|---|---|
| **A** | `Individu.h`, `Population.h` | Node + catalogue : ajouter, additionner (+), supprimer (-), ancêtre commun (?) |
| **B** | `Cellules.h`, `Affichage.h` | ColorCell/ChromoCell (+, <<, >>) + affichage arbre ($) |
| **C** | `TP_2.cpp` (main), `IO.h` | Lecture TRANSACTIONS.txt, switch des opérations, charger (O) / sauvegarder (S) |

## Directives

1. **Chacun complète uniquement ses fichiers** — les signatures des `.h` sont le
   contrat commun : on ne les change pas sans en parler à l'équipe.
2. Les `TODO [Dev X]` indiquent qui code quoi.
3. **Héritage INTERDIT** (consigne du prof) — généricité par templates uniquement.
4. Librairie standard C++ uniquement.
5. Les fonctions template s'implémentent **dans le .h** (règle C++).
6. Le programme se lance avec le fichier de transactions en argument :
   `TP_2.exe TRANSACTIONS.txt`
7. Avant de push : le projet **doit compiler**. On ne push pas du code cassé sur main.

## Opérations à supporter (TRANSACTIONS.txt)

| Op | Signification |
|---|---|
| `C` | Créer une nouvelle population (type courant) |
| `A` | Ajouter un individu sans parents |
| `O` | Charger une population depuis un fichier |
| `S` | Sauvegarder la population dans un fichier |
| `+ X Y` | Créer un enfant de X et Y (fusion des valeurs) |
| `- X` | Supprimer l'individu X (tombstone) |
| `? X Y` | Ancêtre commun le plus proche de X et Y |
| `$ X` | Afficher l'arbre généalogique de X |

## Git — mise en place (une fois, par le responsable du repo)

```bash
git init
git add .
git commit -m "squelette initial : .h du contrat + gitignore + readme"
git branch -M main
git remote add origin https://github.com/wafomael/TP_2.git
git push -u origin main
```

## Git — workflow quotidien (tout le monde)

```bash
# 1. Récupérer le dépôt (première fois)
git clone https://github.com/wafomael/TP_2.git

# 2. TOUJOURS se mettre à jour avant de travailler
git pull

# 3. Travailler dans SES fichiers, puis :
git add Cellules.h            # ajouter ses fichiers modifiés (pas git add . à l'aveugle)
git commit -m "ColorCell : operator+ et operator<<"
git pull                      # intégrer les changements des autres AVANT de push
git push

# Voir l'état / l'historique
git status
git log --oneline
```

### Règles d'équipe

- **Messages de commit clairs** : `"Population : supprimer() avec tombstone"` plutôt que `"update"`.
- `git pull` avant de commencer ET avant de push — ça évite 90 % des conflits.
- Conflit sur un fichier qui n'est pas à toi → voir son propriétaire, ne pas résoudre à l'aveugle.
- Ne jamais commiter `.vs/`, `x64/`, `*.exe` (le `.gitignore` s'en charge déjà).

## Compilation

- **Visual Studio** : ouvrir `TP_2.slnx`, build en Debug x64.
- **Ligne de commande (g++)** :
  ```bash
  g++ -std=c++17 -o TP_2 TP_2.cpp
  ./TP_2 TRANSACTIONS.txt
  ```
