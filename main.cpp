#include <iostream>
#include <vector>
#include "fonction.h"
using namespace std;

int main()
{
    vector<vector<int>> rouge = {{0, 0, 0, 0}, {0, 0, 255, 255}, {0, 255, 255, 255}, {255, 255, 255, 255}};
    vector<vector<int>> vert = {{0, 0, 255, 255},{0, 255, 255, 255},{255, 255, 255, 0},{255, 255, 0, 0}};
    vector<vector<int>> bleu = {{255, 255, 0, 0}, {255, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    vector<vector<float>> g3 = {{1. / 16, 1. / 8, 1. / 16},{1. / 8, 1. / 4, 1. / 8},{1. / 16, 1. / 8, 1. / 16}};


    Image i(rouge, vert, bleu);

    i.Menu();

    return 0;

}
