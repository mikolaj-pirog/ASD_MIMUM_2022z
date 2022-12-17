#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

struct node {
    map<int, int> koloryDzieci;
    int kolor;
};

void colourNode(vector<int> &parent, int colour, int nd, vector<node> &tree) {
    int kolorDoUsun = tree[nd].kolor;
    tree[nd].kolor = colour;
    while(parent[nd] != -1) {
        if (tree[nd].koloryDzieci.find(kolorDoUsun) != tree[nd].koloryDzieci.end()) {
            tree[nd].koloryDzieci[kolorDoUsun]--;
            if (tree[nd].koloryDzieci[kolorDoUsun]==0)
                tree[nd].koloryDzieci.erase(kolorDoUsun);
        }

        if (tree[nd].koloryDzieci.find(colour) == tree[nd].koloryDzieci.end()) {
            tree[nd].koloryDzieci[colour] = 1;
        } else {
            tree[nd].koloryDzieci[colour]++;
        }

        nd = parent[nd];
    }
}


void cho() {
    int n,q;
    cin >> n >> q;
    vector<int> parent(n+1);
    parent[1] = -1;
    for (int i = 2; i <= n; i++) {
        int tmp;
        cin >> tmp;
        parent[i] = tmp;
    }
    vector<node > drzewo(n+1);
    for (int i = 1; i <= n; i++) {
        int tmp;
        cin >> tmp;
        colourNode(parent, tmp, i, drzewo);
    }

    for (int i = 0; i < q; i++) {
        char a;
        cin >> a;
        if (a == 'z') {
            int b,c;
            cin >> b >> c;

            colourNode(parent, c, b, drzewo);
        } else {
            int b;
            cin >> b;
            if (drzewo[b].koloryDzieci.size() == 1 || (drzewo[b].koloryDzieci.size() == 2 && (drzewo[b].koloryDzieci.begin()->second == 1 || drzewo[b].koloryDzieci.begin()++->second == 1)))
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