#include "fonction.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

Image::Image() {
  _largeur = 0;
  _longueur = 0;
}


Image::Image(const vector<vector<int>> &rouge, const vector<vector<int>> &vert,
             const vector<vector<int>> &bleu) {
  _rouge = rouge;
  _vert = vert;
  _bleu = bleu;
  _longueur = _rouge.size();
  _largeur = _rouge[0].size();

  if (_longueur != _vert.size() || _largeur != _vert[0].size() ||
      _longueur != _bleu.size() || _largeur != _bleu[0].size()) {
    throw invalid_argument("Error probleme de dimension !");
  }
}

int Image::Getlongueur(){//retourne la longueur de l'image
  return _longueur;
}

int Image::Getlargeur(){//retourne la largeur de l'image
  return _largeur;
}

void Image::Affichage() const {
  cout << "-------- display red vector--------" << endl;
  for (int i = 0; i < _rouge.size(); i++) {
    for (int j = 0; j < _rouge[i].size(); j++) {
      cout << _rouge[i][j] << " ";
    }
    cout << endl;
  }
  cout << "-------- display green vector------" << endl;
  for (int i = 0; i < _vert.size(); i++) {
    for (int j = 0; j < _vert[i].size(); j++) {
      cout << _vert[i][j] << " ";
    }
    cout << endl;
  }

  cout << "-------- display blue vector--------" << endl;
  for (int i = 0; i < _bleu.size(); i++) {
    for (int j = 0; j < _bleu[i].size(); j++) {
      cout << _bleu[i][j] << " ";
    }
    cout << endl;
  }
}

Image Image::composanteRouge() {

  Image m(_rouge, _vert, _bleu);

  for (int i = 0; i < _vert.size(); i++) { // vector vert
    for (int j = 0; j < _vert[i].size(); j++) {
      m._vert[i][j] = 0;
    }
  }

  for (int i = 0; i < _bleu.size(); i++) { // vector bleu
    for (int j = 0; j < _bleu[i].size(); j++) {
      m._bleu[i][j] = 0;
    }
  }
  return m;
}

bool Image::detection(int r, int v, int b) {
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      if (_rouge[i][j] == r && _vert[i][j] == v && _bleu[i][j] == b) {
        return true;
      }
    }
  }
  return false;
}

Image Image::niveauxGris() const {
  int moy;
  Image m(_rouge, _vert, _bleu);
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      moy = _rouge[i][j] + _vert[i][j] + _bleu[i][j];
      moy = moy / 3;
      m._rouge[i][j] = moy;
      m._vert[i][j] = moy;
      m._bleu[i][j] = moy;
    }
  }
  return m;
}

Image Image::noirEtblanc() const {

  Image m = niveauxGris();
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      if (m._rouge[i][j] < 170) {
        m._rouge[i][j] = 0;
        m._vert[i][j] = 0;
        m._bleu[i][j] = 0;
      } else if (m._rouge[i][j] >= 170) {
        m._rouge[i][j] = 255;
        m._vert[i][j] = 255;
        m._bleu[i][j] = 255;
      }
    }
  }
  return m;
}

void Image::visionProtanopie() {
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      if (_rouge[i][j] == 255 && _vert[i][j] == 0 && _bleu[i][j] == 0) {
        _rouge[i][j] = 107;
        _vert[i][j] = 92;
        _bleu[i][j] = 11;
      } else if (_rouge[i][j] == 0 && _vert[i][j] == 0 && _bleu[i][j] == 255) {
        _rouge[i][j] = 0;
        _vert[i][j] = 56;
        _bleu[i][j] = 253;
      } else if (_rouge[i][j] == 0 && _vert[i][j] == 255 && _bleu[i][j] == 0) {
        _rouge[i][j] = 254;
        _vert[i][j] = 237;
        _bleu[i][j] = 1;
      }
    }
  }
}

