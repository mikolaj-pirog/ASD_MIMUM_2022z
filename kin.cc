#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr int Mod = 1e9;

int neareastPow2(int n) {
	int i = 1;
	for (; i < n;) { i *= 2; }

	return i;
}

struct seqTree {
	vector<int> tree;
	int B;

	seqTree(int n) : tree(2 * neareastPow2(n) + 1, 0), B(neareastPow2(n)){};

	void insertLeaf(int leaf, int whatToInsert = 1) {
		leaf += B;
		tree[leaf] = whatToInsert % Mod;
		while (leaf != 0) {
			leaf /= 2;
			tree[leaf] = (tree[leaf * 2] + tree[leaf * 2 + 1]) % Mod;
		}
	}

	int biggerThan(int i) {
		int left = i + 1 + B;
		int right = tree.size() - 1;
		if (left > right)
			return 0;
		if (left == right)
			return tree[left];
		int wynik = (tree[left] + tree[right]) % Mod;

		while (left / 2 != right / 2) {
			if (left % 2 != 1) {
				wynik = (wynik + tree[(left / 2) * 2 + 1]) % Mod;
			}

			if (right % 2 != 0)
				wynik = (wynik + tree[(right / 2) * 2]) % Mod;

			left /= 2;
			right /= 2;
		}

		return wynik;
	}
};

using namespace std;

void kin() {
	int n, k;
	cin >> n >> k;
	vector<int> ciag(n + 1);

	for (int i = 1; i <= n; i++)
		cin >> ciag[i];

	vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
	for (int i = 1; i <= n; i++) {
		dp[i][1] = 1;
	}

	for (int l = 2; l <= k; l++) {
		seqTree tree(n);
		for (int i = 1; i <= n; i++) {
			dp[i][l] = tree.biggerThan(ciag[i]) % Mod;
			tree.insertLeaf(ciag[i], dp[i][l - 1]);
		}
	}

	long long res = 0;
	for (int i = 1; i <= n; i++) {
		res = (res + dp[i][k]) % Mod;
	}

	cout << res % Mod<< "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	kin();
	return 0;
}