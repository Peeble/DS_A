#include <iostream>

class Factorial {
    public: 

    static double lnF(int N) {
        if (N == 1) { return 0;}
        if (N == 2) { return 1;}

        return log(N) + lnF(N-1);
    }

    static void output(int N) {
        double lnFactorial = lnF(N);
        std::cout << "ln(" << N << "!) is: " << lnFactorial << std::endl; 
    }

};