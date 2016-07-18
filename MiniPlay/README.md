MiniPlay
========

MiniPlay est le lecteur de fichiers binaires qui va permettre de jouer les
différents fichiers compilés et de passer de l’un à l’autre en fonction des
touches appuyées par l’utilisateur.

Le module `SoftwareSerialExtended` est une version spéciale de la bibliothèque
`SoftwareSerial` livrée en standard avec l’IDE de l’Arduino. Elle a été
modifiée afin d’ajouter le support du mode 7 bits avec bit de parité,
indispensable pour le Minitel dans son mode de fonctionnement standard (les
Minitel Magis quant à eux peuvent fonctionner à 9600 baud en 8 bits sans aucun
bit de parité).
