/* https://www.facebook.com/hackercup/problem/1611251319125133/ */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

ifstream f("input.txt");
ofstream g("output.txt");

struct job {
    long long time;
    long long wi;
} ;

bool operator<(const job& a, const job& b) {
      return a.time > b.time;
}

int main() {

    int T;
    f >> T;
    for (int t = 1; t <= T; ++t) {
        long long L, N, M, D, W;
        priority_queue<job> jobs;

        f >> L >> N >> M >> D;
        for (int i = 1; i <= N; ++i) {
            job j;
            
            f >> W;
            j.time = W;
            j.wi = W;
            jobs.push(j);
        }  
        
        long long waiting_to_dry = M, waiting_for_dry = 0, done = 0;
        while (done < L) {
            job j = jobs.top();
            jobs.pop();

            if (j.wi) {
                //cout << "Time:" << j.time << "done wash\n";
                j.time += j.wi;
                jobs.push(j);

                if (waiting_to_dry > 0) {
                    --waiting_to_dry;
                    j.time += D - j.wi;
                    j.wi = 0;
                    jobs.push(j);
                } else {
                    ++waiting_for_dry;
                }
            } else {
                ++done;
                //cout << "Time:" << j.time << "done dry\n";
                if (done == L) {
                    g << "Case #" << t << ": " << j.time << "\n";
                    break;
                }
                if (waiting_for_dry) {
                    --waiting_for_dry; 
                    j.time += D;
                    j.wi = 0;
                    jobs.push(j);
                } else {
                    ++waiting_to_dry;
                }
            }
        }
    }
    return 0;
}



        