void Image::visionTritanopie() {
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      if (_rouge[i][j] == 255 && _vert[i][j] == 0 && _bleu[i][j] == 0) {
        _rouge[i][j] = 255;
        _vert[i][j] = 0;
        _bleu[i][j] = 78;
      } else if (_rouge[i][j] == 0 && _vert[i][j] == 0 && _bleu[i][j] == 255) {
        _rouge[i][j] = 0;
        _vert[i][j] = 98;
        _bleu[i][j] = 137;
      } else if (_rouge[i][j] == 0 && _vert[i][j] == 255 && _bleu[i][j] == 0) {
        _rouge[i][j] = 121;
        _vert[i][j] = 233;
        _bleu[i][j] = 255;
      }
    }
  }
}

void Image::visionDeuteranopie() {
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      if (_rouge[i][j] == 255 && _vert[i][j] == 0 && _bleu[i][j] == 0) {
        _rouge[i][j] = 165;
        _vert[i][j] = 139;
        _bleu[i][j] = 0;
      } else if (_rouge[i][j] == 0 && _vert[i][j] == 0 && _bleu[i][j] == 255) {
        _rouge[i][j] = 0;
        _vert[i][j] = 86;
        _bleu[i][j] = 253;
      } else if (_rouge[i][j] == 0 && _vert[i][j] == 255 && _bleu[i][j] == 0) {
        _rouge[i][j] = 241;
        _vert[i][j] = 209;
        _bleu[i][j] = 49;
      }
    }
  }
}

vector<int> Image::HistogrammeGris() {
  vector<int> histo;
  Image G = this->niveauxGris();
  int countp = 0;
  int Apparait = 0;
  while (countp < 256) {
    for (int i = 0; i < _longueur; i++) {
      for (int j = 0; j < _largeur; j++) {
        if (G._rouge[i][j] == countp) {
          ++Apparait;
        }
      }
    }
    ++countp;
    histo.push_back(Apparait);
  }
  return histo;
}

Image Image::luminosityUp(float n) const {
  Image m(_rouge, _vert, _bleu);
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      m._rouge[i][j] *= n;
      m._vert[i][j] *= n;
      m._bleu[i][j] *= n;
      if (m._bleu[i][j] > 255) {
        m._bleu[i][j] = 255;
      }
      if (m._vert[i][j] > 255) {
        m._vert[i][j] = 255;
      }
      if (m._rouge[i][j] > 255) {
        m._rouge[i][j] = 255;
      }
    }
  }
  return m;
}

Image Image::luminosityDown(float n) const {
  Image m(_rouge, _vert, _bleu);
  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur; j++) {
      m._rouge[i][j] *= n;
      m._vert[i][j] *= n;
      m._bleu[i][j] *= n;
    }
  }
  return m;
}

Image Image::contrasteDown(){
  cout << "Entrez la distance (elle doit etre entre 1 et 0) :"<<endl;
  float resp;
  cin >> resp;
  Image m;
  m._longueur = _rouge.size();
  m._largeur = _rouge[0].size();
  while (resp > 1 || resp < 0) {
      cout << "LA VALEUR DOIT ETRE ENTRE 1 ET O :"<<endl;
      cin >> resp;
  }
  for (int i = 0; i < _longueur; ++i) {
    m._rouge.push_back(vector<int>{});
    m._vert.push_back(vector<int>{});
    m._bleu.push_back(vector<int>{});
    for (int k = 0; k < _largeur; ++k) {
      m._rouge[i].push_back((_rouge[i][k] - 128) * resp + 128);
      m._vert[i].push_back((_vert[i][k] - 128) * resp + 128);
      m._bleu[i].push_back((_bleu[i][k] - 128) * resp + 128);
    }
  }
  return m;
}

