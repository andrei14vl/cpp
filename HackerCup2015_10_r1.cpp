/* https://www.facebook.com/hackercup/problem/798506286925018/ */
#include <iostream>
#include <vector>
#include <fstream>
#define MAX_RES 400000
using namespace std;

ifstream f("input.txt");
ofstream g("output.txt");

int necessary_between(int val_cur, int val_prev, int p_cur, int p_prev) {
    int dif1 = p_cur - p_prev - 1, dif2 = p_cur + 4 - p_prev - 1;

    if (p_cur <= p_prev) { //only dif2 is available
        if (100 - p_prev >= 4 - p_prev && val_cur >= p_cur) 
            return dif2;
        return MAX_RES;
    } else { // both dif1 and dif2 are available
        int min_res = MAX_RES;
        
        if (100 - p_prev >= 4 - p_prev && val_cur >= p_cur) 
            min_res = dif2;

        if (val_cur <= val_prev) 
            return min_res;

        if ((val_cur - val_prev <= (dif1 + 1) * 10)
            && (val_cur - val_prev -1 >= dif1))
            return min(min_res, dif1);
    }

    return MAX_RES;
}


int main() {

    int T;

    f >> T;
    for (int t = 1; t <= T; ++t) {
        int N;
        vector<int> D(100001, 0);

        f >> N;
        for (int i = 1; i <= N; ++i) {
            f >> D[i];
        }

        vector<vector<int> > sol(100001, vector<int>(5, MAX_RES));
    
        sol[0][4] = 0;
        D[0] = 100;

        for (int i = 1; i <= N; ++i) {
            for (int p_cur = 1; p_cur < 5; ++p_cur) {
                for (int p_prev = 1; p_prev < 5; ++p_prev) {
                    int temp = necessary_between(D[i], D[i-1], p_cur, p_prev);
                    if (sol[i-1][p_prev] + temp < sol[i][p_cur]) {
                        sol[i][p_cur] = sol[i-1][p_prev] + temp;
                    }
                }
                //cout << sol[i][p_cur] << ", ";
            }
            //cout << "\n";
        }

        g << "Case #" << t << ": " << min(min(sol[N][1] + 3, sol[N][2] + 2), min(sol[N][3] + 1, sol[N][4])) << "\n";
    }

    return 0;
}

