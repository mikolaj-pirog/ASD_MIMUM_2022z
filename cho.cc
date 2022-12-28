#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

int B = 0;

int neareastPow2(int n) {
    int i = 1;
    for (; i < n;) { i *= 2; }

    return i;
}

struct node {
    map<int, int> left;
    map<int, int> right;
};

int
dfs(vector<set<int>> &children, vector<node> &result, vector<pair<int, int>> &descendants, int i) {
    result.emplace_back();
    int begin = result.size() - 1;
    int end = begin;
    for (auto el: children[i]) {
        end = dfs(children, result, descendants, el);
    }
    descendants[i] = pair<int, int>(begin, end);

    return end;
}

void color(int i, int color, vector<node> &tree, bool isFirst) {
    if (isFirst) {
        bool isLeft = true;
        for (int j = i; j != 0; j /= 2) {
            if (isLeft) {
                tree[j].left[color]++;
            } else {
                tree[j].right[color]++;
            }
            if (j % 2 == 0)
                isLeft = true;
            else
                isLeft = false;
        }
    } else {
        int toDelete = tree[i].left.begin()->first;
        bool isLeft = true;
        for (int j = i; j != 0; j /= 2) {
            if (isLeft) {
                int deleteCount = tree[j].left[toDelete];
                if (deleteCount == 1)
                    tree[j].left.erase(toDelete);
                else
                    tree[j].left[toDelete]--;

                tree[j].left[color]++;
            } else {
                int deleteCount = tree[j].right[toDelete];
                if (deleteCount == 1)
                    tree[j].right.erase(toDelete);
                else
                    tree[j].right[toDelete]--;

                tree[j].right[color]++;
            }

            if (j % 2 == 0)
                isLeft = true;
            else
                isLeft = false;
        }
    }
}

bool transferColors(map<int, int> &dest, map<int, int> &source) {
    for (auto el: source) {
        dest[el.first] += el.second;
        if (dest.size() > 2)
            return false;
    }
    return true;
}

bool isSolidColor(vector<node> &tree, pair<int, int> descendants) {
    map<int, int> colors;
    int begin = descendants.first, end = descendants.second;
    colors.insert(*tree[begin].left.begin());
    colors[tree[end].left.begin()->first] += tree[end].left.begin()->second;
    bool isBl = !(begin % 2), isRl = (end % 2);
    begin /= 2;
    end /= 2;
    while (begin != end) {
        if (isBl) {
            if (!transferColors(colors, tree[begin].right))
                return false;

        }

        if (begin % 2 == 0)
            isBl = true;
        else
            isBl = false;

        begin /= 2;

        if (isRl) {
            if (!transferColors(colors, tree[end].left))
                return false;
        }

        if (end % 2 != 0)
            isRl = true;
        else
            isRl = false;

        end /= 2;
        if (colors.size() > 1) {
            auto fir = colors.begin();
            auto snd = fir++;
            if (!(fir->second == 1 || snd->second == 1))
                return false;
        }
    }

    return true;
}

void cho() {
    int n, q;
    cin >> n >> q;
    vector<set<int>> children(n + 1);
    B = neareastPow2(n);
    vector<node> nodes(B + 1);
    vector<pair<int, int>> descendants(n + 1);
    for (int i = 2; i <= n; i++) {
        int tmp;
        cin >> tmp;
        children[tmp].insert(i);
    }

    dfs(children, nodes, descendants, 1);


    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;
        color(descendants[i].first, c, nodes, true);
    }


    for (int i = 0; i < q; i++) {
        char a;
        cin >> a;
        if (a == 'z') {
            int b, c;
            cin >> b >> c;
            color(descendants[b].first, c, nodes, false);
        } else {
            int b;
            cin >> b;
            if (isSolidColor(nodes, descendants[b]))
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