Image Image::contrasteUp(){
  Image m;
    m._longueur = _rouge.size();
    m._largeur = _rouge[0].size();
    float resp;
    cout << "Veillez entrer un nombre superieur � 1 "<<endl;
    cin >> resp;
    while (resp < 1) {
      cout << "UN NOMBRE SUPERIEUR A 1 SVP :"<<endl;
      cin >> resp;
    }
    for (int i = 0; i < _longueur; ++i) {
      m._rouge.push_back(vector<int>{});
      m._vert.push_back(vector<int>{});
      m._bleu.push_back(vector<int>{});
      for (int j = 0; j < _largeur; ++j) {
        m._rouge[i].push_back((_rouge[i][j] - 128) * resp + 128);
        if (m._rouge[i][j] > 255) {
          m._rouge[i][j] = 255;
        }
        if (m._rouge[i][j] < 0) {
          m._rouge[i][j] = 0;
        }
        m._vert[i].push_back((_vert[i][j] - 128) * resp + 128);
        if (m._vert[i][j] > 255) {
          m._vert[i][j] = 255;
        }
        if (m._vert[i][j] < 0) {
          m._vert[i][j] = 0;
        }
        m._bleu[i].push_back((_bleu[i][j] - 128) * resp + 128);
        if (m._bleu[i][j] > 255) {
          m._bleu[i][j] = 255;
        }
        if (m._bleu[i][j] < 0) {
          m._bleu[i][j] = 0;
        }
      }
    }
    return m;
}





void Image::writeFile(ofstream &stream) {
  stream << "P3" << endl;
  stream << _largeur << endl;
  stream << _longueur << endl;
  stream << "255" << endl;
  for (int i = 0; i < _rouge.size(); i++) {
    for (int j = 0; j < _rouge[0].size(); j++) {
      stream << _rouge[i][j] << " " << _vert[i][j] << " " << _bleu[i][j]
             << endl;
    }
  }
}

