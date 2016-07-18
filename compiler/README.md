compilevdt et compilecmd
========================

Les programmes `compilevdt` et `compilecmd` compilent des fichiers XML en
binaires prêts à être joués par `MiniPlay`.

`compilevdt` génère un fichier rempli de codes VideoTexte (VDT) directement
interprétables par un Minitel.

`compilecmd` génère un fichier binaire uniquement lisible par `MiniPlay` et
qui contient une liste de touches associées à des fichiers VDT. Quand une
touche est pressée, `MiniPlay` recherche la touche dans le fichier. S’il la
trouve, il affiche le fichier VDT qui lui est associé.

Structure d’un fichier XML
--------------------------

Un fichier XML est structuré de la façon suivante :

    <?xml version="1.0" encoding="UTF-8"?>
    <page>
      <clavier>
        <!-- Liste des touches et de leurs pages associées -->
      </clavier>
      <affichage>
        <!-- Liste des commandes d’affichage -->
      </affichage>
    </page>

La section `clavier` permet de générer le fichier de commandes, la section
`affichage` permet de générer le fichier VDT.

S’agissant d’un fichier au format XML, les commentaires sont autorisés.

Balises de la section `clavier`
-------------------------------

La balise `clavier` accepte la balise `touche` :

    <touche nom="**A**" page="**B**" repertoire="**C**"/>

Attributs de la baliase `touche` :

