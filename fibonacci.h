#include <iostream>
#include "array.h"

class Fibonacci {
    public:
    static long long F(const int N) {
        if (N == 0) {return 0;}
        if (N == 1) {return 1;}

        long long farray[N+1];
        farray[0] = 0;
        farray[1] = 1;

        for (int i = 2; i <= N; i++) {
            farray[i] = farray[i-1] + farray[i-2];
        }

        return farray[N];
    }

    static void output() {
        for (int N = 0; N < 100; N++) {
            std::cout << N << " " << F(N) << std::endl;
        }
    }
    

};