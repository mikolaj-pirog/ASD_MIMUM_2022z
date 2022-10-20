#include <iostream>
#include <vector>

using namespace std;

constexpr int modConst = 1000000000;

void sor() {
	int n;
	cin >> n;
	vector<int> dane(n);
	vector<vector<int>> macierzLewa(n, vector<int>(n, 0));
	vector<vector<int>> macierzPrawa(n, vector<int>(n, 0));

	// This solution works for n > 1.
	if (n == 1) {
		cout << 1;
		return;
	}

	for (int i = 0; i < n; i++) {
		macierzLewa[i][i] = 1;
		macierzPrawa[i][i] = 1;
		cin >> dane[i];
	}

	auto liczLewy = [&](int i, int j) {
		int wynik = 0;
		if (dane[i] < dane[i + 1])
			wynik = (wynik + macierzLewa[i + 1][j]) % modConst;
		if (dane[i] < dane[j] && i + 1 < j)
			wynik = (wynik + macierzPrawa[i + 1][j]) % modConst;

		return wynik;
	};

	auto liczPrawy = [&](int i, int j) {
		int wynik = 0;
		if (dane[i] < dane[j])
			wynik = (wynik + macierzLewa[i][j - 1]) % modConst;
		if (dane[j - 1] < dane[j] && i + 1 < j)
			wynik = (wynik + macierzPrawa[i][j - 1]) % modConst;

		return wynik;
	};

	for (int i = 1; i < n; i++) {
		for (int j = 0; j + i < n; j++) {
			macierzLewa[j][i + j] = liczLewy(j, i + j);
			macierzPrawa[j][i + j] = liczPrawy(j, i + j);
		}
	}

	cout << (macierzLewa[0][n - 1] + macierzPrawa[0][n - 1]) % modConst;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	sor();
	return 0;
}