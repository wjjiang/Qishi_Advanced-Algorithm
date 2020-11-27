#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void simpleSieve(int limit, vector<int> &prime) {
    vector<bool> mark(limit + 1, true);
 
    for (int p=2; p*p<limit; p++)
        if (mark[p])
            for (int i=p*p; i<limit; i+=p)
                mark[i] = false;
    
    for (int p=2; p<limit; p++)
        if (mark[p]) {
            prime.emplace_back(p);
            cout << p << ", ";
        }
}

void segmentedSieve(int n) {
    int limit = floor(sqrt(n))+1;
    vector<int> prime; 
    simpleSieve(limit, prime);
    
    int low = limit;
    int high = 2*limit;
    
    while (low < n) {
        if (high >= n) 
           high = n;
        
        vector<bool> mark(limit + 1, true);
        
        for (int i = 0; i < prime.size(); i++) {
            int loLim = floor(low/prime[i]) * prime[i];
            if (loLim < low)
                loLim += prime[i];
            for (int j=loLim; j<high; j+=prime[i])
                mark[j-low] = false;
        }
        
        for (int i = low; i<high; i++)
            if (mark[i - low])
                cout << i << ", ";
        
        low = low + limit;
        high = high + limit;
    }
    cout << endl;
}

void eulerSieve(int n) {
    int primeCnt = 0;
    vector<bool> isPrime(n + 1, true);
    vector<int> primes(n + 1, 0);
    
    //memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < n; ++i) {
        if (isPrime[i]) {
            cout << i << ", ";
            primes[primeCnt++] = i;
        }
        for (int j = 0; j < primeCnt && primes[j] * i < n; ++j) {
            isPrime[primes[j] * i] = false;
            if (!(i % primes[j]))
                break;
        }
    }
}
 
int main() {
    int n = 1000;
    cout << "Segmented Sieve, Primes smaller than " << n << ":" << endl;
    segmentedSieve(n);
    cout << "Euler Sieve, Primes smaller than " << n << ":" << endl;
    eulerSieve(n);
    return 0;
}