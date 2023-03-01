#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>


int N = 0;

template <typename T>
struct F {
    T sum;
    F(): sum(0) {}
    void operator()(T k) { sum += k; }
};

int main() {
    int a[5] = { 1, 2, 3, 4, 5 };
    int n = 0;

    // example 1
    n = 0;
    for (int i = 0; i < 5; ++i) {
        n += a[i];
    }
    std::cout << n << std::endl;


    // example 2
    n = 0;
    for (const auto &e: a) {
        n += e;
    }
    std::cout << n << std::endl;


    // example 3
    N = 0;
    auto sum = [](const int &k) { N += k; };
    std::for_each(a, a + 5, sum);
    std::cout << N << std::endl;


    // example 4
    F<int> fSum = std::for_each(a, a + 5, F<int>());
    std::cout << fSum.sum << std::endl;

    // example 5
    std::cout << std::accumulate(a, a + 5, 0) << std::endl;

    return 0;
}
