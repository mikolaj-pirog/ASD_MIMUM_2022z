#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr int Mod = 1000000000;

int neareastPow2(int n) {
	int i = 1;
	for (; i < n;) { i *= 2; }

	return i;
}

struct seqTree {
	vector<int> tree;
	int B;

	seqTree(int n) : tree(2 * neareastPow2(n) + 1, 0), B(neareastPow2(n)){};

	void insertLeaf(int leaf) {
		leaf += B;
		tree[leaf] = 1;
		while (leaf  != 0) {
			leaf /= 2;
			tree[leaf]++;
		}
	}

	int biggerThan(int i) {
		i++;
		int left = i + B;
		int right = tree.size() - 1;

		int wynik = tree[left] + tree[right];

		while (left / 2 != right / 2) {
			if (left % 2 != 1) {
				wynik = (wynik + tree[(left / 2) * 2 + 1]) % Mod;
			}

			if (right % 2 != 0)
				wynik = (wynik + tree[(right / 2) * 2] % Mod);

			left /= 2;
			right /= 2;
		}

		return wynik;
	}
};

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	seqTree tree(6);
	tree.insertLeaf(6);
	tree.insertLeaf(5);
	tree.insertLeaf(1);
	tree.insertLeaf(2);
	cout << tree.biggerThan(0);
	return 0;
}