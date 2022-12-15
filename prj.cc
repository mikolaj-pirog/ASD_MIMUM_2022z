#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

void proj() {
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> wagi(n + 1);
	vector<set<int>> dependOnMe(n + 1);
	vector<int> myDependcies(n + 1, 0);
	for (int i = 1; i <= n; i++)
		cin >> wagi[i];

	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		dependOnMe[b].insert(a);
		myDependcies[a]++;
	}

	auto cmp = [](pair<int, int> first, pair<int, int> snd) {
		if (first.second >= snd.second)
			return true;
		return false;
	};

	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

	for (int i = 1; i < myDependcies.size(); i++) {
		if (myDependcies[i] == 0)
			q.push(pair(i, wagi[i]));
	}
	int i = 0;
	int maks = q.top().second;
	while (i < k) {
		auto min = q.top();
		q.pop();
		if (min.second > maks)
			maks = min.second;

		for (auto dependent: dependOnMe[min.first]) {
			myDependcies[dependent]--;
			if (myDependcies[dependent] == 0)
				q.push({dependent, wagi[dependent]});
		}
		dependOnMe[min.first].clear();
		i++;
	}

	cout << maks << "\n";
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	proj();
	return 0;
}