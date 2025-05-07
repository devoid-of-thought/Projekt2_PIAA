#include "Graf.h"
#include <vector>
#include "Lista.h"
using namespace std;

void DFSG(Graf& graf, int start, vector<bool>& odwiedzone, vector<int>& przeszukaj_wyniki) {
    odwiedzone[start] = true;
    przeszukaj_wyniki.push_back(start);

    for (int i = 0; i < graf.rozmiar; ++i) {
        if (graf.macierz[start * graf.rozmiar + i] != 0 && !odwiedzone[i]) {
            DFSG(graf, i, odwiedzone, przeszukaj_wyniki);
        }
    }
}

void DFSL(Lista& graf, int start, vector<bool>& odwiedzone, vector<int>& przeszukaj_wyniki) {
    odwiedzone[start] = true;
    przeszukaj_wyniki.push_back(start);

    for (const auto& [sąsiad, _waga] : graf.lista[start]) {
        if (!odwiedzone[sąsiad]) {
            DFSL(graf, sąsiad, odwiedzone, przeszukaj_wyniki);
        }
    }
}