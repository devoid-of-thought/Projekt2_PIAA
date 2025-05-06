#include <vector>
#include <limits>
#include "Graf.h"
#include "Lista.h"
using namespace std;

vector<int> DijkstraG(Graf graf, int start) {
    const int INF = 9999999;
    int rozmiar = graf.rozmiar;

    vector<int> odleglosci(rozmiar, INF);
    vector<bool> odwiedzone(rozmiar, false);

    odleglosci[start] = 0;

    for (int numer_pętli = 0; numer_pętli < rozmiar;numer_pętli++) {
        int najmniejszy_dystans = INF;
        int obecne_V = -1;
        // Szukamy najbliższego wieszchołka, który nie został jeszcze przez nas odwiedzony
        for (int i = 0; i < rozmiar; i++) {
            if (!odwiedzone[i] && odleglosci[i] < najmniejszy_dystans) {
                najmniejszy_dystans = odleglosci[i];
                obecne_V = i;
            }
        }

        if (obecne_V == -1) break;

        odwiedzone[obecne_V] = true;

        // Zmierz odległości do sąsiadów obecnego wierzchołka
        for (int j = 0; j < rozmiar; j++) {
            int waga = graf.macierz[obecne_V * rozmiar + j];
            if (waga > 0 && !odwiedzone[j]) {
                int nowa_odleglosc = odleglosci[obecne_V] + waga;
                if (nowa_odleglosc < odleglosci[j]) {
                    odleglosci[j] = nowa_odleglosc;
                }
            }
        }
    }

    return odleglosci;
}
vector<int> DijkstraL(Lista graf, int start) {
    const int INF = 9999999;
    int rozmiar = graf.rozmiar;

    vector<int> odleglosci(rozmiar, INF);
    vector<bool> odwiedzone(rozmiar, false);

    odleglosci[start] = 0;

    for (int numer_pętli = 0; numer_pętli < rozmiar; numer_pętli++) {
        int najmniejszy_dystans = INF;
        int obecne_V = -1;

        for (int i = 0; i < rozmiar; i++) {
            if (!odwiedzone[i] && odleglosci[i] < najmniejszy_dystans) {
                najmniejszy_dystans = odleglosci[i];
                obecne_V = i;
            }
        }

        if (obecne_V == -1) break;

        odwiedzone[obecne_V] = true;

        // Zmierz odległości do sąsiadów obecnego wierzchołka
        for (auto& [sasiad, waga] : graf.lista[obecne_V]) {
            if (!odwiedzone[sasiad]) {
                int nowa_odleglosc = odleglosci[obecne_V] + waga;
                if (nowa_odleglosc < odleglosci[sasiad]) {
                    odleglosci[sasiad] = nowa_odleglosc;
                }
            }
        }
    }

    return odleglosci;
}

