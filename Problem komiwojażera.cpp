// Problem komiwojażera.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <fstream>
#include <iostream>
using namespace std;


//const int N = 4;

void zamiana(int& a, int& b)
{
	int c = a; 
	a = b; 
	b = c;
}

void permutacje(int T[], int ix, int R, int* NajSciezka, int& NajSuma, int& BiezSuma, int** NaszGraf) // ix = 0..N-1
{
	if (ix < R - 1)
	{
		for (int i = ix; i < R; i++)
		{
			zamiana(T[ix], T[i]); // zamienia dwa elementy miejscami
			permutacje(T, ix + 1, R, NajSciezka, NajSuma, BiezSuma, NaszGraf);
			zamiana(T[ix], T[i]); // przywracamy
		}
	}
	else
		{
			//obliczanie biezacej sumy
			BiezSuma = 0;

			int wierszgrafu = 0;
			int kolumnagrafu = T[0];
			BiezSuma = BiezSuma + NaszGraf[wierszgrafu][kolumnagrafu];

			for (int i = 0; i < R-1; i++)
			{
				wierszgrafu = T[i];
				kolumnagrafu = T[i + 1];

				BiezSuma = BiezSuma + NaszGraf[wierszgrafu][kolumnagrafu];

				cout << T[i]; // 1234 bez rozdzielania...
			}

			wierszgrafu = T[R-1];
			kolumnagrafu = 0;
			BiezSuma = BiezSuma + NaszGraf[wierszgrafu][kolumnagrafu];

			cout << T[R - 1];

			cout << "		Suma przejścia to " << BiezSuma;

			//sprawdzenie czy mamy nowa najlepsza sume
			if (BiezSuma < NajSuma)
			{
				NajSuma = BiezSuma;

				for (int i = 0; i < R; i++)
				{
					NajSciezka[i] = T[i];
				}

				cout << "		To jest najlepsza suma, ścieżka to : 0 -> ";

				for (int i = 0; i < R+1; i++)
				{
					cout << " " << NajSciezka[i];
				}
			}

			cout << endl; // nowa linia;
		}
}


int** ustawienie_grafu(int a, int** graf)
{
	graf = new int* [a];

	for (int i = 0; i < a; i++)
	{
		graf[i] = new int[a];
	}

	return graf;
}

