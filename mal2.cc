#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int neareastPow2(int n) {
	int i = 1;
	for (; i < n;) { i *= 2; }

	return i;
}

constexpr int Mod = 1e9;

class seqTree {
public:
	vector<pair<char, int>> tree;
	int B;

	seqTree(int n) : tree(2 * neareastPow2(n) + 1, pair('C', 0), B(neareastPow2(n))){};

	void insert(int a, int b, char c, int l, int r, int indeks) {

	}

};


void mal() {
	int n, m, a, b;
	char c;
	cin >> n >> m;
	seqTree tree(n);
	seqTree::B = neareastPow2(n);

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		tree.insert_interval(a, b, c);
		cout << tree.tree[1].second << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	mal();
	return 0;
}