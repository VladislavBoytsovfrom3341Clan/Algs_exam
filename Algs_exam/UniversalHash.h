#pragma once

#include <random>
#include <limits>


template<typename T>
class UniversalHash
{
	unsigned int m = 0;
	unsigned int p = 0;
	unsigned int a, b = 0;

    unsigned int getNextPrime(unsigned int n) {
        while (!isPrime(n)) ++n;
        return n;
    }

    bool isPrime(unsigned int n) {
        if (n <= 1) return false;
        for (unsigned int i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

    unsigned int getRandom(unsigned int min, unsigned int max) {
        std::random_device rd; 
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> dist(min, max);
        return dist(gen);
    }

public:
	UniversalHash(unsigned int size) :
        m(size)
    {
        p = getNextPrime(std::numeric_limits<int>::max());
        a = getRandom(1, p - 1);
        b = getRandom(0, p - 1);
    }

    unsigned int operator()(T k)
    {
        return ((a * k + b) % p) % m;
    }
};