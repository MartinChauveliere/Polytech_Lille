# Projet PCB - STM32F030F4Px

**Conception d'un circuit imprimé (PCB) avec KiCad**  
**Durée totale estimée : 4 heures**

---

## Composants principaux

- **Microcontrôleur** : STM32F030F4Px  
- **Capteur de température** : MCP9700T-ETT (boîtier SOT-23-3)  
- **Mémoire** : M24C01-RDW  
- **LEDs de test**  
- **Condensateurs de découplage** : valeur à définir (F)

---

## Chronologie du projet

### 1ère heure - Choix des composants & Schéma électrique

- Sélection et ajout des composants dans KiCad.
- Lecture des datasheets pour configurer correctement les connexions.
- **Notes importantes** :
  - **M24C01-RDW** : Les bits **E0**, **E1**, **E2** (Chip Enable) doivent être fixés à **0** pour permettre la communication (valable pour le package **DFN5**).
- Début de la création du schéma électrique (`Schematic`) à partir des spécifications des datasheets.

---

### 2ème heure - Outils supplémentaires et finalisation du schéma

- **Installation de la librairie SparkFun** pour ajouter un bouton Reset au microcontrôleur.
- Utilisation de l'**ASN4325** pour la configuration précise du schéma du contrôleur.
- Finalisation du schéma (reportée en partie à la 3ème heure).

---

### 3ème heure - Interface de programmation et préparation PCB

- Passage de la programmation via **SWD** (Serial Wire Debug) au lieu de l'**AVR ISP** (suppression du connecteur ISP).
- Ajout du **footprint pour le quartz** : **HC49**.
- Conception du schéma du connecteur SWD.
- Finalisation du schéma électrique complet.
- Attribution des **footprints** aux composants.
- Début du **routage PCB**.

---

### 4ème heure - Finalisation

- Fin du **routage du PCB**.
- Génération des fichiers de fabrication (`Gerber files`).
- Envoi du projet en fabrication.

---

## Programmation

En suivant les étapes données par le sujet et le site :  
[https://linuxembedded.fr/2021/02/bare-metal-from-zero-to-blink](https://linuxembedded.fr/2021/02/bare-metal-from-zero-to-blink)

Nous sommes parvenus à :

- Écrire la configuration de la carte (`stm32_startup.c`, `main.c` et `final.map`)
- Créer la librairie `stm32_ls.ld`

Dans cette configuration, nous avons :

- Défini la table de vecteurs
- Initialisé la pile
- Initialisé le segment BSS

**Remarques** :

- Le tutoriel comprenait quelques erreurs à repérer (au niveau des caractères) et quelques adaptations étaient nécessaires (par exemple la fréquence).
- Nous avons finalement réussi à flasher notre code dans la carte (à l'aide de `gdb`).
- Cependant, nous suspectons une maladresse au niveau de la soudure qui nous a empêchés de voir la LED clignoter.

Ce qui reste certain est que le code a bien été flashé dans la carte !

---

## Infos supplémentaires

- Outils utilisés : **KiCad** (v6 ou v7 recommandé)
- Technologies de communication : **SWD** pour la programmation et le debug du STM32.
- Important : vérifier les tensions de fonctionnement compatibles entre tous les composants.

---

## À faire (améliorations possibles)

- Définir précisément la valeur des condensateurs de découplage.
- Ajouter des protections ESD si nécessaire.
- Vérifier les largeurs de pistes selon l'intensité prévue (règles IPC-2221).

