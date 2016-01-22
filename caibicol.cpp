/* http://www.infoarena.ro/problema/morcovi */
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream f("caibicol.in"); 
ofstream g("caibicol.out");

int main() {
    int n, k, color_count[2];
    vector <int> color(501);
    vector <vector<int> > min_sol(501, vector<int>(501, 999999999));

    f >> n >> k;
    color_count[0] = color_count[1] = 0;
    for (int i = 1; i <= n; ++i) {
        f >> color[i];
        ++color_count[color[i]];
        min_sol[1][i] = color_count[0] * color_count[1];
    }

    for (int stall_id = 2; stall_id <= k; ++stall_id) {
        for (int last_horse_id = n - (k - stall_id); last_horse_id >= stall_id; --last_horse_id) {
            color_count[0] = color_count[1] = 0;
            for (int horse_id = last_horse_id; horse_id >= stall_id; --horse_id) { //selecting the sequence (horse_id...last_horse_id) for this stall
                ++color_count[color[horse_id]];
                min_sol[stall_id][last_horse_id] = min(min_sol[stall_id][last_horse_id], color_count[0] * color_count[1] + min_sol[stall_id - 1][horse_id - 1]);
            }
        }
    }

    g << min_sol[k][n];
    return 0;
}

    
