#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Fan {
    int index;
    int likes;
    int stars;

    Fan(int i, int x, int y) : index(i), likes(x), stars(y) {}
};

bool compareFans(const Fan& fan1, const Fan& fan2) {
    int supportLevel_1 = fan1.likes + 2 * fan1.stars;
    int supportLevel_2 = fan2.likes + 2 * fan2.stars;

    if (supportLevel_1 != supportLevel_2)
        return supportLevel_1 > supportLevel_2;
    else if (fan1.index != fan2.index)
        return fan1.index < fan2.index;
    return false;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<Fan> fans;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        fans.push_back(Fan(i + 1, x, y));
    }

    sort(fans.begin(), fans.end(), compareFans);

    vector<int> indexes(k);
    for (int i = 0; i < k; ++i) {
        indexes[i] = fans[i].index;
    }

    sort(indexes.begin(), indexes.end());
    for (int i = 0; i < k; ++i) {
        cout << indexes[i] << " ";
    }

    return 0;
}
