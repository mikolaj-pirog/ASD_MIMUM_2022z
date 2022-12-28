#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

struct island{
    int number;
    pair<int, int> cords;

    island(int number, int x, int y) : number(number), cords(x,y){};
};

void kap() {
    auto dist = [](island a, island b){return min(abs(a.cords.first - b.cords.first),
               abs(a.cords.second - b.cords.second));};
    int n;
    cin >>n;
    vector<island> see;
    vector<map<int, int>> graph(n); 
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        see.push_back( island(i, x, y));
    }

      sort(see.begin(), see.end(), [](const island a, const island b){
        return bool(a.cords.first < b.cords.first);
    });

    for (int i = 0; i < n - 1; i++) {
        graph[see[i].number].insert({see[i + 1].number, dist(see[i], see[i+1])});
        graph[see[i+1].number].insert({see[i].number, dist(see[i], see[i+1])});
    }

    sort(see.begin(), see.end(), [](const island a, const island b){
        return bool(a.cords.second < b.cords.second);
    });

     for (int i = 0; i < n - 1; i++) {
        graph[see[i].number].insert({see[i + 1].number, dist(see[i], see[i+1])});
        graph[see[i+1].number].insert({see[i].number, dist(see[i], see[i+1])});
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}