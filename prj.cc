#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <functional>

using namespace std;

void proj() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> wagi(n);
    vector<set<int> > dependOnMe(n+1);
    vector<int> myDependcies(n+1);
    for (int i = 0; i < n; i++)
        cin >> wagi[i];

    for(int i = 0; i < n; i++) {
        int a,b;
        cin >> a >> b;
        zalezy[b].insert(a);
        myDependcies[a]++;
    }
    
    auto cmp = [](pair<int, int> first, pair<int, int> snd) {
        if (first.second <= snd.second)
            return true;
    };

    priority_queue<pair<int, int>, vector<pair<int,int>> ,decltype(cmp)> q(cmp);

    for (int i = 0; i < zalezy.size(); i++) {
        if (zalezy[i].size() == 0)
            q.push(pair(i, wagi[i]));
    }
    int i = 0;
    int maks = q.top().second;
    while (i < k) {
        auto min = q.top();
        q.pop();
        if (min.second > maks)
            maks = min.second;

        
    }

    
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	return 0;
}