int main()
{
    int wybor = -1;
	int wybor2 = -1;
	int rozmiar = -1;
	int** graf=NULL;

	//int* TablicaOdwiedzin;
	int* NajlepszaSciezka;
	//int* BiezacaSciezka;
	int NajlepszaSuma = 0;
	int BiezacaSuma = 0;
	int tablica[4] = { 1,2,3,4 };
	int* TablicaDrogi;

    while (wybor != 0)
    {
        cout << "Problem komiwojażera!" << endl << "wybierz co chcesz zrobić:\n";
        //cout << "1 - brutforce\n";
		cout << "1 - wygeneruj graf" << endl;
		cout << "2 - załaduj graf z pliku" << endl;
		cout << "0 - wyjście\n";

        cin >> wybor;

		if (wybor == 0)
		{
			break;
		}
		else
			{
				switch (wybor)
				{
					//graf losowy
					case 1:
					{//cout << "bruyforce kurva" << endl;
						cout << "Podaj rozmiar grafu:" << endl;
						cin >> rozmiar;

						graf = ustawienie_grafu(rozmiar, graf);

						/*graf = new int* [rozmiar];

						for (int i = 0; i < rozmiar; i++)
						{
							graf[i] = new int[rozmiar];
						}*/

						//ustalenie odległości

						for (int i = 0; i < rozmiar; i++)
						{
							for (int j = 0; j < rozmiar; j++)
							{
								if (i == j)
								{
									graf[i][j] = 0;
								}
								else
								{
									graf[i][j] = rand() % 9 + 1;
								}
							}
						}

						break;
					}
					//graf z pliku
					case 2:
					{
						ifstream plik;
						string NazwaPliku;

						cout << "Podaj nazwę pliku z rozszerzeniem:" << endl;
						cin >> NazwaPliku;

						plik.open(NazwaPliku);

						if (plik.good())
						{
							cout << "Udało się otworzyć plik" << endl;

							plik >> rozmiar;

							graf = ustawienie_grafu(rozmiar, graf);

							//ustalenie odległości z pliku
							for (int i = 0; i < rozmiar; i++)
							{
								for (int j = 0; j < rozmiar; j++)
								{
									plik >> graf[i][j];
								}
							}

							plik.close();
						}
						else
						{
							cout << "Nie udało się otworzyć plik" << endl;
						}

						break;
					}
					default:
						break;
				}
			}
			
			while (wybor2 !=0)
			{			
				cout << "Wybierz metodę rozwiązania problemu:" << endl;
				cout << "1 - Wyświetl graf" << endl;
				cout << "2 - brutforce" << endl;
				cout << "3 - programowanie dynamiczne" << endl;
				cout << "0 - wróć do poprzedniego punktu" << endl;

				cin >> wybor2;

				if (wybor == 0)
				{
					break;
				}
				else
					{
						switch (wybor2)
						{
							//wyswietlenie grafu
							case 1:
							{
								cout << "Rozmiar grafu to " << rozmiar << endl;

								for (int i = 0; i < rozmiar; i++)
								{
									for (int j = 0; j < rozmiar; j++)
									{
										cout << graf[i][j] << "  ";
									}

									cout << endl;
								}

								break;
							}

							//brutforce
							case 2:
							{
								cout << "bruyforce kurva" << endl;

								//TablicaOdwiedzin = new int[rozmiar];	- niepotrzebne
								NajlepszaSciezka = new int[rozmiar];
								//BiezacaSciezka = new int[rozmiar];	- niepotrzebne
								NajlepszaSuma = 0;
								BiezacaSuma = 0;
								TablicaDrogi = new int[rozmiar - 1];	//wierzcholki poza tym z indeksem 0 - droga miedzy poczatkiem i koncem

								//wybranie najpierw 1 z brzegu sciezki jako domyslnej, jak znajdzie sie lepsza to sie zamieni

								for (int i = 0; i < rozmiar - 1; i++)
								{
									NajlepszaSciezka[i] = i + 1;
									NajlepszaSuma = NajlepszaSuma + graf[i][i + 1];

									TablicaDrogi[i] = i + 1;
								}

								NajlepszaSciezka[rozmiar - 1] = 0;
								NajlepszaSuma = NajlepszaSuma + graf[rozmiar - 1][0];

								////kodowanie tablicy odwiedzin, moze zbednie
								//for (int i = 0; i < rozmiar; i++)
								//{
								//	TablicaOdwiedzin[i] = 0;
								//}

								//

								permutacje(TablicaDrogi, 0, rozmiar - 1, NajlepszaSciezka, NajlepszaSuma, BiezacaSuma, graf);

								cout << "Najkrótsza droga ma długość " << NajlepszaSuma << " i idzie przez:" << endl;

								cout << "0 -> ";

								for (int i = 0; i < rozmiar; i++)
								{
									cout << " " << NajlepszaSciezka[i];
								}

								cout << endl;
								//

								break;
							}
							
							//dynamicznie
							case 3:
								break;

							default:
								break;
						}
					}
			}

			wybor2 = -1;
    }
}

