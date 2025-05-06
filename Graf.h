#ifndef GRAF_H
#define GRAF_H

#include <vector>

class Graf {
public:
    std::vector<int> macierz;
    int rozmiar;
    void generujGraf(int r, double gestosc);
    void pokażGraf();
    double Gęstość();
};

#endif // GRAF_H