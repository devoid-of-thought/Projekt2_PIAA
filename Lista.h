//
// Created by userbrigh on 5/6/25.
//
using namespace std;
#ifndef LISTA_H
#define LISTA_H
class Lista {
public:
    int rozmiar;
    vector<vector<pair<int, int>>> lista;
    void pokażGraf();
    void generujGraf(int r, double gestosc,int seed);
};
#endif //LISTA_H