/*
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <iostream>
#include <iomanip>

using namespace std;
//Do pomiaru czasu
long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);

}

class TSP
{
private:
	//Alokowanie pamieci
	void Initialize()
	{
		graph = new int* [size];
		for (int i = 0; i < size; i++)
			graph[i] = new int[size];
	}

public:
	int size = 0;	//rozmiar problamu
	int** graph = NULL;	//Macierzowa reprezentacja grafu

	//Generowanie losowego grafu
	void GenerateRandomGraph(int n)
	{
		size = n;
		Initialize();
		srand(time(NULL));
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
			{
				if (i == j)
					graph[i][j] = -1;
				else
					graph[i][j] = rand() % 10 + 1;
			}
	}

	//Wypisywanie grafu w postaci macierzy
	void PrintGraph()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				cout << graph[i][j] << " ";
			cout << endl;
		}
	}

	//Generowanie grafu z pliku
	void GenerateFromFile()
	{
		string rozmiar;
		ifstream file;
		string file_name;
		cout << "Podaj nazwe pliku: ";
		cin >> file_name;
		file.open(file_name);
		if (file.good())
		{
			string line;
			for (int i = 0; i < 4; i++)
				getline(file, line);
			size = stoi(line.substr(11));
			Initialize();
			for (int i = 0; i < 3; i++)
				getline(file, line);
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					file >> graph[i][j];
			file.close();
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					if (i == j) graph[i][j] = -1;
		}
		else
			cout << "Nie udalo sie otworzyc pliku!";
	}

	//Zwalnianie pamieci
	~TSP()
	{
		if (graph != NULL)
		{
			for (int i = 0; i < size; i++)
				delete[] graph[i];
			delete[]graph;
		}
	}
};

class BF {
public:
	int* path;	//Tablica tymczasowa na obliczana sciezke
	int* best_path;	//Tablica na najlepsza sciezke

	int FindSolution(int** tab, int n)
	{
		path = new int[n];
		best_path = new int[n];
		int cost, l, i, j, k;

		long long int frequency, start, elapsed;
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		start = read_QPC();

		for (int i = 0; i < n; i++)
		{
			path[i] = i + 1;
			best_path[i] = i + 1;
		}
		int min_cost = INT_MAX;
		double counter = 0;
		do
		{
			cost = 0;
			l = 0;
			for (int i = 0; i < n; i++)
			{
				cost += tab[l][path[i]];
				l = path[i];
			}
			cost += tab[l][0];
			// update minimum 
			if (cost < min_cost)
			{
				min_cost = cost;
				for (int i = 0; i < n; i++)
					best_path[i] = path[i];
			}
			i = n - 1;
			//Permutowanie zbioru algorytmem Dijkstry
			while ((i > 0) && (path[i - 1] >= path[i]))
				i--;
			//Wyznaczanie elementu wiekszego od znalezionego
			if (i > 0) {
				j = n;
				while ((j > 0) && (path[j - 1] <= path[i - 1]))
					j--;
			}
			//Zamiana miejscami dwoch znalezionych wyzej elementow 
			if ((i > 0) && (j > 0)) {
				k = path[i - 1];
				path[i - 1] = path[j - 1];
				path[j - 1] = k;
			}
			//Odbicie lustrzane szeregu elementow od indeksu i+1 do konca tablicy
			for (i++, j = n; i < j; i++, j--)
			{
				k = path[i - 1];
				path[i - 1] = path[j - 1];
				path[j - 1] = k;
			}
			counter++;
		} while (counter <= Factorial(double(n)));	//Tak dlugo jak nie sprawdzimy wszystkich permutacji

		elapsed = read_QPC() - start;
		cout << "Czas wykonania w ms: " << setprecision(10) << (1000.0 * elapsed) / frequency << endl;

		return min_cost;
	}

	~BF()
	{
		if (path != NULL)
			delete[] path;
	}

private:
	//Liczenie permutacji potrzebne, aby wiedziec kiedy zakonczyc algorytm
	double Factorial(double n)
	{
		if (n == 0)
			return 1;
		return n * Factorial(n - 1);
	}
};

class DP {
public:
	int n;	//Rozmiar problemu
	int n2;	//Rozmiar potrzebnych tablic (1 << n lub tez 2^n)
	int** dp;	//Tablica do zapisywania rozwiazan
	int** path;	//Tablica potrzebne do wyluskiwania sciezek
	int visited_all;	//Maska oznaczajaca odwiedzenie wszystkich wierzcholkow

	//Alokacja pamieci i zdefiniowanie maski
	void initialize(int size)
	{
		n = size;
		n2 = (1 << size);
		dp = new int* [n2];
		path = new int* [n];
		for (int i = 0; i < n2; i++)
			dp[i] = new int[n];
		for (int i = 0; i < n; i++)
			path[i] = new int[n2];
		visited_all = (1 << n) - 1;	//11...1
	}

	//Algorytm
	int tsp(int mask, int pos, int** dist)
	{
		//cout << "Wywoluje tsp(" << mask << ", " << pos << ")" << endl;
		if (mask == visited_all) {	//Warunek zakonczenia - wszystkie miasta odwiedzone
			//cout << "Wszystkie odwiedzone, dodaje " << dist[pos][0] << endl;
			return dist[pos][0];
		}
		if (dp[mask][pos] != -1) {	//Warunek zakonczenia - ten przypadek zostal obliczony
			//cout << "Juz jest cos na pozycji [" << mask << "][" << pos << "]" << endl;
			return dp[mask][pos];
		}
		int ans = INT_MAX;
		for (int city = 0; city < n; city++)	//Potwarzamy dla kazdego miasta
		{
			//cout << "Iteracja dla " << city << " w tsp(" << mask << ", " << pos << ")" << endl;
			if ((mask & (1 << city)) == 0)		//Jesli miasto nie bylo odwiedzone
			{
				int tmp = dist[pos][city] + tsp(mask | (1 << city), city, dist);	//Dodajemy wage krawedzi oraz wywolujemy rekurencyjnie funkcje
				//dla mniejszych podproblemow
				if (ans > tmp)	//Jesli znajdziemy lepsze rozwiazanie, zamieniamy je
				{
					//cout << tmp << " jest mniejsze niz " << ans << ", wiec zamieniamy" << endl;
					ans = tmp;
					path[pos][mask] = city;
					//cout << "path[" << pos << "][" << mask << "] = " << city << endl;
				}
				//else
					//cout << tmp << " jest wieksze lub rowne " << ans << ", wiec nie zamieniamy" << endl;
			}
		}
		//cout << "dp[" << mask << "][" << pos << "] = " << ans << endl;
		return dp[mask][pos] = ans;	//Zapisujemy rozwiazanie
	}

	int findSolution(int** tab)	//Przygotowanie pomocnicznych tablic oraz uruchomienie algorytmu dla odpowiednich argumentow poczatkowych
	{
		for (int i = 0; i < n2; i++)
			for (int j = 0; j < n; j++)
				dp[i][j] = -1;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n2; j++)
				path[i][j] = -1;

		long long int frequency, start, elapsed;
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		start = read_QPC();

		int result;
		result = tsp(1, 0, tab);		// mask = 1 oznacza odwiedzenie pierwszego wierzcholka
		//pos = 0 oznacza start algorytmu w wierzcholku pierwszym (ktorego indeks = 0)
		elapsed = read_QPC() - start;
		cout << "Czas wykonania w ms: " << setprecision(10) << (1000.0 * elapsed) / frequency << endl;
		return result;
	}

	//Funkcja do odkrywania sciezki
	void getPath(int start, int set)
	{
		if (path[start][set] == -1)
		{
			return;
		}
		int i;
		i = path[start][set];
		cout << i << "->";
		int newSubset = set | (1 << i);
		getPath(i, newSubset);
	}

	~DP()
	{
		for (int i = 0; i < n2; i++)
			delete[] dp[i];
		for (int i = 0; i < n; i++)
			delete[] path[i];
		delete[] dp;
		delete[] path;
	}
};

int main()
{
	int choice;
	TSP salesman;
	BF brute_force;
	DP dynamic_programming;
	while (true)
	{
		cout << "----PROBLEM KOMIWOJAZERA----" << endl;
		cout << "Wybierz opcje zaladowania grafu: " << endl;
		cout << "1. Losowy graf " << endl;
		cout << "2. Zaladuj z pliku" << endl;
		cout << "Wybor: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			int n;
			cout << "Podaj rozmiar grafu: ";
			cin >> n;
			salesman.GenerateRandomGraph(n);
			break;
		case 2:
			salesman.GenerateFromFile();
			break;
		}
		cout << "Rozmiar grafu: " << salesman.size << endl;
		while (choice != 0)
		{
			cout << "Wybierz metode rozwiazania problemu: " << endl;
			cout << "1. Metoda naiwna (brute-force)" << endl;
			cout << "2. Metoda programowania dynamicznego: " << endl;
			cout << "3. Wypisz wczytany graf: " << endl;
			cout << "0. Cofnij" << endl;
			cout << "Wybor: ";
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "Najmniejszy koszt: " << brute_force.FindSolution(salesman.graph, salesman.size - 1) << endl;
				cout << "Sciezka: ";
				cout << "0->";
				for (int i = 0; i < salesman.size - 1; i++)
					cout << brute_force.best_path[i] << "->";
				cout << "0" << endl << endl;
				continue;
				break;
			case 2:
				dynamic_programming.initialize(salesman.size);
				cout << "Najmniejszy koszt: " << dynamic_programming.findSolution(salesman.graph) << endl;
				cout << "Sciezka: 0->";
				dynamic_programming.getPath(0, 1);
				cout << "0" << endl << endl;
				continue;
				break;
			case 3:
				salesman.PrintGraph();
				continue;
				break;
			}
		}
	}
}

*/