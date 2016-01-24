/* http://codeforces.com/contest/617/problem/E */
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#define MAXN 100001
#define BLOCK 555 // ~sqrt(N)
using namespace std;

unordered_map<int, int> val_count;

struct query {
    int L, R;
    int id;
} ;

long long add_val(int val, int k) {
    int ans = val_count[val ^ k];
    //cout << "add val:" << val << " ans:" << ans<< "\n";
    ++val_count[val];
    return ans;
}

long long del_val(int val, int k) {
    --val_count[val];
    //cout << "remove val:" << val << " ans:" << val_count[val ^ k] << "\n";
    return val_count[val ^ k];
}

bool cmp(const query &A, const query &B) {
    if (A.L / BLOCK != B.L / BLOCK) {
        return A.L / BLOCK < B.L / BLOCK;
    }
    return A.R < B.R;
}

int main() {
    
    int n, m, k;
    vector<int> arr(MAXN);
    vector<long long> ans(MAXN);
    vector<query> q(MAXN);

    cin >> n >> m >> k;
    arr[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        arr[i] ^= arr[i-1];
    }
    for (int i = 0; i < m; ++i) {
        cin >> q[i].L >> q[i].R;
        q[i].id = i;
    }

    sort(q.begin(), q.begin() + m, cmp);
    long long cur_ans = 0;
    int cur_L = 0, cur_R = 0;
    val_count[0] = 1;
    for (int i = 0; i < m; ++i) {
        while (cur_R < q[i].R) {
            ++cur_R;
            cur_ans += add_val(arr[cur_R], k);
        }
        while (cur_R > q[i].R) {
            cur_ans -= del_val(arr[cur_R], k);
            --cur_R;
        }
        while (cur_L < q[i].L - 1) {
            cur_ans -= del_val(arr[cur_L], k);
            ++cur_L;
        }
        while (cur_L > q[i].L - 1) {
            --cur_L;
            cur_ans += add_val(arr[cur_L], k);
        }
        ans[q[i].id] = cur_ans;
        //cout << q[i].L << " " << q[i].R << " " << q[i].id << " res:" << cur_ans << "\n";
    }
    
    for (int i = 0; i < m; ++i) {
        cout << ans[i] << "\n";
    }
   
    return 0;
}




