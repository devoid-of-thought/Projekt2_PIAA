#include <iostream>
#include <vector>
#include <random>
using namespace std;

class Lista {
public:
    int rozmiar;
    vector<vector<pair<int, int>>> lista;
    void pokażGraf();
    void generujGraf(int r, double gestosc,int seed);
};

void Lista::generujGraf(int r, double gestosc, int seed) {
    rozmiar = r;
    lista.clear();
    lista.resize(r);

    mt19937 rng(seed);
    uniform_real_distribution<double> prob_dist(0.0, 1.0);
    uniform_int_distribution<int> weight_dist(1, 10);

    // Generate edges for directed graph
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < r; j++) {
            if (i != j && prob_dist(rng) < gestosc) {
                int weight = weight_dist(rng);
                lista[i].emplace_back(j,weight);
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