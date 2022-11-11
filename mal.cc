#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;


auto cmp = [](pair<int, int> lhs, pair<int, int> rhs) {//Przedziały są definicje rozłączne parami. Dlatego to działa.
	if (lhs.first >= rhs.first)
		return true;

	return false;
};

void malowanie() {
	int n, m;
	cin >> n >> m;
	set<pair<int, int>, decltype(cmp)> autostrada(cmp);
	autostrada.insert(pair(0, n));
	//autostrada.insert(pair(1, 5));
	//autostrada.insert(pair(3, 3));
	//auto wyn = autostrada.lower_bound(pair(3, 5));
	//cout << wyn->first << " " << wyn->second;
	//printSet(autostrada);
	for (int i = 0; i < m; i++) {
		bool nieUsuwamy = false;
		char malowanie;
		int pocz, kon;
		cin >> pocz >> kon >> malowanie;
		if (malowanie == 'C') {
			auto odcinek = pair(pocz, kon);
			auto inf = autostrada.lower_bound(odcinek);
			auto sup = autostrada.upper_bound(odcinek);
			auto poczUsuwanie = inf;
			auto konUsuwanie = sup;
			if (inf != autostrada.end() && inf == sup) {
				auto infW = *inf;
				auto supW = *sup;
				autostrada.erase(inf);
				if (infW.first <= pocz - 1)
					autostrada.insert(pair(infW.first, pocz - 1));
				if (supW.second >= kon + 1)
					autostrada.insert(pair(kon + 1, supW.second));
			} else {
				if (inf == autostrada.end()) {
					poczUsuwanie = autostrada.begin();
				} else {
					auto infW = *inf;
					if (infW.second >= pocz) {
						poczUsuwanie++;
						if (poczUsuwanie == autostrada.end())
							nieUsuwamy = true;
						autostrada.erase(inf);
						if (infW.first <= pocz - 1)
							autostrada.insert(pair(infW.first, pocz - 1));
					} else {
						poczUsuwanie++;
					}
				}

				if (sup == autostrada.end()) {
					konUsuwanie = autostrada.end();
					konUsuwanie--;
				} else {
					auto supW = *sup;
					if (supW.first <= kon) {
						if (konUsuwanie == autostrada.begin())
							nieUsuwamy = true;
						else
							konUsuwanie--;
						autostrada.erase(sup);
						if (supW.second >= kon + 1)
							autostrada.insert(pair(kon + 1, supW.second));
					} else {
						konUsuwanie--;
					}
				}
			}

			if (!nieUsuwamy && *poczUsuwanie <= *konUsuwanie)
				autostrada.erase(poczUsuwanie, konUsuwanie);
		}
	}

	for (auto el: autostrada)
		cout << el.first << " " << el.second << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	malowanie();
	return 0;
}