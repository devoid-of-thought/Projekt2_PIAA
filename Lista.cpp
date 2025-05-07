#include <iostream>
#include <vector>
#include <random>
#include "Graf.h"
using namespace std;

class Lista {
public:
    int rozmiar;
    vector<vector<pair<int, int>>> lista;
    void pokażGraf();
    void generujGraf(int r, double gestosc,int seed);
    void macierzDoListy(const Graf& graf, Lista& lista);
};

void Lista::generujGraf(int r, double gestosc,int seed) {
    rozmiar = r;
    lista.clear();
    lista.resize(r);

    static mt19937 rng(seed);
    uniform_real_distribution<double> prob_dist(0.0, 1.0);
    uniform_int_distribution<int> weight_dist(1, 10000000);

    for(int u = 0; u < r; ++u) {
        for(int v = u + 1; v < r; ++v) {
            if(prob_dist(rng) < gestosc) {
                int weight = weight_dist(rng);
                lista[u].emplace_back(v, weight);
            }
        }
    }
}
void Lista::pokażGraf() {
    cout << "Graph Structure (Adjacency List):\n";
    for(int node = 0; node < rozmiar; ++node) {
        cout << "Node " << node << " connected to: ";
        if(lista[node].empty()) {
            cout << "No connections";
        }
        else {
            for(auto& [neighbor, weight] : lista[node]) {
                cout << neighbor << "(W:" << weight << ") ";
            }
        }
        cout << "\n";
    }
}

void Lista::macierzDoListy(const Graf& graf, Lista& lista) {
    lista.rozmiar = graf.rozmiar;
    lista.lista.clear();
    lista.lista.resize(graf.rozmiar);

    for (int u = 0; u < graf.rozmiar; ++u) {
        for (int v = 0; v < graf.rozmiar; ++v) {
            int waga = graf.macierz[u * graf.rozmiar + v];
            if (waga != 0) {
                lista.lista[u].emplace_back(v, waga);
            }
        }
    }
}