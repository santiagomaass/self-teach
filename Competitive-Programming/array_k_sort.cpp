#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// max common divisor
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// finds mcd in vector
int find_mcd(vector<int> v) {
    int result = v[0];
    for (int i = 0; i < v.size(); i++) {
        result = gcd(result, v[i]);
        if (result == 1)
            return 1;  // if gcd is 1, no need to continue, as gcd can't be larger than 1.
    }
    return result;
}

int main() {
    int t, n; 
    cin >> t;
    // for each case
    for(int i=0; i<t; i++) {
        cin >> n; // length of array
        vector<int> v(n);
        vector<int> dist; // distance to sorted position
        for(int i=0; i<n; i++) { 
            cin >> v[i];
            int d = abs(v[i] - 1 - i); // distance
            if(d > 0) {
                dist.push_back(d);
            }
        }
        // idea: k equals to the larger number that divides all the distances
        cout << find_mcd(dist) << endl;
    }
    return 0;
}
