#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

struct node {
	unordered_map<int, int> koloryDzieci;
	int kolor;
};

void colourNode(vector<int> &parent, int colour, int nd, vector<node> &tree) {
	int kolorDoUsun = tree[nd].kolor;
	tree[nd].kolor = colour;
	while (nd != -1) {
		auto it = tree[nd].koloryDzieci.find(kolorDoUsun);
		if (it != tree[nd].koloryDzieci.end()) {
			it->second--;
			if (it->second == 0)
				tree[nd].koloryDzieci.erase(it);
		}

		it = tree[nd].koloryDzieci.find(colour);
		if (it ==  tree[nd].koloryDzieci.end()) {
			tree[nd].koloryDzieci[colour] = 1;
		} else {
			it->second++;
		}

		nd = parent[nd];
	}
}


void cho() {
	int n, q;
	cin >> n >> q;
	vector<int> parent(n + 1);
	parent[1] = -1;
	for (int i = 2; i <= n; i++) {
		int tmp;
		cin >> tmp;
		parent[i] = tmp;
	}
	vector<node> drzewo(n + 1);
	for (int i = 1; i <= n; i++) {
		int tmp;
		cin >> tmp;
		colourNode(parent, tmp, i, drzewo);
	}

	for (int i = 0; i < q; i++) {
		char a;
		cin >> a;
		if (a == 'z') {
			int b, c;
			cin >> b >> c;

			colourNode(parent, c, b, drzewo);
		} else {
			int b;
			cin >> b;
			auto it = drzewo[b].koloryDzieci.begin();
			if (drzewo[b].koloryDzieci.size() == 1 || (drzewo[b].koloryDzieci.size() == 2 && (it->second == 1 || (++it)->second == 1)))
				cout << "TAK\n";
			else
				cout << "NIE\n";
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cho();
	return 0;
}