void loadPicture(const string &picture, vector<vector<int>> &rouge,
                 vector<vector<int>> &vert, vector<vector<int>> &bleu) {
  // Declaration des variables
  string line; // pour recuperer les lignes du fichier image au format.ppm, qui
               // est code en ASCII.
  string format; // pour recuperer le format de l'image : celui-ci doit �tre de
                 // la forme P3
  string name;   // au cas o� l'utilisateur se trompe dans le nom de l'image a
                 // charger, on redemande le nom.
  int taille;
  vector<int> mypixels; // pour recuperer les donnees du fichier de maniere
                        // lineaire. On repartira ensuite ces donnees dans les
                        // tableaux correspondants
  ifstream entree; // Declaration d'un "flux" qui permettra ensuite de lire les
                   // donnees de l'image.
  int hauteur;     // pour bien verifier que l'image est carree, et de taille
                   // respectant les conditions fixees par l'enonce
  // Initialisation des variables
  name = picture;
  // Permet d'ouvrir le fichier portant le nom picture
  // ouverture du fichier portant le nom picture
  entree.open(name);
  // On verifie que le fichier a bien ete ouvert. Si cela n'est pas le cas, on
  // redemande un nom de fichier valide
  while (!entree) {
    // cin.rdbuf(oldbuf);
    cerr << "Erreur! Impossible de lire de fichier " << name << " ! " << endl;
    cerr << "Redonnez le nom du fichier a ouvrir SVP. Attention ce fichier "
            "doit avoir un nom du type nom.ppm."
         << endl;
    cin >> name;
    entree.open(name); // relance
  }
  // Lecture du nombre definissant le format (ici P3)
  entree >> format;
  // on finit de lire la ligne (caractere d'espacement)
  getline(entree, line);
  // Lecture du commentaire
  getline(entree, line);
  // lecture des dimensions
  entree >> taille >> hauteur;
  getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
  // On verifie que l'image a une taille qui verifie bien les conditions
  // requises par l'enonce. Si cela n'est pas le cas, on redemande un fichier
  // valide, et ce, tant que necessaire.
  while (format != "P3") {
    if (format != "P3") {
      cerr << "Erreur! L'image que vous nous avez donnee a un format ne "
              "verifiant pas les conditions requises."
           << endl;
      cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et "
              "non en brut."
           << endl;
    }
    entree.close();
    // On va redemander un nom de fichier valide.
    do {
      cerr << "Veuillez redonner un nom de fichier qui respecte les conditions "
              "de format et de taille. Attention, ce nom doit etre de la forme "
              "nom.ppm."
           << endl;
      cin >> name;
      entree.open(name); // relance
    } while (!entree);
    // Lecture du nombre definissant le format (ici P3)
    entree >> format;
    getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    // Lecture du commentaire
    getline(entree, line);
    // lecture des dimensions
    entree >> taille >> hauteur; // relance
    getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
  }
  // Lecture de la valeur max
  getline(entree, line);
  // Lecture des donnees et ecriture dans les tableaux :
  //  Pour plus de simplicite, on stocke d'abord toutes les donnees dans
  //  mypixels dans l'ordre de lecture puis ensuite on les repartira dans les
  //  differents tableaux.
  // Les donnees stockees dans mypixels sont de la forme RGB RGB RGB ....
  //  Il faudra donc repartir les valeurs R correspondant a la composante rouge
  //  de l'image dans le tableau red, de m�me pour G et B.
  int pix;
  mypixels.resize(3 * taille *
                  hauteur); // taille fixe : on alloue une fois pour toutes
  for (int i = 0; i < 3 * taille * hauteur; i++) {
    entree >> pix;
    mypixels[i] = pix;
  }
  // Remplissage des 3 tableaux : on repartit maintenant les valeurs dans les
  // bonnes composantes Comme dans mypixels, les donnees sont stockees de la
  // maniere suivante : RGB RGB RGB, il faut mettre les valeurs correspondant a
  // la composante rouge dans red, ... Ainsi, les valeurs de la composante rouge
  // correspondent aux valeurs stockes aux indices congrus a 0 mod 3 dans
  // mypixels, que les valeurs de la composante verte correspond aux valeurs
  // stockes aux indices sont congrus a 1 mod 3, ...
  // les valeurs d'une ligne
  int val;
  rouge.resize(hauteur);
  vert.resize(hauteur);
  bleu.resize(hauteur);
  for (int i = 0; i < hauteur; i++) {
    vector<int> ligneR(taille);
    vector<int> ligneB(taille); // les lignes ont toutes la m�me taille
    vector<int> ligneG(taille);
    for (int j = 0; j < taille; j++) {
      val = mypixels[3 * j + 3 * taille * i];
      ligneR[j] = val;
      val = mypixels[3 * j + 1 + 3 * taille * i];
      ligneG[j] = val;
      val = mypixels[3 * j + 2 + 3 * taille * i];
      ligneB[j] = val;
    }
    rouge[i] = ligneR;
    vert[i] = ligneG;
    bleu[i] = ligneB;
  }
  // Informations a l'utilisateur pour dire que tout s'est bien passe
  cout << " L'image " << name << " a bien ete chargee dans les tableaux ."
       << endl;
  entree.close();
}

Image::Image(const string &picture) {
  loadPicture(picture, _rouge, _vert, _bleu);
  _largeur = _rouge[0].size();
  _longueur = _rouge.size();
}