- **A** : touche à intercepter. Les valeurs acceptées sont `a` à `z`, `A` à `Z`,
  `0` à `9`, `connexion`, `sommaire`, `annulation`, `retour`, `répétition`,
  `envoi`, `suite`, `correction`, `guide`, `ctrl+sommaire`, `ctrl+annulation`,
  `£`, `ctrl+retour`, `ctrl+répétition`, `ctrl+suite`, `ctrl+correction`,
  `maj+connexion`, `brk`, `maj+sommaire`, `maj+annulation`, `\`, `maj+retour`,
  `maj+répétition`, `maj+envoi`, `maj+suite`, `maj+correction`, `§`,
  `maj+guide`.
- **B** : le nom du fichier à afficher sans extension.
- **C** : le répertoire dans lequel le fichier se trouve par rapport à la
  racine. Il ne doit pas contenir de `/` au début ou à la fin.

Exemples de balises `touche` :

    <touche nom="1" page="apropos" repertoire="minitel"/>
    <touche nom="2" page="manif" repertoire="minitel"/>
    <touche nom="3" page="plan" repertoire="minitel"/>
    <touche nom="4" page="fourpain" repertoire="minitel"/>
    <touche nom="5" page="vapeur" repertoire="minitel"/>
    <touche nom="sommaire" page="racine" repertoire="racine"/>

Balises de la section `affichage`
---------------------------------

La balise `affichage` est beaucoup plus riche que la balise `clavier`.

`compilevdt` est notamment capable de :

- convertir un PNG en caractères semi-graphiques pour le Minitel,
- convertir les caractères accentués quand le Minitel les connaît.

Les balises acceptées sont :

### couleur

La balise `couleur` change les couleurs utilisées par le Minitel pour les
prochains caractères.

Elle accepte deux attributs :

- `caractere` (optionnel) = couleur d’avant-plan (voir Couleurs)
- `fond` (optionnel) = couleur d’arrière-plan (voir Couleurs)

### position

La balise `position` positionne le curseur pour les prochains caractères.

Elle requiert deux attributs et accepte un attributs optionnel :

- `colonne` = colonne 1 à 40
- `ligne` = ligne 0 à 24 (0 = ligne de statut)
- `rappel` (optionnel) = si l’attribut est présent, colonne et ligne
  fonctionnent en mode relatif, sinon en mode absolu

### taille

La balise `taille` change la taille des prochains caractères.

Elle requiert deux attributs :

- `largeur` = 1 ou simple, 2 ou double
- `hauteur` = 1 ou simple, 2 ou double

### soulignement

La balise `soulignement` active le soulignement pour les prochains caractères.

Elle requiert un seul attribut :

- `etat` = (voir Booléens)

### clignotement

La balise `clignotement` active le clignotement pour les prochains caractères.

Elle requiert un seul attribut :

- `etat` = (voir Booléens)

### insertion

La balise `insertion` repousse/écrase le texte qui suit.

Elle requiert un seul attribut :

- `etat` = (voir Booléens)

### echo

La balise `echo` affiche/n’affiche pas les touches tapées au clavier par
l’utilisateur.

Elle requiert un seul attribut :

- `etat` = (voir Booléens)

### video

La balise `video` active/désactive l’inversion vidéo des caractères.

Elle requiert un seul attribut :

- `etat` = `normal`, `inverse` ou `transparent`

### curseur

La balise `curseur` montre/cache le curseur

Elle requiert un seul attribut :

- `etat` = (voir Booléens)

### repete

La balise `repete` répète plusieurs fois un caractère ou une chaîne. Elle
est optimisée pour la répétition d’un caractère.

Elle requiert un seul attribut :

- `nombre` = nombre de répétitions

Le contenu de la balise correspond au contenu à répéter.

### texte

La balise `texte` affiche le texte contenu dans la balise.

Elle accepte un attribut optionnel :

- `largeur` (optionnel) = si une largeur est spécifiée, le texte subit
  automatiquement des retours à la ligne pour tenir dans la largeur indiquée.

### rectangle

La balise `rectangle` dessine un rectangle à une position donnée.

Elle requiert cinq attributs :

- `colonne` = 1 à 40
- `ligne` = 1 à 24
- `largeur` = nombre de colonnes à couvrir
- `hauteur` = nombre de lignes à couvrir
- `couleur` = couleur du rectangle (voir Couleurs)

### mode

La balise `mode` fait basculer le Minitel entre le mode texte et le mode
semi-graphique.

Elle requiert un attribut :

- `type` = `graphique` ou `texte`

### haut, bas, gauche, droite

Les balises `haut`, `bas`, `gauche` et `droite` permettent de déplacer le
curseur d’une case à la fois dans la direction voulue.

Elles n’acceptent aucun attribut.

### bip

La balise `bip` fait émettre un bip par le Minitel

Elle n’accepte aucun attribut.

### retourchariot

La balise `retourchariot` fait effectuer un retour chariot au Minitel (le
curseur est positionné au début de la ligne courante).

### minuscules, majuscules

Les balises `minuscules` et `majuscules` passent le clavier respectivement
en mode `minuscules` et en mode `majuscules`

Elles n’acceptent aucun attribut.

En mode `majuscules`, une lettre frappée au clavier sans l’appui d’aucune
autre touche sera envoyée en majuscule. C’est le mode par défaut du Minitel.

### inclure

La balise `inclure` permet d’inclure dynamiquement un autre fichier XML. Le
fichier peut être inclus autant de fois que nécessaire.

Elle requiert un attribut :

- `page` = le chemin relatif par rapport au fichier XML courant vers le
  fichier XML à inclure

### definir

La balise `definir` affecte une valeur à une variable qui pourra ensuite
être utilisée n’importe où dans le fichier XML, y compris à l’intérieur des
scripts inclus avec la balise `inclure`

Elle requiert un attribut :

- `nom` = nom de la variable

Le contenu de la variable correspond au contenu de la balise `definir`. Elle
peut contenir d’autres balises mais celles-ci seront évaluées lors de la
définition de la variable.

### variable

La balise `variable` insère le contenu d’une variable précédemment définie par
la balise `définir`.

Elle requiert un attribut :

- `nom` = nom de la variable

### image

La balise `image` convertit une image PNG en caractères semi-graphiques.

Elle requiert un attribut :
- `fichier` = nom du fichier à convertir

### code

La balise `code` insère un caractère brute dans le fichier VDT généré.

Elle requiert un attribut :

- `hex` = code hexadécimal du caractère brut à insérer

### efface

La balise `efface` efface une partie de l’écran.

Elle requiert un attribut `jusque` qui peut prendre les valeurs suivantes :

- `finligne` = efface du curseur jusqu’à la fin de la ligne
- `finecran` = efface du curseur jusqu’à la fin de l’écran
- `debutecran` = efface du début de l’écran jusqu’au curseur
- `tout` = efface tout l’écran (sauf la ligne de statut)
- `debutligne` = efface du début de la ligne jusqu’au curseur
- `ligne` = efface la ligne courante

### clavier

La balise `clavier` configure le mode de saisie du clavier.

Elle accepte les attributs :
- `etendu` (booléen)
- `simple` (booléen)

### attente

La balise `attente` insère un délai

- `duree` = flottant donnant le nombre de secondes à attendre pour une
  connexion de 1200 bauds

### redefinir

La balise `redefinir` permet de redéfinir des caractères. Cette commande ne
fonctionne qu’à partir du Minitel 2.

Elle requiert les attributs suivants :

- `depuis` = caractère de départ
- `jeu` = jeu de caractères à utiliser `G0` ou `G1`

le dessin est contenu dans la balise et est composé de `0` et de `1`, dans
une matrice de 8×10. Tout autre caractère est ignoré ce qui permet de présenter les matrices comme bon vous semble (sur une seule ligne ou sur 10 lignes de 8 chiffres).

Valeurs reconnues
-----------------

### Couleurs

Lorsqu’un attribut accepte une couleur, les valeurs possibles sont :

- un nom de couleur : `noir`, `rouge`, `vert`, `jaune`, `bleu`, `magenta`,
  `cyan` et `blanc`,
- un chiffre de 0 à 7, du moins lumineux au plus lumineux, 0 étant le noir et
  7 le blanc.

### Booléens

Un booléen peut prendre 2 valeurs :

- `ko`, `non`, `off`, `inactif`, `faux`, `invisible` pour faux
- `ok`, `oui`, `on`, `actif`, `vrai`, `visible` pour vrai
