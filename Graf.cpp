using namespace std;
#include <iostream>
#include <vector>
#include <random>

class Graf {

public:
    vector<int> macierz;
    int rozmiar;
    void generujGraf(int r, double gestosc,int seed);
    void pokażGraf();
    double Gęstość();
};

void Graf::generujGraf(int r, double gestosc,int seed) {
    rozmiar = r;
    macierz.assign(rozmiar * rozmiar, 0); // Reset and resize matrix

    mt19937 rng(seed);
    uniform_real_distribution<float> prob_dist(0.0f, 1.0f);
    uniform_int_distribution<int> weight_dist(1, 10);

    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            if (i != j && prob_dist(rng) < gestosc) {
                macierz[i * rozmiar + j] = weight_dist(rng);
             }
        }
    }
}

void Graf::pokażGraf(){
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            cout << macierz[i * rozmiar + j] << " ";
        }
        cout << '\n';
    }
}

double Graf::Gęstość() {
    if (rozmiar < 2) return 0.0; // No possible edges

    int possible_edges = rozmiar * (rozmiar - 1);
    int actual_edges = 0;

    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            if (i != j && macierz[i * rozmiar + j] != 0) {
                actual_edges++;
            }
        }
    }

    return static_cast<double>(actual_edges) / possible_edges;
}