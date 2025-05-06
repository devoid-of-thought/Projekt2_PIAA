#include "Graf.h"
#include <vector>

using namespace std;

void DFS(Graf& graf, int start, vector<bool>& odwiedzone, vector<int>& przeszukaj_wyniki) {
    odwiedzone[start] = true;
    przeszukaj_wyniki.push_back(start);

    for (int i = 0; i < graf.rozmiar; ++i) {
        if (graf.macierz[start * graf.rozmiar + i] != 0 && !odwiedzone[i]) {
            DFS(graf, i, odwiedzone, przeszukaj_wyniki);
        }
    }
}
