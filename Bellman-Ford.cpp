#include "Graf.h"
#include <vector>
#include "Lista.h"
using namespace std;

vector<int> BellmanFord(Graf& graf, int start) {
    //symulacja nieskończoności poprzez dużą liczbę
    const int INF = 9999999;
    int rozmiar = graf.rozmiar;
    //inicjalizacja wektora odległości
    vector<int> odleglosci(rozmiar, INF);
    //inicjalizacja odległości startowej
    odleglosci[start] = 0;
    for (int i = 0; i < rozmiar - 1; i++) {
        //iteracja po wszystkich krawędziach
        for (int u = 0; u < rozmiar; u++) {
            //iteracja po sąsiadach
            for (int v = 0; v < rozmiar; v++) {
                int waga = graf.macierz[u * rozmiar + v];
                //sprawdzamy czy krawędź istnieje
                if (waga !=0) {
                    //sprawdzamy czy nowa scieżka jest krótsza
                    if (odleglosci[u] + waga < odleglosci[v]) {
                        odleglosci[v] = odleglosci[u] + waga;
                    }
                }
            }
        }
    }

    return odleglosci;
}
