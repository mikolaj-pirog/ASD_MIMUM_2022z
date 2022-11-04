#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

void printVector(vector<int> &vec) {
	for (auto el : vec)
		cout << el << " ";
	cout << "\n";
}

void komitet() {
	int n, k , l;
	cin >> n >> k >> l;
	vector<int> dane(n);
	vector<int> najblizszeL(n);
	vector<int> najdalszeK(n);

	for (int i = 0; i < n; i++)
		cin >> dane[i];

	int indeksSprawdzany = n - 1;
	for(int i  = n - 1; i >= 0; i--) {
		if (dane[indeksSprawdzany] - l >= dane[i]) {
			najblizszeL[indeksSprawdzany] = i;
			indeksSprawdzany--;
			i++;
		}
	}

	for(; indeksSprawdzany >= 0; indeksSprawdzany--)
		najblizszeL[indeksSprawdzany] = -1;

	printVector(najblizszeL);

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	komitet();
	return 0;
}