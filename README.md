# Element propres d'une matrice carrée de taille très grande

Ce projet intervient dans le cadre du cours de programmation parallèle à l'ISTY.
Il utiliser l'algorithme Padé-Rayleigh-Ritz (PRR). 
Que nous avons essayé de paralléliser avec l'outil OpenMP.


## Dépendances

Le projet utilise le package gsl de gnu.

```bash
apt sudo install libgsl-dev
```

## Usage

Nous déterminons où est installé le package gsl pour pouvoir l'utiliser au Makefile
```bash
. ./configure
```
Puis pour compiler nos fichiers et exécuter le code : 
```bash
make
./programme
```
