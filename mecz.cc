#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

void mecz() {
	int n, m;
	cin >> n >> m;
	vector<long long> zawodnicyBitFlaga(n, 0ll);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			int tmp;
			cin >> tmp;
			if (j < n / 2)
				zawodnicyBitFlaga[tmp - 1] = zawodnicyBitFlaga[tmp - 1] | (1ll << i);
		}

	unordered_set<long long> result(zawodnicyBitFlaga.begin(), zawodnicyBitFlaga.end());
	if (result.size() == n) {
		cout << "TAK\n";
	} else {
		cout << "NIE\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	mecz();
	return 0;
}