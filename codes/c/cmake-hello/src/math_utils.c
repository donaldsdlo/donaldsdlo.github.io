#include "math_utils.h"
#include <math.h>

unsigned long long factorial(int n) {
    if (n < 0) return 0;
    if (n <= 1) return 1;
    
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double power(double base, int exp) {
    if (exp == 0) return 1.0;
    
    double result = 1.0;
    int positive_exp = exp > 0 ? exp : -exp;
    
    for (int i = 0; i < positive_exp; i++) {
        result *= base;
    }
    
    return exp > 0 ? result : 1.0 / result;
}

double sqrt_newton(double n) {
    if (n < 0) return -1.0;
    if (n == 0) return 0.0;
    
    double x = n;
    double epsilon = 1e-10;
    
    while (fabs(x * x - n) > epsilon) {
        x = (x + n / x) / 2.0;
    }
    
    return x;
}

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    
    return 1;
}

int gcd(int a, int b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}
