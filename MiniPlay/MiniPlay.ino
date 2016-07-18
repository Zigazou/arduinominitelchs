// Uncomment following line to enable debug messages
#define DEBUG

#ifdef DEBUG
 #define DEBUG_PRINT(x)  Serial.println (x)
 #define DEBUG_PRINT_(x)  Serial.print (x)
 #define DEBUG_PRINTD(x)  Serial.println (x, DEC)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINT_(x)
 #define DEBUG_PRINTD(x)
#endif

// Bibliothèque de lecture de carte SD
#include <SD.h>

// Bibliothèque de port série logiciel adaptée au Minitel
#include "SoftwareSerialExtended.h"

// Broches du port série logiciel
#define RXPIN 2
#define TXPIN 3

// Broche du lecteur de carte SD
#define CHIPSELECT 10

// Définition du port série logiciel
//SoftwareSerialMinitel minitelSerial(RXPIN, TXPIN); // (RX/TX)
SoftwareSerialExtended minitelSerial(RXPIN, TXPIN); // (RX/TX)

// Garde trace des noms des fichiers de page et commandes en cours
String pageActuelle;
String commandesActuelles;
long inactivite;

typedef union {
  char raw[32];
  struct {
    char type;
    long touche;
    char page[27];
  } action;
} Enregistrement;

// ************************************************************************
//
// Initialisation
//
// ************************************************************************
void setup() {
#ifdef DEBUG
  Serial.begin(57600);
  while (!Serial);
#endif
  
  // Test si la carte SD est disponible et lisible
  DEBUG_PRINT ("Tentative de lecture de la carte SD");
  if (!SD.begin(CHIPSELECT)) {
    minitelSerial.println("Impossible de lire la carte SD");
    DEBUG_PRINT ("Impossible de lire la carte SD");
    return;
  }

  // Activation du port série logiciel
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);

  DEBUG_PRINT ("Initialisation de la liaison serie avec le Minitel");
  minitelSerial.begin(1200, 7);

  // Affiche le nom de l'association dans la ligne de service
  DEBUG_PRINT ("Affichage du nom de l'association sur la ligne de statut");
  minitelSerial.write(0x1f);
  minitelSerial.write(0x40);
  minitelSerial.write(0x41);
  minitelSerial.print("Centre d'Histoire Sociale          ");
  minitelSerial.write(0x0a);

  // Affiche la page racine
  afficherPage("racine/racine.vdt");
}

// ************************************************************************
//
// Boucle principale
//
// ************************************************************************
void loop() {
  long touche;

  // Récupère un éventuel caractère envoyé par le Minitel
  touche = lireTouche();

  // Si le code est différent de 0, il faut exécuter l'action correspondante
  if(touche != 0) executerTouche(touche, 'T');
}

// ************************************************************************
// Fonction lireTouche
// Lit une éventuelle touche tapée sur le Minitel
// Si aucune touche n'a été frappée, la fonction retourne la valeur 0
// ************************************************************************
long lireTouche() {
  long touche = 0;
  long c;

  minitelSerial.listen();
  while(minitelSerial.available() > 0 && (c = minitelSerial.read()) != -1) {
    touche = (touche << 8) + c;

    // Petit délai pour voir si le minitel n’a pas d’autres caractères à envoyer
    delay(20);
  }  

  return touche;
}

// ************************************************************************
// Fonction afficherPage
// Envoit une page complète au Minitel
// ************************************************************************
void afficherPage(char *page) {
  File vdtFile;

  DEBUG_PRINT_ ("Affichage d'une page : ");
  DEBUG_PRINT (page);

  // Copie le nom de la page
  pageActuelle = String(page);

  // Génère le nom du fichier de commandes à partir du nom de fichier de la page
  commandesActuelles = pageActuelle;
  commandesActuelles.replace(".vdt", ".cmd");

  // Ouvre la page à afficher
  if(vdtFile = SD.open(pageActuelle.c_str(), FILE_READ)) {
    DEBUG_PRINT ("Lecture du fichier VDT");
    // Affiche la page caractère par caractère
    int16_t octet;
    while((octet = vdtFile.read()) != -1) minitelSerial.write((char)octet);

    // Ferme le fichier
    DEBUG_PRINT ("Fermeture du fichier VDT");
    vdtFile.close();
  } else {
    minitelSerial.write(0x07);
    DEBUG_PRINT ("Fichier non trouve : ");
    DEBUG_PRINT (pageActuelle.c_str());
    minitelSerial.println("Fichier non trouve : ");
    minitelSerial.println(pageActuelle.c_str());
  }
}

// ************************************************************************
// Fonction executerTouche
// Tente de trouver l'action correspondante à la touche frappée
// En cas de succès, exécute l'action
// ************************************************************************
void executerTouche(long touche, byte type) {
  Enregistrement enregistrement;

  File cmdFile;
  int trouve;

  DEBUG_PRINT_ ("Ouverture du fichier de commandes : ");
  DEBUG_PRINT (commandesActuelles.c_str());

  // Récupère le nom du fichier de commandes
  cmdFile = SD.open(commandesActuelles.c_str(), FILE_READ);

  // Le fichier de commandes est un fichier d’enregistrements
  DEBUG_PRINT ("Recherche d'une commande a executer");
  trouve = 0;
  while(cmdFile.read(enregistrement.raw, sizeof(Enregistrement)) == sizeof(Enregistrement)) {
    // Traite uniquement les touches
    if(enregistrement.action.type != type) continue;

    if(type == 'D' || touche == enregistrement.action.touche) {
      // La touche a été trouvée, on n’en cherche pas d’autres
      trouve = 1;
      break;
    }
  }

  // Ferme le fichier
  cmdFile.close();

  if(trouve == 1) {
    DEBUG_PRINT ("Une commande a ete trouvee");
    afficherPage(enregistrement.action.page);
  } else {
    DEBUG_PRINT ("Aucune commande trouvee");
  }
}
