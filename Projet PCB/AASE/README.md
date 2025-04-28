# AASE_Nehari_Chauveliere

## Objectif

L'obejctif initial de ce projet est de concevoir et réaliser la partie récepton d'une chaîne de réception en modulation numérique BPSK.

## Kicad schématique

Tout d'abord, nous avons dû créer notre carte électronique sur Kicad, pour cela nous sommes partis du précédent projet réalisé en TMS. De ce projet nous avons conservé le microcontrôleur (STM32) et le capteur de température (MCP9000) principalement.

Nous avons ensuite ajouté ce dont on avait besoin, c'est-à-dire :
- Quartz haute fréquence pour le STM32, MCSJK-7U-32.00-10-30-60-B-30;
- LDO positif pour convertir du +15V venant d'un générateur en +8V pour le démodulateur, AP7333-33SAG-7;
- LDO négatif pour convertir du -15V venant d'un générateur en -8V pour le démodulateur, MIC5271YM5-TR;
- Mosfet de puissance, XP161A1355PR-G;
- Convertisseur boost pour convertir du +1.8V venant d'une batterie vers du +3.3V, XC9103D095MR-G;
- Diode schottky pour le convertisseur boost, D0-214AC;
- Connecteurs divers.

## Kicad Rootage

Nous avons eu que très peu de soucis pour cette partie là.
Les tailles des pistes ont été choisies pour avoir une impédance adéquate.
Les plans de masse ont été placés de telle sorte à éviter la création d'antenne dans le PCB.
Nous avons aussi bien isolé les composants hautes fréquences du reste du circuit.

## Déphaseur

Plus tard, nous avons décidé de créer le circuit déphaseur du démodulateur BPSK.
Sur ce PCB, nous avons placé des connecteurs SMA car nous travaillons en haute fréquence.
La taille des pistes a été calculée pour avoir une impédance de 50 ohms

##Soudure et tests

Nous avons d'abord soudé les composants principaux afin de pouvoir tester simplement le clignotement d'une led.
Utilisation d'air chaud pour souder le quartz et de flux pour faciliter le travail.
Nous avons programmé le STM32 grâce à l'ide STM32CubeIDE.

Enfin, nous avons soudé le capteur de température, celui-ci nous donnant une valeur de 0.733V.
Selon la datasheet de ce capteur celaindique une température aux alentours des 20°c.
Nous pouvons donc en déduire qu'il fonctionne correctement.

## Consommation d'un STM32

Nous avons fait plusieurs tests sur la consommation d'une board Nucleo STM32 (résultats dans le dossier Vidéo consommation).
On peut noter que les résultats sur la consommation en fonction de la fréquence ne sont pas ceux espérés.
Nous aurions dû trouver une fonction en forme parabolique avec en sommet la fréquence idéale.

## Post-scriptum

A noter, que nous avons eu 4H de moins que les autres groupes car nous avons eu 3 séances de 4H avec Mr.Wichmann.