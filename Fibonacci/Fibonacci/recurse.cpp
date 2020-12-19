#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <math.h>
using namespace std;


int fibonacci(int n) {
    if (n < 2)
        return 1;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int fib_iter(int n) {
    int result = 0;
    int prev = 1;
    int pprev = 1;

    if (n < 2)
        return 1;

    for (int i = 1; i < n; i++) {
        result = prev + pprev;
        pprev = prev;
        prev = result;
    }
    return result;
}

int fib(int current, int previous, int n) {
    if (n <= 1)
        return current;
    else
        return fib(current + previous, current, n - 1);
}

int recursive_start(int n) {
    return fib(1, 1, n);
}

int main()
{
    clock_t oldtime, newtime;
    double seconds;
    int n;


    cout << "Enter an integer " << endl;
    cin >> n;
    oldtime = clock();
    int rval = fib_iter(n);
    newtime = clock();
    seconds = (double)(newtime - oldtime) / CLOCKS_PER_SEC;
    cout << "Fib iter " << n << " = " << rval << "  took " << seconds << endl;
    oldtime = clock();
    rval = recursive_start(n);
    newtime = clock();
    seconds = (double)(newtime - oldtime) / CLOCKS_PER_SEC;
    cout << "Fib recursive O(n) " << n << " = " << rval << "  took " << seconds << endl;
    oldtime = clock();
    rval = fibonacci(n);
    newtime = clock();
    seconds = (double)(newtime - oldtime) / CLOCKS_PER_SEC;
    cout << "Fib " << n << " = " << rval << "  took " << seconds << endl;
}