#include <iostream>

using namespace std;

void matryca() {
	string tapeta;
	cin >> tapeta;
	unsigned long long minOdleglosci = 1000001;
	unsigned long long i = 0;
	char poprzedniZnak = '\0';
	unsigned long long pozycja = 0;
	auto rozmiarTapety = tapeta.size();

	if (tapeta[0] == '*') {
		for (; i < rozmiarTapety; i++) {
			if (tapeta[i] != '*')
				break;
		}
	}

	poprzedniZnak = tapeta[i];
	for (; i < rozmiarTapety; i++) {
		unsigned long long j = i;
		for (; j < rozmiarTapety; j++) {
			if (tapeta[j] == '*')
				continue;
			else if (tapeta[j] == poprzedniZnak) {
				pozycja = j;
				continue;
			} else {
				minOdleglosci = min(j - pozycja - 1, minOdleglosci);
				poprzedniZnak = tapeta[j];
				pozycja = j;
				break;
			}
		}
		i = j;
	}

	if (minOdleglosci == 1000001) {
		cout << "1\n";
		return;
	}
	cout /*<< minOdleglosci << endl*/
	        << tapeta.size() - minOdleglosci << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	matryca();
	return 0;
}