#include <vector>
#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

const constexpr int MOD = 1000000007;



int operator+(int X, const int& rhs){
    return 0;
}

int liczbaKombinacjiDwochGrup(std::list<uint32_t> &pier, std::list<uint32_t> &drugi, int l) {

    int wynik = 0;
    auto it_pier = pier.rbegin();
    auto it_drugi = drugi.rbegin();
    int ileDrugiZwiekszany = 0;
    while(it_pier != pier.rend() && it_drugi != drugi.rend()) {
        auto t = *it_pier;
        auto d = *it_drugi;
        if (*it_pier + l <= *it_drugi) {
            wynik = (wynik + 1) % MOD;
            it_drugi++;
            ileDrugiZwiekszany++;
        } else {
            it_pier++;
            if (it_pier != pier.rend())
                wynik = (wynik + ileDrugiZwiekszany) % MOD;

        }
    }

    if (it_pier != pier.rend()) {
        int pozostale = -1;
        while(it_pier != pier.rend()) {
            it_pier++;
            pozostale++;
        }

        wynik = (wynik + wynik * pozostale) % MOD;
    }

    return wynik;

}

void komitet() {
    uint32_t n, k, l;
    cin >> n >> k >> l;
    vector<uint32_t> rangi(n);
    vector< list<uint32_t> > podKomitety;

    for (uint32_t i = 0; i < n; i++) {
        cin >> rangi[i];
    }

    auto drukujPodKomitety = [&]() {
        for (auto &komitet : podKomitety) {
            for (auto czl : komitet)
                cout << czl << " ";
            cout << "\n";
        }
    };

    

    sort(rangi.begin(), rangi.end());
    podKomitety.push_back(list<uint32_t>());


    for (auto ranga : rangi) {
        if (podKomitety.back().size() == 0)
            podKomitety.back().push_back(ranga);
        else {
            if (ranga - podKomitety.back().front() <= k)
                podKomitety.back().push_back(ranga);
            else {
                podKomitety.push_back(list<uint32_t>());
                podKomitety.back().push_back(ranga);
            }
        }
    }

    drukujPodKomitety();


    int wynik = 0;
    int size = podKomitety.size();
    int min = podKomitety.size();
    if (size != 1)
        for (int i = 0; i < size - 1 && size != 1; i += 2) {
            wynik = wynik + (liczbaKombinacjiDwochGrup(podKomitety[i], podKomitety[i + 1], l) % MOD) % MOD;
            podKomitety[i].splice(podKomitety[i].end(), podKomitety[i + 1]);
            podKomitety[i / 2] = podKomitety[i];

            if (i + 1 - size == 1) {
                podKomitety[i / 2 + 1] = podKomitety[i + 2];
                size = i / 2 + 2;
                i = 0;
            } else if (i + 2 >= size - 1) {
                size = i / 2 + 1;
                i = 0;
            }
        }
    else {
        cout << 1 << " " << podKomitety[0].size() << "\n";
        return;
    }


    cout << min << " " << wynik << "\n";
    


}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    komitet();
    return 0;
}