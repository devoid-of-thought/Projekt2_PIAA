#include "Graf.h"
#include <vector>
#include "Lista.h"
using namespace std;

vector<int> BellmanFordG(Graf& graf, int start) {
    const int INF = 9999999;
    int rozmiar = graf.rozmiar;

    vector<int> odleglosci(rozmiar, INF);
    vector<int> poprzednik(rozmiar, 0);
    odleglosci[start] = 0;
    for (int i = 0; i < rozmiar - 1; i++) {
        for (int u = 0; u < rozmiar; u++) {
            for (int v = 0; v < rozmiar; v++) {
                int waga = graf.macierz[u * rozmiar + v];
                if (waga !=0) {
                    if (odleglosci[u] + waga < odleglosci[v]) {
                        odleglosci[v] = odleglosci[u] + waga;
                        poprzednik[v] = u;
                    }
                }
            }
        }
    }

    return odleglosci;
}
vector<int> BellmanFordL(Lista& graf, int start) {
    const int INF = 9999999;
    int rozmiar = graf.rozmiar;
    vector<int> odleglosci(rozmiar, INF);
    odleglosci[start] = 0;

    for (int i = 0; i < rozmiar - 1; ++i) {
        for (int u = 0; u < rozmiar; ++u) {
            if (odleglosci[u] == INF || u >= graf.lista.size()) continue;
            for (auto& [v, waga] : graf.lista[u]) {
                if (v >= rozmiar) continue; // Validate node index
                if (odleglosci[u] + waga < odleglosci[v]) {
                    odleglosci[v] = odleglosci[u] + waga;
                }
            }
        }
    }
    return odleglosci;
}