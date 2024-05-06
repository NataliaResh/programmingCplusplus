#include <iostream>

template <int N, int M>
struct isPrime
    : std::conditional_t<(N % M == 0), std::integral_constant<bool, false>, isPrime<N, M - 1>> {};

template <int N>
struct isPrime<N, 1> : std::integral_constant<bool, true> {};

template <int N>
struct PrimeLoop
    : std::conditional_t<isPrime<N, N - 1>{}, std::integral_constant<int, N>, PrimeLoop<N + 1>> {};

template <int N>
struct Prime : PrimeLoop<Prime<N - 1>{} + 1> {};

template <>
struct Prime<1> : std::integral_constant<int, 2> {};

int main() {
    std::cout << Prime<50>{} << "\n";
}
