#include <iostream>
#include <vector>

#define size_t unsigned long long

using namespace std;
/*
void printVector(std::vector<size_t> &vec) {
	for(auto tek : vec)
		cout << tek << "/";
	cout << "\n";
}
 */

void bazarek() {
	size_t n, m;
	cin >> n;

	vector<size_t> ceny(n);

	vector<size_t> sumyCzesciowe(n + 1);
	vector<size_t> parzMax(n+1);
	vector<size_t> nparzMax(n+1);
	vector<size_t> parzMin(n+1);
	vector<size_t> nparzMin(n+1);

	parzMax[0] = 0;
	nparzMax[0] = 0;


	sumyCzesciowe[n] = 0;

	for (size_t i = 0; i < n; i++) {
		cin >> ceny[i];
		if (ceny[i] % 2 == 0) {
			parzMax[i + 1] = ceny[i];
			nparzMax[i + 1] = nparzMax[i];
		}
		else {
			parzMax[i + 1] = parzMax[i];
			nparzMax[i + 1] = ceny[i];
		}
	}

	for (size_t i = 1; i < n + 1; i++) {
		sumyCzesciowe[i] = ceny[n - i] + sumyCzesciowe[i - 1];
	}


	for (size_t i = n - 1; ; i--) {
		if (ceny[i] % 2 == 0) {
			parzMin[i] = ceny[i];
			nparzMin[i] = nparzMin[i + 1];
		} else {
			parzMin[i] = parzMin[i + 1];
			nparzMin[i] = ceny[i];
		}
		//sumyCzesciowe[i] = sumyCzesciowe[i + 1] + ceny[i];

		if (i == 0)
			break;

	}

	//printVector(nparzMin);
	//printVector(parzMin);
	//printVector(nparzMax);
	//printVector(parzMax);

	//printVector(sumyCzesciowe);

	cin >> m;
	size_t liczbaZakupow, sumaZakupow;
	for (size_t i = 0; i < m; i++) {
		cin >> liczbaZakupow;

		sumaZakupow = sumyCzesciowe[liczbaZakupow];
		//cout << sumaZakupow << endl;

		if (sumaZakupow % 2 == 1) {
			cout << sumaZakupow << "\n";
		} else {
			size_t wariant1 = 0;
			size_t wariant2 = 0;

			if (!(nparzMin[n - liczbaZakupow] == 0 || parzMax[n - liczbaZakupow] == 0))
				wariant1 = (sumaZakupow - nparzMin[n - liczbaZakupow]) + parzMax[n - liczbaZakupow];
			if (!(parzMin[n - liczbaZakupow] == 0 || nparzMax[n - liczbaZakupow] == 0))
				wariant2 = (sumaZakupow - parzMin[n - liczbaZakupow]) + nparzMax[n - liczbaZakupow];

			if (wariant1 == 0 && wariant2 == 0)
				cout << "-1\n";
			else {
				size_t result = wariant1 >= wariant2 ? wariant1 : wariant2;
				cout << result << "\n";
			}
		}
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	bazarek();
	return 0;
}