#include <bits/stdc++.h>
using namespace std;

int greatestCommonDivisor(int a, int b) {
    int temp;
    while (1) {
        temp = a % b;
        if (temp == 0)
            return b;
        a = b;
        b = temp;
    }
}

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }

    return true;
}

// Function to generate two random prime numbers within a given range
std::pair<int, int> generateTwoRandomPrimes(int lower, int upper) {
    srand(static_cast<unsigned>(time(0)));
    int prime1 = 0, prime2 = 0;
    
    while (true) {
        int num = lower + rand() % (upper - lower + 1);
        if (isPrime(num)) {
            prime1 = num;
            break;
        }
    }
    
    while (true) {
        int num = lower + rand() % (upper - lower + 1);
        if (isPrime(num) && num != prime1) {
            prime2 = num;
            break;
        }
    }
    
    return std::make_pair(prime1, prime2);
}

// Function to calculate n and phi
std::pair<int, int> generatePublicKey(int lower, int upper) {
    std::pair<int, int> primes = generateTwoRandomPrimes(lower, upper);
    int p1 = primes.first;
    int p2 = primes.second;
    
    int n = p1 * p2;
    int phi = (p1 - 1) * (p2 - 1);
    
    return std::make_pair(n, phi);
}

int getExponent(int phi) {
    int e = 2;
    while (e < phi) {
        if (greatestCommonDivisor(e, phi) == 1)
            break;
        else
            e++;
    }
    return e;
}

// Extended Euclidean Algorithm to find modular inverse
int modInverse(int e, int phi) {
    int t = 0, newT = 1;
    int r = phi, newR = e;
    while (newR != 0) {
        int quotient = r / newR;
        t = t - quotient * newT;
        r = r - quotient * newR;

        swap(t, newT);
        swap(r, newR);
    }
    if (r > 1) return -1; // e is not invertible
    if (t < 0) t = t + phi;
    return t;
}

int main() {
    int lower = 100;
    int upper = 999;

    // Generate public key (n, e) and private key d
    std::pair<int, int> result = generatePublicKey(lower, upper);
    int n = result.first;
    int phi = result.second;
    int e = getExponent(phi);
    int d = modInverse(e, phi);

    if (d == -1) {
        printf("Error in finding modular inverse.");
        return 1;
    }

    int message = 12;

    // Encrypt the message: c = (msg ^ e) % n
    int c = (int)pow(message, e) % n;
    printf("\nEncrypted data = %d", c);

    // Decrypt the message: m = (c ^ d) % n
    int m = (int)pow(c, d) % n;
    printf("\nOriginal Message Sent = %d\n", m);

    return 0;
}
