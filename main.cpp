#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "Graf.h"
#include "Dikstrja.h"
#include "BellmanFord.h"
#include "DFS.h"
#include "Lista.h"

using namespace std;
int rozmiary[] = {10, 50, 100, 200, 500};
double gestosci[] = {0.25, 0.5, 0.75, 1};
void test_poprawności() {
    for (int g = 0; g <4; ++g) {
        for (int r = 0; r < 1; ++r) {
            for (int c = 0; c < 1; ++c) {
                c = 999;
                Graf g1;
                g1.generujGraf(rozmiary[r], gestosci[g],c);
                Lista l1;
                l1.generujGraf(rozmiary[r], gestosci[g],c);
                g1.pokażGraf();
                l1.pokażGraf();

                vector<int> odleg_D1 = DijkstraG(g1, 0);
                vector<int> odleg_D2 = DijkstraL(l1, 0);
                vector<int> odleg_B1 = BellmanFordG(g1, 0);
                vector<int> odleg_B2 = BellmanFordL(l1, 0);
                vector<bool> odwiedzone(g1.rozmiar, false);
                vector<int> wynik_DFS;
                DFS(g1, 0, odwiedzone, wynik_DFS);
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
    ofstream dijkstra_wyniki("/home/userbrigh/CLionProjects/Projekt2_PIAA/dijkstra.csv");
    ofstream bellman_wyniki("/home/userbrigh/CLionProjects/Projekt2_PIAA/bellman.csv");
    ofstream dfs_wyniki("/home/userbrigh/CLionProjects/Projekt2_PIAA/dfs.csv");

    dijkstra_wyniki << "gestosc/rozmiar";
    bellman_wyniki << "gestosc/rozmiary";
    dfs_wyniki << "gestosc/rozmiary";
    for (int r = 0; r < 5; r++) {
        dijkstra_wyniki << "," << rozmiary[r];
        bellman_wyniki << "," << rozmiary[r];
        dfs_wyniki << "," << rozmiary[r];
    }
    dijkstra_wyniki << "\n";
    bellman_wyniki << "\n";
    dfs_wyniki << "\n";

    for (int g = 0; g < 4; g++) {
        dijkstra_wyniki << gestosci[g];
        bellman_wyniki << gestosci[g];
        dfs_wyniki << gestosci[g];

        for (int r = 0; r < 5; r++) {
            long long suma_D = 0, suma_B = 0, suma_DFS = 0;

            for (int c = 0; c < 100; c++) {
                Graf g1;
                g1.generujGraf(rozmiary[r], gestosci[g],c);

                auto start_D = chrono::high_resolution_clock::now();
                vector<int> odleg_D = DijkstraG(g1, 0);
                auto end_D = chrono::high_resolution_clock::now();
                suma_D += chrono::duration_cast<chrono::nanoseconds>(end_D - start_D).count();

                auto start_B = chrono::high_resolution_clock::now();
                vector<int> odleg_B = BellmanFordG(g1, 0);
                auto end_B = chrono::high_resolution_clock::now();
                suma_B += chrono::duration_cast<chrono::nanoseconds>(end_B - start_B).count();

                vector<bool> odwiedzone(g1.rozmiar, false);
                vector<int> wynik_DFS;
                auto start_DFS = chrono::high_resolution_clock::now();
                DFS(g1, 0, odwiedzone, wynik_DFS);
                auto end_DFS = chrono::high_resolution_clock::now();
                suma_DFS += chrono::duration_cast<chrono::nanoseconds>(end_DFS - start_DFS).count();
            }

            double avg_D = suma_D / 100.0;
            double avg_B = suma_B / 100.0;
            double avg_DFS = suma_DFS / 100.0;

            dijkstra_wyniki << "," << (avg_D);
            bellman_wyniki << "," << (avg_B);
            dfs_wyniki << "," << (avg_DFS);
        }

        dijkstra_wyniki << "\n";
        bellman_wyniki << "\n";
        dfs_wyniki << "\n";
    }

    dijkstra_wyniki.close();
    bellman_wyniki.close();
    dfs_wyniki.close();
}


int main() {
    //test_spr();
    test_poprawności();
     return 0;
}
