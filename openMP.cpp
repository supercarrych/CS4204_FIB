// gcc example.c -o example


#include<omp.h>
#include <chrono>
#include <stdio.h>
#include <iostream>
#include <vector>

//
//int fib(int n) {
//    int i, Fnew, Fold, temp, ans;
//
//    Fnew = 1;
//    Fold = 0;
//
//
//    for (i = 2; i <= n; i++) { /* apsim_loop 1 0 */
//        temp = Fnew;
//        Fnew = Fnew + Fold;
//        Fold = temp;
//    }
//    ans = Fnew;
//    return ans;
//}
//
//int payload1(int i) {
//    return (fib(900090000));
//}
//
//int payload2(int j) {
//    return (fib(900090000));
//}


//int main() {
//    // 获取开始时间点
//    auto start = std::chrono::high_resolution_clock::now();
//    int res, res2;
//    printf("Begin\n");
//#pragma omp parallel for
//    for (int i = 0; i < 100; i++) {
//        res = payload1(i);
//        res2 = payload2(res);
////#pragma omp critical//critical 指令确保在同一时刻只有一个线程执行被保护的代码段。
//        {
//            printf("fib(%d) = % d\n", i, res);
//        }
//    }
//
//    printf("End");
//    // 获取结束时间点
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // 计算经过的时间（以毫秒为单位）
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    std::cout << "Execution time: " << duration << " ms" << std::endl;
//
//    return 0;
//}
