Arduino-Minitel-CHS
===================

(Sorry, the whole project is in french…)

Arduino-Minitel-CHS est un projet permettant d’afficher des pages Minitel pour
une association de sauvegarde du patrimoine industriel (CHS =
[Centre d’Histoire Sociale](http://www.expotec103.com))

Les composants
--------------

Le projet est composé de plusieurs éléments :

- un dialecte XML de description de pages Minitel gérant l’appui de touches
  pour la navigation,
- un compilateur (lui-même composé de 2 exécutables) transformant le code XML
  en fichiers binaires prêts à être utilisés par l’afficheur,
- l’afficheur `MiniPlay` qui lit les fichiers binaires précédemment générés
  sur une carte SD pour les envoyer à un Minitel,
- le code source des fichiers composant le site complet.

Pré-requis et dépendances
-------------------------

Pour des informations plus détaillées, voir dans chacun des sous-répertoires
du projet.

Ce projet a besoin de :

### Édition et compilation des pages

Un Linux est nécessaire pour l’édition et la compilation des pages.

La compilation des pages nécessite **Python 2.7** et les dépendances
suivantes : **xml.dom.minidom, binascii, PIL, operator, struct**.

### Compilation et installation de MiniPlay

Un **Arduino Uno** (ou plus) est nécessaire.

Pour compiler MiniPlay, vous aurez besoin de l’environnement de développement
standard de l’Arduino.

Les dépendances suivantes doivent être installées et disponibles :
**SdFat, SoftwareSerialMinitel, Wire, RTClib**.
