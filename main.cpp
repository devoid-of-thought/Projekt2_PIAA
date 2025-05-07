#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "Graf.h"
#include "Dikstrja.h"
#include "BellmanFord.h"
#include "DFS.h"

using namespace std;
int rozmiary[] = {10, 50, 100, 200, 500};
double gestosci[] = {0.25, 0.5, 0.75, 1};
void test_poprawności() {
    for (int g = 0; g <4; ++g) {
        for (int r = 0; r < 1; ++r) {
            for (int c = 0; c < 1; ++c) {
                Graf g1;
                g1.generujGraf(rozmiary[r], gestosci[g]);
                Lista l1;
                l1.macierzDoListy(g1, l1);
                g1.pokażGraf();
                l1.pokażGraf();

                vector<int> odleg_D1 = DijkstraG(g1, 0);
                vector<int> odleg_D2 = DijkstraL(l1, 0);
                vector<int> odleg_B1 = BellmanFordG(g1, 0);
                vector<int> odleg_B2 = BellmanFordL(l1, 0);
                vector<bool> odwiedzone(g1.rozmiar, false);
                vector<int> wynik_DFS;
                DFSG(g1, 0, odwiedzone, wynik_DFS);
                for (int i = 0; i < rozmiary[r];i++) {
                    cout << "Odległość od 0 dla :"<< to_string(i) <<" macierz " << to_string(odleg_D1[i]) << " lista " << to_string(odleg_D2[i]) << " "<<endl;;
                }
                if (odleg_D1 == odleg_B1) {
                    cout << "Algorytmy Dijkstra i Bellman-Ford dają takie same wyniki dla macierzy." << endl;
                } else {
                    cout << "Algorytmy Dijkstra i Bellman-Ford dają różne wyniki dla macierzy.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1111" << endl;
                }
                if (odleg_D1 == odleg_D2) {
                    cout << "Algorytmy Dijkstra daje takie same wyniki dla obu implementacji grafu." << endl;

                }
                else {
                    cout << "Algorytmy Dijkstra nie  daje takie same wyniki dla obu implementacji grafu.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11" << endl;

                }
                if (odleg_D2 == odleg_B2) {
                    cout << "Algorytmy Dijkstra i Bellman-Ford dają takie same wyniki dla listy." << endl;
                } else {
                    cout << "Algorytmy Dijkstra i Bellman-Ford dają różne wyniki dla listy.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1111" << endl;
                }
                cout << "Wynik przeszukiwania w głąb: ";
                for (int node : wynik_DFS) {
                    cout << node << " ";
                }
                cout << endl;

            }
        }
    }
}
void test_spr() {
    ofstream dijkstra_wyniki_L("dijkstra.csv");
    ofstream bellman_wyniki_L("bellman.csv");
    ofstream dfs_wyniki_L("dfs.csv");

    dijkstra_wyniki_L << "gestosc/rozmiar";
    bellman_wyniki_L << "gestosc/rozmiar";
    dfs_wyniki_L << "gestosc/rozmiar";

    ofstream dijkstra_wyniki_M("dijkstra_M.csv");
    ofstream bellman_wyniki_M("bellman_M.csv");
    ofstream dfs_wyniki_M("dfs_M.csv");

    dijkstra_wyniki_M << "gestosc/rozmiar";
    bellman_wyniki_M << "gestosc/rozmiar";
    dfs_wyniki_M << "gestosc/rozmiar";

    for (int r = 0; r < 5; r++) {
        dijkstra_wyniki_M << "," << rozmiary[r];
        bellman_wyniki_M << "," << rozmiary[r];
        dfs_wyniki_M << "," << rozmiary[r];
    }
    dijkstra_wyniki_M << "\n";
    bellman_wyniki_M << "\n";
    dfs_wyniki_M << "\n";

    for (int r = 0; r < 5; r++) {
        dijkstra_wyniki_L << "," << rozmiary[r];
        bellman_wyniki_L << "," << rozmiary[r];
        dfs_wyniki_L << "," << rozmiary[r];
    }
    dijkstra_wyniki_L << "\n";
    bellman_wyniki_L << "\n";
    dfs_wyniki_L << "\n";

    for (int g = 0; g < 4; g++) {
        dijkstra_wyniki_L << gestosci[g];
        bellman_wyniki_L << gestosci[g];
        dfs_wyniki_L << gestosci[g];

        for (int r = 0; r < 5; r++) {
            long long suma_D1 = 0, suma_B1 = 0, suma_DFS1 = 0;
            long long suma_D2 = 0, suma_B2 = 0, suma_DFS2 = 0;

            for (int c = 0; c < 100; c++) {
                Graf g1;
                g1.generujGraf(rozmiary[r], gestosci[g]);
                Lista l1;
                l1.macierzDoListy(g1,l1);

                vector<int> wynik_DFS1;
                vector<int> wynik_DFS2;
                auto start_D1 = chrono::high_resolution_clock::now();
                DijkstraG(g1, 0);
                auto end_D1 = chrono::high_resolution_clock::now();
                suma_D1 += chrono::duration_cast<chrono::nanoseconds>(end_D1 - start_D1).count();

                auto start_B1 = chrono::high_resolution_clock::now();
                BellmanFordG(g1, 0);
                auto end_B1 = chrono::high_resolution_clock::now();
                suma_B1 += chrono::duration_cast<chrono::nanoseconds>(end_B1 - start_B1).count();

                vector<bool> odwiedzone(g1.rozmiar, false);
                auto start_DFS1 = chrono::high_resolution_clock::now();
                DFSG(g1, 0, odwiedzone, wynik_DFS1);
                auto end_DFS1 = chrono::high_resolution_clock::now();
                suma_DFS1 += chrono::duration_cast<chrono::nanoseconds>(end_DFS1 - start_DFS1).count();

                auto start_D2 = chrono::high_resolution_clock::now();
                DijkstraL(l1, 0);
                auto end_D2 = chrono::high_resolution_clock::now();
                suma_D2 += chrono::duration_cast<chrono::nanoseconds>(end_D2 - start_D2).count();

                auto start_B2 = chrono::high_resolution_clock::now();
                BellmanFordL(l1, 0);odwiedzone.assign(l1.rozmiar, false);
                auto end_B2 = chrono::high_resolution_clock::now();
                suma_B2 += chrono::duration_cast<chrono::nanoseconds>(end_B2 - start_B2).count();

                vector<bool> odwiedzone2(l1.rozmiar, false);
                auto start_DFS2 = chrono::high_resolution_clock::now();
                DFSL(l1, 0, odwiedzone2, wynik_DFS2);
                auto end_DFS2 = chrono::high_resolution_clock::now();
                suma_DFS2 += chrono::duration_cast<chrono::nanoseconds>(end_DFS2 - start_DFS2).count();
            }

            dijkstra_wyniki_M << "," << (suma_D1 / 100.0);
            bellman_wyniki_M << "," << (suma_B1 / 100.0);
            dfs_wyniki_M << "," << (suma_DFS1 / 100.0);

            dijkstra_wyniki_L << "," << (suma_D2 / 100.0);
            bellman_wyniki_L << "," << (suma_B2 / 100.0);
            dfs_wyniki_L << "," << (suma_DFS2 / 100.0);
        }

        dijkstra_wyniki_L << "\n";
        bellman_wyniki_L << "\n";
        dfs_wyniki_L << "\n";
    }

    dijkstra_wyniki_L.close();
    bellman_wyniki_L.close();
    dfs_wyniki_L.close();
    dijkstra_wyniki_M.close();
    bellman_wyniki_M.close();
    dfs_wyniki_M.close();
}




int main() {
    //test_spr();
    test_poprawności();
     return 0;
}
