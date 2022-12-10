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
	static int B;

	seqTree(int n) : tree(2 * neareastPow2(n) + 1, pair('C', 0)){};

	void insert_interval(int a, int b, char color, int l = 1, int r = B, int indeks = 1) {
		if (a <= l && r <= b) {
			tree[indeks].first = color;
			int nowaSuma = color == 'B' ? r - l + 1 : 0;
			tree[indeks].second = nowaSuma;
			return;
		}

		if (tree[indeks].first != 'S') {
			tree[2 * indeks].first = tree[indeks].first;
			tree[2 * indeks].second = tree[indeks].second / 2;
			tree[2 * indeks + 1].first = tree[indeks].first;
			tree[2 * indeks + 1].second = tree[indeks].second / 2;
			tree[indeks].first = 'S';
		}

		if ((l + r) / 2 >= a && tree[2 * indeks].first != color)
			insert_interval(a, b, color, l, (l + r) / 2, 2 * indeks);

		if ((l + r) / 2 + 1 <= b && tree[2 * indeks + 1].first != color)
			insert_interval(a, b, color, (l + r) / 2 + 1, r, 2 * indeks + 1);

		tree[indeks].second = tree[2 * indeks].second + tree[indeks * 2 + 1].second;
	}
};


int seqTree::B;

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