void Image::Menu() {
    int result = 1;
    const Image original = *this;

    while (result >= 1 && result <= 21) {
        cout << "\n------------- Ceci est le menu --------------------" << endl;
        cout << "1 : Affichage de l' image." << endl;
        cout << "2 : Appliquer la composante rouge." << endl;
        cout << "3 : Verifier l' existence d' un pixel." << endl;
        cout << "4 : Convertir en niveaux de gris." << endl;
        cout << "5 : Convertir en noir et blanc." << endl;
        cout << "6 : Afficher l' histogramme des niveaux de gris." << endl;
        cout << "7 : Augmenter la luminosite." << endl;
        cout << "8 : Diminuer la luminosite." << endl;
        cout << "9 : Appliquer la vision Protanopie." << endl;
        cout << "10 : Appliquer la vision Tritanopie." << endl;
        cout << "11 : Appliquer la vision Deuteranopie." << endl;
        cout << "12 : Rogner le haut de l' image." << endl;
        cout << "13 : Rogner le bas de l' image." << endl;
        cout << "14 : Rogner la droite de l' image." << endl;
        cout << "15 : Rogner la gauche de l' image." << endl;
        cout << "16 : Rotation de l'image vers la droite." << endl;
        cout << "17 : Rotation de l'image vers la gauche." << endl;
        cout << "18 : Symetrie Verticale de l' image" << endl;
        cout << "19 : Symetrie Horizontale de l'image" << endl;
        cout << "20 : Agrandissement de l'image" << endl;
        cout << "21 : Retrecissement de l'image" << endl;
        cout << "22 : Quitter." << endl;
        cin >> result;

        //reinitialisation de l'image en celle de base
        if(result != 21){
                *this = original;
        }

        // Variables locales pour éviter des duplications inutiles
        float lumi;
        int r, v, b;
        int nb, facteur;

        switch (result) {
        case 1:
            cout << "Affichage de l image actuelle." << endl;
            Affichage();
            break;

        case 2:
            cout << "Application de la composante rouge." << endl;
            *this = composanteRouge(); // Mise à jour de l'instance actuelle
            cout << "Composante rouge appliquee." << endl;
            break;

        case 3:
            cout << "Verification de un pixel specifique." << endl;
            cout << "Entrez la valeur rouge : ";
            cin >> r;
            cout << "Entrez la valeur verte : ";
            cin >> v;
            cout << "Entrez la valeur bleue : ";
            cin >> b;
            if (detection(r, v, b)) {
                cout << "Le pixel (" << r << ", " << v << ", " << b << ") existe." << endl;
            } else {
                cout << "Le pixel n'existe pas." << endl;
            }
            break;

        case 4:
            cout << "Conversion de l image en niveaux de gris." << endl;
            *this = niveauxGris();
            cout << "Image convertie en niveaux de gris." << endl;
            break;

        case 5:
            cout << "Conversion de l image en noir et blanc." << endl;
            *this = noirEtblanc();
            cout << "Image convertie en noir et blanc." << endl;
            break;

        case 6:
            cout << "Affichage de l histogramme des niveaux de gris." << endl;
            for (int i = 0; i < 256; ++i) {
                cout << "Niveau " << i << ": " << HistogrammeGris()[i] << endl;
            }
            break;

        case 7:
            do {
                cout << "Entrez un facteur de luminosite (>1) : ";
                cin >> lumi;
            } while (lumi <= 1);
            *this = luminosityUp(lumi);
            cout << "Luminosite augmentee." << endl;
            break;

        case 8:
            do {
                cout << "Entrez un facteur de luminosite(0 < facteur < 1) : ";
                cin >> lumi;
            } while (lumi <= 0 || lumi >= 1);
            *this = luminosityDown(lumi);
            cout << "Luminosite diminuee." << endl;
            break;
        case 9:
            cout << "Conversion de l image pour les personnes atteintes de Protanopie." << endl;
            visionProtanopie();
            cout << "Image convertie pour vision Protanopie." << endl;
            break;

        case 10:
            cout << "Conversion de l image pour les personnes atteintes de Tritanopie." << endl;
            visionTritanopie();
            cout << "Image convertie pour vision Tritanopie." << endl;
            break;

        case 11:
            cout << "Conversion de l image pour les personnes atteintes de Deuteranopie." << endl;
            visionDeuteranopie();
            cout << "Image convertie pour vision Deuteranopie." << endl;
            break;

        case 12:
            cout << "Entrer le nombre de lignes que vous voulez rogner" << endl;
            cin >> nb;
            *this = rognerH(nb);
            cout << nb ;
            cout<< " ligne(s) en haut" << endl;
            break;

        case 13:
            cout << "Entrer le nombre de lignes que vous voulez rogner" << endl;
            cin >> nb;
            *this = rognerB(nb);
            cout << "Image rognee en bas" << endl;
            break;

        case 14:
            cout << "Entrer le nombre de colonnes que vous voulez rogner" << endl;
            cin >> nb;
            *this = rognerD(nb);
            cout << "Image rognee a droite" << endl;
            break;

        case 15:
            cout << "Entrer le nombre de colonnes que vous voulez rogner" << endl;
            cin >> nb;
            *this = rognerG(nb);
            cout << "Image rognee a gauche" << endl;
            break;

        case 16:
            cout << "Conversion de l image de base en rotation vers la droite de celle-ci" << endl;
            *this = RotationD();
            cout << "Rotation de l image vers la droite" << endl;
            break;

        case 17:
            cout << "Conversion de l image de base en rotation vers la gauche de celle-ci" << endl;
            *this = RotationG();
            cout << "Rotation de l image vers la gauche" << endl;
            break;

        case 18:
            cout << "Conversion de l' image de base en sa symetrie verticale" << endl;
            *this = retournementV();
            cout << "Symetrie verticale de l'image" << endl;
            break;

        case 19:
            cout << "Conversion de l' image de base en sa symetrie horizontale" << endl;
            *this = retournementH();
            cout << "Symetrie horizontale de l'image" << endl;
            break;

        case 20:
            cout<< "Entrez un facteur d'agrandissement de l'image :" << endl;
            cin >> facteur;
            *this = agrandissement(facteur);
            cout << "Agrandissement de l'image effectue" << endl;
            break;

        case 21:
            cout<< "Entrez un facteur de retrecissement de l'image :" << endl;
            cin >> facteur;
            *this = retrecissement(facteur);
            cout << "Retrecissement de l'image effectue" << endl;
            break;

        case 22:
            cout << "Merci d avoir utilise le programme. Au revoir !" << endl;
            return;

        default:
            cout << "Option invalide, veuillez reessayer." << endl;
        }

        // Sauvegarde de l'image après chaque opération (sauf quit)
        string fichier;
        cout << "\nEntrez le nom du fichier pour sauvegarder l'image (avec ou sans .ppm) : ";
        cin >> fichier;

        if (fichier.find(".ppm") == string::npos) { // Ajouter l'extension si nécessaire
            fichier += ".ppm";
        }

        ofstream output(fichier);
        if (output) {
            writeFile(output); // Sauvegarder l'état actuel de l'image
            cout << "L'image a ete enregistree dans le fichier : " << fichier << endl;
        } else {
            cerr << "Erreur : impossible d ecrire dans le fichier " << fichier << endl;
        }
    }
}

