/* http://codeforces.com/contest/617/problem/B */
#include <iostream>
using namespace std;

long long sol[999];

void mul(long long B)
{
      long long i, t = 0;
      for (i = 1; i <= sol[0] || t; i++, t /= 10)
              sol[i] = (t += sol[i] * B) % 10;
      sol[0] = i - 1;
}

int main() {

    int n;
    
    cin >> n;
    long long  zero_count = 1;
    int x,i = 0;
    sol[0] = sol[1] = 1;
    do {
        cin >> x;
        ++i;
    } while ((x == 0) && (i < n));

    if (i >= n && x == 0) {
        cout << 0;
        return 0;
    }

    for (; i < n; ++i) {
        cin >> x;
        if (x == 0) {
            ++zero_count;
        } else {
            mul(zero_count);
            zero_count = 1;
        }
    }

    for (long long i = sol[0]; i > 0; --i) {
        cout << sol[i];
    }

    return 0;
}

