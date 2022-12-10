#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr const int64_t Mod = 1000000007;

void print64_tVector(vector<int64_t> &vec) {
	for (auto el: vec)
		cout << el << " ";
	cout << "\n";
}

void komitet() {
	int64_t n, k, l;
	cin >> n >> k >> l;
	vector<int64_t> dane(n);
	vector<int64_t> najblizszeL(n);
	vector<int64_t> najdalszeK(n, 0);

	for (int64_t i = 0; i < n; i++)
		cin >> dane[i];

	sort(dane.begin(), dane.end());

	int64_t indeksSprawdzany = n - 1;
	for (int64_t i = n - 1; i >= 0 && indeksSprawdzany >= 0; i--) {
		if (dane[indeksSprawdzany] - l >= dane[i]) {
			najblizszeL[indeksSprawdzany] = i;
			indeksSprawdzany--;
			i++;
		}
	}

	for (; indeksSprawdzany >= 0; indeksSprawdzany--)
		najblizszeL[indeksSprawdzany] = -1;


	indeksSprawdzany = n - 1;
	for (int64_t i = n - 1; i >= 0 && indeksSprawdzany >= 0;) {
		if (dane[indeksSprawdzany] - dane[i] <= k) {
			najdalszeK[indeksSprawdzany] = i;
			i--;
		} else {
			indeksSprawdzany--;
			najdalszeK[indeksSprawdzany] = najdalszeK[indeksSprawdzany + 1];
		}
	}

	vector<int64_t> minima(n);
	vector<int64_t> wynikCzesciowy(n);
	wynikCzesciowy[0] = 1;
	vector<int64_t> sumaCzeciowaWynik(n);
	sumaCzeciowaWynik[0] = 1;
	minima[0] = 1;

	vector<int64_t> sumyCzescioweRozmiarowMinimow;
	sumyCzescioweRozmiarowMinimow.push_back(1);

	for (int64_t i = 1; i < dane.size(); i++, sumyCzescioweRozmiarowMinimow.back()++) {
		int64_t najblizszyInnyPrzedstawiciel = najblizszeL[i];
		int64_t najdalszyLapany = najdalszeK[i];

		if (najdalszyLapany == 0) {
			wynikCzesciowy[i] = 1;
			minima[i] = 1;
			sumaCzeciowaWynik[i] = (sumaCzeciowaWynik[i - 1] + wynikCzesciowy[i]) % Mod;
			continue;
		}

		int64_t najdalszLapiacyNielapanego = najdalszeK[najdalszyLapany - 1];
		if (najdalszLapiacyNielapanego > najblizszyInnyPrzedstawiciel) /* Jeśli prawda, to znaczy, że nie mogę być wzięty - bo istnieje element, którego zwyczajnei nie da się wziąć */ {
			minima[i] = -1;
		} else {// Musimy potencjalnie zwiększyć minimum
			int64_t minimum = 0;
			for (; najdalszLapiacyNielapanego <= i && minimum == 0 && najdalszLapiacyNielapanego <= najblizszyInnyPrzedstawiciel; najdalszLapiacyNielapanego++)
				minimum = minima[najdalszLapiacyNielapanego] + 1;

			najdalszLapiacyNielapanego--;

			if (minimum == 0)
				minimum = -1;

			if (minimum > sumyCzescioweRozmiarowMinimow.size()) {
				sumyCzescioweRozmiarowMinimow.push_back(sumyCzescioweRozmiarowMinimow.back());
			}

			minima[i] = minimum;
		}

		if (minima[i] == -1 || minima[najdalszLapiacyNielapanego] == -1) {
			wynikCzesciowy[i] = 0;
		} else {
			if (najdalszLapiacyNielapanego == 0) {
				wynikCzesciowy[i] = sumaCzeciowaWynik[min(sumyCzescioweRozmiarowMinimow[0] - 1, najblizszyInnyPrzedstawiciel)];
			} else {
				wynikCzesciowy[i] = (Mod + sumaCzeciowaWynik[min(sumyCzescioweRozmiarowMinimow[minima[najdalszLapiacyNielapanego] - 1] - 1, najblizszyInnyPrzedstawiciel)] - sumaCzeciowaWynik[najdalszLapiacyNielapanego - 1]) % Mod;
			}
		}


		sumaCzeciowaWynik[i] = (sumaCzeciowaWynik[i - 1] + wynikCzesciowy[i]) % Mod;
	}

	int64_t min = -1;
	int64_t i;
	for (i = 0; min == -1; i++)
		min = minima[najdalszeK[n - 1] + i];
	int64_t najdalszeLapiaceKoniec = najdalszeK[n - 1] + i - 1;
	int64_t suma;
	if (najdalszeLapiaceKoniec > 0)
		suma = (Mod + sumaCzeciowaWynik[sumyCzescioweRozmiarowMinimow[min - 1] - 1] - sumaCzeciowaWynik[najdalszeLapiaceKoniec - 1]) % Mod;
	else
		suma = sumaCzeciowaWynik[sumyCzescioweRozmiarowMinimow[min - 1] - 1];


	cout << min << " " << suma << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	komitet();
	return 0;
}