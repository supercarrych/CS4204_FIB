#include "fibonacci.h"

int fib(int n) {
    int i, Fnew, Fold, temp, ans;

    Fnew = 1;
    Fold = 0;
    for (i = 2; i <= n; i++) { /* apsim_loop 1 0 */
        temp = Fnew;
        Fnew = Fnew + Fold;
        Fold = temp;
    }
    ans = Fnew;
    return ans;
}

int payload1(int i) {
    return (fib(900090000));
}

int payload2(int j) {
    return (fib(900090000));
}
