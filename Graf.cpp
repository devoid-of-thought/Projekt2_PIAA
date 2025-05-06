using namespace std;
#include <iostream>
#include <vector>
#include <random>
//implementacja grafu na macierzy sąsiedztwa
class Graf {

public:
    vector<int> macierz;
    int rozmiar;
    void generujGraf(int r, double gestosc);
    void pokażGraf();
    double Gęstość();
};
//generowanie losowych macierzy sąsiedztwa
void Graf::generujGraf(int r, double gestosc) {
    rozmiar = r;
    //tworzenie inicjalizowanie macierzy
    macierz.assign(rozmiar * rozmiar, 0);
    //losowanie krawędzi
    static mt19937 rng(random_device{}());
    uniform_real_distribution<float> prob_dist(0.0f, 1.0f);
    uniform_int_distribution<int> weight_dist(1, 10);
    //generowanie krawędzi
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            if (i != j && prob_dist(rng) < gestosc) {
                macierz[i * rozmiar + j] = weight_dist(rng);
            }
        }
    }
}
//wyświetlanie macierzy sąsiedztwa
void Graf::pokażGraf(){
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            cout << macierz[i * rozmiar + j] << " ";
        }
        cout << '\n';
    }
}

double Graf::Gęstość() {
    if (rozmiar < 2) return 0.0;

    int max_E = rozmiar * (rozmiar - 1);
    int ilość_E = 0;

    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            if (i != j && macierz[i * rozmiar + j] != 0) {
                ilość_E++;
            }
        }
    }

    return static_cast<double>(ilość_E) / max_E;
}