/* http://main.edu.pl/en/archive/oi/18/roz */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct sum {
    int cur_min, waiting_min;
    sum () {
        cur_min=999999;
        waiting_min = 0;
    }
}; //partial sum, consider each pair of different chars as +1 and -1

vector<vector<sum> > sums(26, vector<sum>(26));
vector<int> counter(26, 0);

void update_sums(int c_id, int cnt) {
    counter[c_id] += cnt;
    //cout << "\nchar:" << c_id << " cur_counter:" << counter[c_id];
    for (int j = 0; j < 26; ++j) {
        if (j == c_id) {
            continue;
        }
        int cur_dif = counter[j] - counter[c_id];
        if (cnt > 1) {
            //try update cur_min with the partial_sum before the last character(cur_dif + 1)
            sums[j][c_id].cur_min = min(sums[j][c_id].cur_min, cur_dif + 1);
        }
        sums[j][c_id].cur_min = min(sums[j][c_id].cur_min, sums[j][c_id].waiting_min);
        sums[j][c_id].waiting_min = cur_dif;
    }
}

int query(int c_id) {
    int sol = 0;
    
    for (int j = 0; j < 26; ++j) {
        if (j == c_id) {
            continue;
        }
        
        //cout << "\nfor char:" << j << "cur_counter:" << counter[j] << "cur_min:" << sums[c_id][j].cur_min << "waiting_min:" << sums[c_id][j].waiting_min;
        int cur_dif = counter[c_id] - counter[j];
        sol = max(sol, cur_dif - sums[c_id][j].cur_min);
    }

    return sol;
}

int main() {

    int N, sol = 0;
    string S;

    cin >> N >> S;
    for (int i = 0; i < N; ++i) {
        int c_id = S[i] - 'a', cnt = 1;
        
        while (i+1 < N && S[i+1] - 'a' == c_id) {
            ++cnt;
            ++i;
        }

        update_sums(c_id, cnt);
        sol = max(sol, query(c_id));
    } 

    //try again in reverse
    sums =vector<vector<sum> >(26, vector<sum>(26));
    counter = vector<int>(26, 0);
    for (int i = N - 1; i >= 0; --i) {
        int c_id = S[i] - 'a', cnt = 1;
        
        while (i+1 >= 0 && S[i-1] - 'a' == c_id) {
            ++cnt;
            --i;
        }

        update_sums(c_id, cnt);
        sol = max(sol, query(c_id));
    } 
   


    cout << sol;
    return 0;
}

