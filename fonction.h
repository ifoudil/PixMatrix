#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Image {

private:
  vector<vector<int>> _rouge;
  vector<vector<int>> _vert;
  vector<vector<int>> _bleu;
  int _largeur;
  int _longueur;

public:
  Image(); // empty constructor

  Image(const vector<vector<int>> &rouge, const vector<vector<int>> &vert,
        const vector<vector<int>> &bleu); // constructor with 3 vectors

  Image(const string &picture); // constructeur qui prend en parametre le nom d�un fichier
                      // image au format ppm et creera l'objet correspondant

  int Getlongueur(); // permet d'obtenir la longueur de l'image

  int Getlargeur(); // permet d'obtenir la largeur de l'image

  void Affichage() const; // affiche l'image en question

  Image composanteRouge(); // renvoie une image teint en rouge

  bool detection(int R, int V, int B);

  Image niveauxGris() const; // affiche l'image de avec des pixels de niveau
                             // gris

  Image noirEtblanc() const; // affiche l'image en noir et blanc

  void visionProtanopie(); // affiche les images avecla vision Protanopie

  void visionTritanopie(); // afficheles images avec la vision Tritanopie

  void visionDeuteranopie(); // affiche les images avec la vision Deuteranopie

  vector<int> HistogrammeGris(); // renvoie un vecteur de 256 valeurs qui contient le nombre
                     // de pixel de chaque niveau de l'image

  Image luminosityUp(float n) const; // augment la limite de luminosit� de l'image

  Image luminosityDown(float n) const; // diminue la liminuosit� de l'image

  Image contrasteDown(); // le contraste de l'image diminue

  Image contrasteUp(); // le contraste de l'image augmente

  void writeFile(ofstream &stream); //�criture de l'image dans un fichier

  void Menu(); // Propose les methodes

  Image retournementV(); // retournement vertical

  Image retournementH(); // retournement horizontal

  Image RotationG() const; // tourne l'image de 90� vers la gauche

  Image RotationD() const; // tourne l'image de 90� vers la droite

  Image rognerD(int nb); // supprime nb de colonne de pixel de l�image respective � droite

  Image rognerG(int nb); // supprime nb de colonne de pixel de l�image respective � gauche

  Image rognerH(int nb); // supprime nb de ligne de pixel de l�image respective en haut

  Image rognerB(int nb); // supprime nb de ligne de pixel de l�image respective en bas

  Image retrecissement(int facteur); // retrecie l'image

  //Image blanchirCouleur(int r, int v, int b);

  Image agrandissement(int facteur);

  Image rotationCouleur();// change les couleurs en d'autre en fonction des pixels

};

// loadPicture : prend le nom d'un fichier contenant une image au format ppm,
// remplit 3 tableaux 2D avec les donnees de cette image, et renvoie la taille
// effective de ces tableaux (identique pour les 3 tableaux).
// parametres (D) image : chaine de caracteres
//  		 (R) tabR, tabB, tabG : tableaux [0,MAX-1][0,MAX-1] d'entiers
void loadPicture(const string &picture, vector<vector<int>> &rouge,
                 vector<vector<int>> &vert, vector<vector<int>> &bleu);


#endif // FONCTION_H_INCLUDED
