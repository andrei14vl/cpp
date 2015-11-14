/* Given an array of N numbers(v[i] < 100), 
 * find the number of ascending subarrays of length K */
#define LSB(x) (x & (-x))
#include <iostream>
#include <vector>
#include <fstream>
#define MAX_N 405
#define MAX_VAL 105
using namespace std;

ifstream f("nrsubsircresc2.in");
ofstream g("nrsubsircresc2.out");

long long query_aib(const vector<long long> &aib_in, int index) {
    long long total;

    total =  aib_in[index]; 
    while (index > 0) { 
        index -= LSB(index);
        total += aib_in[index];    
    }

    return total;
}

void update_aib(vector<long long> &aib_in, int index, long long value) {
    if (value == 0) {
        return ;
    }
    while (index <= MAX_VAL) {
        aib_in[index] += value;
        index += LSB(index);
    }
}

int main() {
    int N, K;
    vector<int> v(MAX_N);
    vector<vector<long long> > aib(MAX_N, vector<long long>(MAX_VAL + 1, 0)); 
    f >> N >> K;
    if (N > 400 || K > N)
        return -1;
    for (int i = 0; i < N; ++i) {
        f >> v[i];
        if (v[i] > 100)
            return -1;
    }

    for (int i = 0; i < N; ++i) {
        for (int l = min(i + 1, K); l > 1; --l) {
            /* query the aib for the length l-1 
             * and update the aib for l */
            /* this is the current number of ascending subarrays 
             * with the last element < v[i] */ 
            long long num_subarrays = query_aib(aib[l-1], v[i] - 1);
            //cout << v[i] << " " << num_subarrays << "\n";
            update_aib(aib[l], v[i], num_subarrays);
        }
        update_aib(aib[1], v[i], 1);
    }
    
    g << query_aib(aib[K], MAX_VAL) << "\n";

    return 0;
}
            



