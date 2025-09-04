# 🍽️ Philosophers

## 📖 Présentation
**Philosophers** est un projet de l’école 42 qui met en œuvre le problème classique des **philosophes mangeurs**.  
L’objectif est de gérer la synchronisation entre plusieurs threads représentant des philosophes qui mangent, pensent et dorment autour d’une table, en partageant un nombre limité de fourchettes.  

Ce projet permet de se familiariser avec :  
- Les threads en C.  
- Les mutex pour gérer les ressources partagées.  
- Les problèmes de synchronisation (deadlock, starvation).  

---

## 🎯 Objectifs et Contraintes
- Chaque philosophe est représenté par un thread indépendant.  
- Chaque philosophe doit alternativement : **manger**, **dormir**, **penser**.  
- Un philosophe ne peut manger que s’il a deux fourchettes (mutex).  
- Le programme prend en paramètre :  
  1. `number_of_philosophers`  
  2. `time_to_die` (ms)  
  3. `time_to_eat` (ms)  
  4. `time_to_sleep` (ms)  
  5. `[number_of_times_each_philosopher_must_eat]` (optionnel)  

- Le programme doit arrêter la simulation si :  
  - Un philosophe meurt de faim (dépasse `time_to_die`).  
  - Tous les philosophes ont mangé au moins le nombre requis de fois (si l’argument optionnel est fourni).  

- Contraintes supplémentaires :  
  - Pas d’utilisation de variables globales.  
  - Pas de data races ni de comportements indéfinis.  
  - Gestion stricte des mutex pour éviter les deadlocks.  

---

## 🚀 Utilisation

### 1️⃣ Compilation
Dans le répertoire du projet, lancer : 
```bash
make  
```
Cela génère l’exécutable :  
``` bash
./philo  
```

### 2️⃣ Lancement de la simulation
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]  
```

Exemple :  
```bash
./philo 5 800 200 200  
```

Ce qui simule 5 philosophes, chacun ayant :  
- 800ms avant de mourir s’il ne mange pas.  
- 200ms pour manger.  
- 200ms pour dormir.  

### 3️⃣ Exemple avec l’argument optionnel
```bash
./philo 5 800 200 200 7  
```

Dans ce cas, la simulation s’arrête lorsque chaque philosophe a mangé au moins 7 fois.  

---

## 🛠️ Exemple de sortie
Philosophe 1 est en train de manger  
Philosophe 2 est en train de penser  
Philosophe 3 est en train de dormir  
Philosophe 4 est en train de manger  
Philosophe 5 est en train de penser  
...  