Image Image::rognerH(int nb) {
  vector<vector<int>> rouge;
  vector<vector<int>> vert;
  vector<vector<int>> bleu;

  for (int i = nb; i < _longueur; i++) {
    rouge.push_back(_rouge[i]);
    vert.push_back(_vert[i]);
    bleu.push_back(_bleu[i]);
  }
  Image m = Image(rouge, vert, bleu);
  return m;
}

Image Image::rognerB(int nb) {
  vector<vector<int>> rouge;
  vector<vector<int>> vert;
  vector<vector<int>> bleu;

  for (int i = 0; i < _longueur - nb; i++) {
    rouge.push_back(_rouge[i]);
    vert.push_back(_vert[i]);
    bleu.push_back(_bleu[i]);
  }
  Image m = Image(rouge, vert, bleu);
  return m;
}

Image Image::rognerG(int nb) {

  vector<vector<int>> rouge(_longueur, vector<int>(_largeur - nb));
  vector<vector<int>> vert(_longueur, vector<int>(_largeur - nb));
  vector<vector<int>> bleu(_longueur, vector<int>(_largeur - nb));

  if (nb < 0 || nb >= _largeur) {
    throw invalid_argument("Le nombre de colonnes à rogner est invalide.");
  }

  for (int i = 0; i < _longueur; i++) {
    for (int j = nb; j < _largeur; j++) {
      rouge[i][j - nb] = _rouge[i][j];
      vert[i][j - nb] = _vert[i][j];
      bleu[i][j - nb] = _bleu[i][j];
    }
  }
  Image m = Image(rouge, vert, bleu);
  return m;
}

