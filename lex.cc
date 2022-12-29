#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

#define int long long

using namespace std;

const int p = 37;
const int q = 1000003;

int myhash(int from, int to, vector<int> &powers, vector<int> &h) {
    return (h[from] - h[to + 1] * powers[to - from + 1] % q + q) % q;
}

void cmp(int from1, int to1, int from2, int to2, vector<int> &word, vector<int> &powers, vector<int> &h) {
    int flen = to1 - from1, slen = to2 - from2;
    int l = 0;
    int r = min(flen, slen) + 1;
    while (l < r) {
        int i = (l + r) / 2;
        if (myhash(from1, from1 + i, powers, h) == myhash(from2, from2 + i, powers, h)) {
            l = i + 1;
        } else {
            r = i;
        }
    }

    if (flen == slen && flen + 1 == l)
        cout << "=\n";
    else if ((flen < slen && l == min(flen, slen) + 1))
        cout << "<\n";
    else if (flen > slen && l == min(flen, slen) + 1)
        cout << ">\n";
    else if (word[from1+1] < word[from2+1])
        cout << "<\n";
    else
        cout << ">\n";


}

void lex() {
    int n, m;
    cin >> n >> m;
    vector<int> word(n);
    vector<int> powers(n);
    vector<int> hashes(n + 1);
    powers[0] = 1;
    for (int i = 0; i < n; i++) {
        char tmp;
        cin >> tmp;
        word[i] = tmp;
        if (i != 0)
            powers[i] = (p * powers[i - 1]) % q;
    }
    powers.push_back((powers[n - 1] * p) % q);

    hashes[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        hashes[i] = (word[i] + (hashes[i + 1] * p) % q) % q;
    }

    for (int i = 0; i < m; i++) {
        int from1, to1, from2, to2;
        cin >> from1 >> to1 >> from2 >> to2;
        from1--;
        to1--;
        from2--;
        to2--;
        cmp(from1, to1, from2, to2, word, powers, hashes);
    }


}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    lex();
    return 0;
}