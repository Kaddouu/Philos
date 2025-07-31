# Philosophers (Dining Philosophers Problem)

Ce projet est une implémentation du problème classique des philosophes mangeurs (Dining Philosophers Problem) en C, utilisant les threads POSIX (pthreads) et les mutex pour la synchronisation. Il s'agit d'un exercice courant pour apprendre la gestion de la concurrence, la synchronisation et la prévention des conditions de compétition.

## Description du projet

Le but est de simuler un certain nombre de philosophes assis autour d'une table, chacun alternant entre manger, penser et dormir. Chaque philosophe a besoin de deux fourchettes (représentées par des mutex) pour manger. Le projet gère les cas particuliers (un seul philosophe, arrêt de la simulation, etc.) et évite les conditions d'interblocage (deadlock).

![Philo](https://github.com/user-attachments/assets/10064efc-8b7a-4acf-b241-68d6bcb88834)

## Compilation

Pour compiler le projet, utilisez simplement la commande suivante dans le dossier du projet :

```sh
make
```

Cela génère un exécutable nommé `philo`.

## Exécution

L'exécutable `philo` attend les arguments suivants :

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` : nombre de philosophes et de fourchettes (>= 1)
- `time_to_die` : temps (en ms) avant qu'un philosophe ne meure s'il ne mange pas
- `time_to_eat` : temps (en ms) qu'un philosophe passe à manger
- `time_to_sleep` : temps (en ms) qu'un philosophe passe à dormir
- `number_of_times_each_philosopher_must_eat` (optionnel) : si spécifié, la simulation s'arrête quand chaque philosophe a mangé ce nombre de fois

### Exemple

```sh
./philo 5 800 200 200
```

Lance une simulation avec 5 philosophes, chaque philosophe meurt s'il ne mange pas pendant 800 ms, mange pendant 200 ms, puis dort pendant 200 ms.

```sh
./philo 5 800 200 200 7
```

Même simulation, mais la simulation s'arrête quand chaque philosophe a mangé 7 fois.

## Fichiers principaux

- `main.c` : point d'entrée du programme
- `philo.h` : définitions des structures et prototypes
- `eating_functions.c` : gestion des actions de prise de fourchettes, repas, etc.
- `philo_routine.c` : routine principale des philosophes
- `monitor.c` : surveillance de la mort des philosophes
- `parsing.c` : parsing et validation des arguments
- `simulation.c` : initialisation et gestion de la simulation
- `utils.c` : fonctions utilitaires

## Dépendances

- POSIX Threads (pthread)
