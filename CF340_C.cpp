/* http://codeforces.com/contest/617/problem/C */
#include <iostream>
#include <algorithm>
using namespace std;

pair<long long, int> dist_r1[2004];
pair<long long, int> dist_r2[2004];
bool covered[2004];

long long dist(long long x1, long long y1, long long x2, long long y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

int main() {

    int n;
    long long x1, y1, x2, y2;

    cin >> n >> x1 >> y1 >> x2 >> y2;
    for (int i = 1; i <= n; ++i) {
        long long x, y;
        cin >> x >> y; 
        dist_r1[i].first = dist(x1, y1, x, y);
        dist_r2[i].first = dist(x2, y2, x, y);
        dist_r1[i].second = dist_r2[i].second = i;
    }

    sort (dist_r1 + 1, dist_r1 + n + 1);
    sort (dist_r2 + 1, dist_r2 + n + 1);
    dist_r2[0].first = dist_r2[0].second = 0;
    int last_cov_r2 = n;
    long long sol = dist_r2[n].first;
    for (int i = 1; i <= n; ++i) {
        covered[dist_r1[i].second] = true;
        while (last_cov_r2 && covered[dist_r2[last_cov_r2].second]) {
            --last_cov_r2;
        }
        if (sol > dist_r1[i].first + dist_r2[last_cov_r2].first) {
            sol = dist_r1[i].first + dist_r2[last_cov_r2].first;
        }
    }

    cout << sol;
    return 0;
}
