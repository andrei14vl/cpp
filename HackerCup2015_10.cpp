#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct star {
    int x, y;

    int dist(const star &b) const {
       return (this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y);
    }

} central_node;

ifstream f("input.txt");
ofstream g("output.txt");

bool cmp(const star &a, const star &b) {
    int d1 = a.dist(central_node); 
    int d2 = b.dist(central_node); 

    return d1 < d2;
}

int main() {

    int T;

    f >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        star s[2000], s2[2000];

        f >> N;
        for (int i = 0; i < N; ++i) {
            f >> s[i].x >> s[i].y;
            s2[i] = s[i];
        }

        long long boom_count = 0;
        for (int i = 0; i < N; ++i) { 
            central_node = s2[i];
            sort(s, s+N, cmp);
          
            for (int j = 1; j < N; ++j) {
                long long nr = 1;
                int cur_d = s2[i].dist(s[j]);
            
                for (++j; j < N && s2[i].dist(s[j]) == cur_d; ++j, ++nr) ;
                --j;
                boom_count += nr * (nr - 1) / 2;
            } 
        }

        g << "Case #" << t << ": " << boom_count << "\n"; 

    }

    return 0;
}
                