Image Image::rognerD(int nb) {

  if (nb < 0 || nb >= _largeur) {
    throw invalid_argument("Le nombre de colonnes à rogner est invalide.");
  }

  vector<vector<int>> rouge(_longueur, vector<int>(_largeur - nb));
  vector<vector<int>> vert(_longueur, vector<int>(_largeur - nb));
  vector<vector<int>> bleu(_longueur, vector<int>(_largeur - nb));

  for (int i = 0; i < _longueur; i++) {
    for (int j = 0; j < _largeur - nb; j++) {
      rouge[i][j] = _rouge[i][j];
      vert[i][j] = _vert[i][j];
      bleu[i][j] = _bleu[i][j];
    }
  }
  Image m = Image(rouge, vert, bleu);
  return m;
}

Image Image::RotationD() const {
  Image m(_rouge, _vert, _bleu);
  for (int i = 0; i < _longueur; i++) {
    for (int j = _largeur - 1; j >= 0; j--) {
      m._rouge[i][j] = _rouge[3 - j][i];
      m._vert[i][j] = _vert[3 - j][i];
      m._bleu[i][j] = _bleu[3 - j][i];
    }
  }
  return m;
}

Image Image::RotationG() const {
  Image m(_rouge, _vert, _bleu);
  for (int i = _largeur - 1; i >= 0; i--) {
    for (int j = 0; j < _longueur; j++) {
      m._rouge[i][j] = _rouge[j][3 - i];
      m._vert[i][j] = _vert[j][3 - i];
      m._bleu[i][j] = _bleu[j][3 - i];
    }
  }
  return m;
}

Image Image::retournementV() {
  Image m(_rouge, _vert, _bleu);
  int nb_max = 3;
  int nb_min = 1;
  for (int i = _longueur - 1; i >= 0; i--) {
    for (int j = 0; j < _largeur; j++) {
      if (i == 3) {
        m._rouge[i][j] = _rouge[i - nb_max][j];
        m._vert[i][j] = _vert[i - nb_max][j];
        m._bleu[i][j] = _bleu[i - nb_max][j];
      } else if (i == 0) {
        m._rouge[i][j] = _rouge[i + nb_max][j];
        m._vert[i][j] = _vert[i + nb_max][j];
        m._bleu[i][j] = _bleu[i + nb_max][j];
      } else if (i == 1) {
        m._rouge[i][j] = _rouge[i + nb_min][j];
        m._vert[i][j] = _vert[i + nb_min][j];
        m._bleu[i][j] = _bleu[i + nb_min][j];
      } else if (i == 2) {
        m._rouge[i][j] = _rouge[i - nb_min][j];
        m._vert[i][j] = _vert[i - nb_min][j];
        m._bleu[i][j] = _bleu[i - nb_min][j];
      }
    }
  }
  return m;
}

Image Image::retournementH() {
  Image m(_rouge, _vert, _bleu);
  int nb_max = 3;
  int nb_min = 1;
  for (int i = _longueur - 1; i >= 0; i--) {
    for (int j = 0; j < _largeur; j++) {
      if (j == 3) {
        m._rouge[i][j] = _rouge[i][j - nb_max];
        m._vert[i][j] = _vert[i][j - nb_max];
        m._bleu[i][j] = _bleu[i][j - nb_max];
      } else if (j == 0) {
        m._rouge[i][j] = _rouge[i][j + nb_max];
        m._vert[i][j] = _vert[i][j + nb_max];
        m._bleu[i][j] = _bleu[i][j + nb_max];
      } else if (j == 1) {
        m._rouge[i][j] = _rouge[i][j + nb_min];
        m._vert[i][j] = _vert[i][j + nb_min];
        m._bleu[i][j] = _bleu[i][j + nb_min];
      } else if (j == 2) {
        m._rouge[i][j] = _rouge[i][j - nb_min];
        m._vert[i][j] = _vert[i][j - nb_min];
        m._bleu[i][j] = _bleu[i][j - nb_min];
      }
    }
  }
  return m;
}

