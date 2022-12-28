#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

struct island {
    int number;
    pair<int, int> cords;

    island(int number, int x, int y) : number(number), cords(x, y) {};
};

void dijkstra(vector<map<int, int>> &graph, int n, int end) {
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<>> toCalc;
    toCalc.push({0, 0});
    while (true) {
        auto node = toCalc.top();
        toCalc.pop();
        if (visited[node.second])
            continue;

        for (auto el: graph[node.second]) {
            toCalc.push({el.second + node.first, el.first});
        }
        visited[node.second] = true;
        if (node.second == n - 1) {
            cout << node.first << "\n";
            return;
        }

    }

}

void kap() {
    auto dist = [](island a, island b) {
        return min(abs(a.cords.first - b.cords.first),
                   abs(a.cords.second - b.cords.second));
    };
    int n;
    cin >> n;
    vector<island> see;
    vector<map<int, int>> graph(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        see.emplace_back(i, x, y);
    }

    sort(see.begin(), see.end(), [](const island a, const island b) {
        return bool(a.cords.first < b.cords.first);
    });

    for (int i = 0; i < n - 1; i++) {
        graph[see[i].number].insert({see[i + 1].number, dist(see[i], see[i + 1])});
        graph[see[i + 1].number].insert({see[i].number, dist(see[i], see[i + 1])});
    }

    sort(see.begin(), see.end(), [](const island a, const island b) {
        return bool(a.cords.second < b.cords.second);
    });
    int end = n - 1;
    for (int i = 0; i < n - 1; i++) {
        if (see[i].number == n - 1)
            end = i;
        graph[see[i].number].insert({see[i + 1].number, dist(see[i], see[i + 1])});
        graph[see[i + 1].number].insert({see[i].number, dist(see[i], see[i + 1])});
    }


    dijkstra(graph, n, end);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    kap();
    return 0;
}