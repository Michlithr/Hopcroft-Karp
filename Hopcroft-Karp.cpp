#include <iostream>
#include <cstdio>
 
/*In this project I have to implement Hopcroft–Karp algorithm to find max matching for specified datas.*/

inline void readFastInput(int *n)
{
	char c = 0;
	while (c < 33) {
		c = _fgetc_nolock(stdin);
	}
	(*n) = 0;
	while (c>32) {
		(*n) = (*n) * 10 + (c - 48); c = _fgetc_nolock(stdin);
	}
}
 
struct wierzcholek {
	int* polaczenia;
	int liczba_polaczen;
	int odleglosc;
	int wierzcholek_skojarzony;
	bool odwiedzony;
	bool odwiedzony_dfs;
};
 
inline void bfs(wierzcholek* G, int* Q, int liczba_ludzi) 
{
	int iterator_kolejki = 0;
	for (int j = 0; j<liczba_ludzi; j++) {
		G[j].odleglosc = -1;
		if (!G[j].odwiedzony_dfs) {
			Q[iterator_kolejki++] = j;
			G[j].odleglosc = 0;
		}
	}
	for (int i = 0; i < iterator_kolejki; i++) {
		int V = Q[i];
		for (int j = G[V].liczba_polaczen - 1; j >= 0; j--) {
			int E = G[G[V].polaczenia[j]].wierzcholek_skojarzony;
			if (E >= 0 && G[E].odleglosc < 0) {
				G[E].odleglosc = G[V].odleglosc + 1;
				Q[iterator_kolejki++] = E;
			}
		}
	}
}
 
inline bool dfs(wierzcholek *G, int V)
{
	G[V].odwiedzony= true;
	for (int i = G[V].liczba_polaczen - 1; i >= 0; i--){
		int E = G[V].polaczenia[i];
		int skojarzony = G[E].wierzcholek_skojarzony;
		if (skojarzony < 0 || !G[skojarzony].odwiedzony && 
			G[skojarzony].odleglosc == G[V].odleglosc + 1 && dfs(G, skojarzony))	{
			G[E].wierzcholek_skojarzony = V;
			G[V].odwiedzony_dfs = true;
			return true;
		}
	}
	return false;
}
 
 
int main() 
{
	int liczba_ludzi, liczba_rowerow, liczba_preferencji,
		liczba_dopasowanych_rowerow = 0, najdluzsza_sciezka = 0, nr_roweru, suma_r_l;
	readFastInput(&liczba_ludzi);
	readFastInput(&liczba_rowerow);
	suma_r_l = liczba_ludzi + liczba_rowerow + 1;
	int* Q = new int[liczba_ludzi];
	wierzcholek* G = new wierzcholek[suma_r_l];
 
	for (int i = 0; i < liczba_ludzi; i++) {
		readFastInput(&liczba_preferencji);
		G[i].polaczenia = new int[liczba_preferencji];
		G[i].liczba_polaczen = liczba_preferencji;
		G[i].odwiedzony_dfs = false;
		for (int j = 0; j < liczba_preferencji; j++) {
			readFastInput(&nr_roweru);
			G[i].polaczenia[j] = nr_roweru;
 
		}
	}
 
	for (int i = 0; i < suma_r_l; i++) {
		G[i].wierzcholek_skojarzony = -1;
	}
 
	while (true) {
		najdluzsza_sciezka = 0;
		bfs(G, Q, liczba_ludzi);
		for (int i = 0; i < liczba_ludzi; i++) {
			G[i].odwiedzony = false;
		}
 
		for (int i = 0; i < liczba_ludzi; i++) {
			if (!G[i].odwiedzony_dfs && dfs(G, i)) {
				najdluzsza_sciezka++;
			}
		}
		liczba_dopasowanych_rowerow += najdluzsza_sciezka;
		if (najdluzsza_sciezka == 0) {
			printf("%d", liczba_dopasowanych_rowerow);
			break;
		}
	}
	delete[] Q;
	delete[] G;
	return 0;
}