Image Image::retrecissement(int facteur) {
  Image m;
  m._longueur = _rouge.size() / facteur;
  m._largeur = _rouge[0].size() / facteur;
  for (int i = 0; i < m._longueur; ++i) {
    m._rouge.push_back(vector<int>{});
    m._vert.push_back(vector<int>{});
    m._bleu.push_back(vector<int>{});
    for (int j = 0; j < m._largeur; ++j) {
      m._rouge[i].push_back((_rouge[i * facteur][j * facteur]));
      m._vert[i].push_back((_vert[i * facteur][j * facteur]));
      m._bleu[i].push_back((_bleu[i * facteur][j * facteur]));
    }
  }
  return m;
}

Image Image::agrandissement(int facteur) {
  Image m;
  m._longueur = _rouge.size() * facteur;
  m._largeur = _rouge[0].size() * facteur;
  for (int i = 0; i < m._longueur; ++i) {
    m._rouge.push_back(vector<int>{});
    m._vert.push_back(vector<int>{});
    m._bleu.push_back(vector<int>{});
    for (int j = 0; j < m._largeur; ++j) {
      m._rouge[i].push_back((_rouge[i / facteur][j / facteur]));
      m._vert[i].push_back((_vert[i / facteur][j /facteur]));
      m._bleu[i].push_back((_bleu[i / facteur][j / facteur]));
    }
  }
  return m;
}


Image Image::rotationCouleur(){

    Image m(_rouge, _vert, _bleu);
    for (int i = 0; i < _longueur; i++) {
        for (int j = 0; j < _largeur; j++) {
            if (m._rouge[i][j] == 255 && m._vert[i][j] == 0 && m._bleu[i][j] == 0) {//modifie la couleur du pixel si il est rouge en vert
                m._rouge[i][j] = 0;
                m._vert[i][j] = 255;
                m._bleu[i][j] = 0;
            } else if (m._rouge[i][j] == 0 && m._vert[i][j] == 255 && m._bleu[i][j] == 0) {//modifie la couleur du pixel si il est vert en bleu
                m._rouge[i][j] = 0;
                m._vert[i][j] = 0;
                m._bleu[i][j] = 255;
            } else if (m._rouge[i][j] == 0 && m._vert[i][j] == 0 && m._bleu[i][j] == 255) {//modifie la couleur du pixel si il est bleu en rouge
                m._rouge[i][j] = 255;
                m._vert[i][j] = 0;
                m._bleu[i][j] = 0;
            }else if (m._rouge[i][j] == 255 && m._vert[i][j] == 255 && m._bleu[i][j] == 0) {//modifie la couleur du pixel si il est jaune en bleu ciel
                m._rouge[i][j] = 102;
                m._vert[i][j] = 204;
                m._bleu[i][j] = 255;
            }
        }
    }
    return m;
}


/*Image Image::blanchirCouleur(int r, int v, int b){

    Image m;
    int rouge, vert, bleu;
    for (int i=0; i<_rouge.size();i++){
        for (int j=0; j<_rouge[i].size(); j++){
           if (((_rouge[i][j]-r+_vert[i][j]-v+bleu[i][j]-b)/(_rouge[i][j]+_vert[i][j]+_bleu[i][j])<=0.1)){
                _rouge[i][j]=0;
                _vert[i][j]=0;
                _bleu[i][j]=0;

            }
        }
    }
}*/




