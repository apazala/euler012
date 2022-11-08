#include <iostream>
#include <cmath>
#include <cinttypes>

using namespace std;

#define MAXS 2000000

int oneprimefactor[MAXS];
int divfun[MAXS];

int64_t iscompound[1 + (MAXS>>6)];

#define baisset(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) != 0
#define baisclear(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) == 0
#define baset(ba, i) (ba)[(i)>>6] |= (1ull << ((i) & 63))

void fillprimes(int upperBound) {
	int i, j;

	baset(iscompound, 0);
	baset(iscompound, 1);
	int sqrtUb = sqrt(upperBound);
	for (i = 2; i <= sqrtUb; i++) {
		if (baisclear(iscompound, i)) {
            oneprimefactor[i] = i;
            divfun[i] = 2;
			for (j = i*i; j <= upperBound; j += i) {
				baset(iscompound, j);
                oneprimefactor[j] = i;
			}
		}
	}

	for (i = sqrtUb + 1; i <= upperBound; i++) {
		if (baisclear(iscompound, i)) {
            oneprimefactor[i] = i;
            divfun[i] = 2;
		}
	}
}

#define TARGET 500

int main()
{
    int64_t res = -1;

    fillprimes(MAXS);
    divfun[1] = 1;
    for(int i = 2; res == -1 && i < MAXS; i++){
        int d = divfun[i];
        if(d == 0){
            int a = 1;
            int p = oneprimefactor[i];
            int n = i/p;
            while(n > 1 && n%p==0){
                a++;
                n/=p;     
            }   
            //n and p^a are mutually primes:
            d = divfun[n]*(a+1);   
            divfun[i] = d;
        }


        int ndivtri;
        int64_t trin = i;
        trin *= i-1;
        trin >>=1;
        if((i&1) == 0){
            ndivtri = divfun[(i>>1)]*divfun[i-1];            
        }else{
            ndivtri = divfun[i]*divfun[(i-1)>>1];
        }

        if(ndivtri > TARGET){
            res = trin;
        }
    }

    cout << res << endl;

}