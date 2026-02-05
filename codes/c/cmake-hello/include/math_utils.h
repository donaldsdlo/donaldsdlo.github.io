#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// 数学工具函数头文件

// 计算阶乘
unsigned long long factorial(int n);

// 计算幂
double power(double base, int exp);

// 计算平方根（牛顿迭代法）
double sqrt_newton(double n);

// 判断素数
int is_prime(int n);

// 计算最大公约数
int gcd(int a, int b);

// 计算最小公倍数
int lcm(int a, int b);

#endif // MATH_UTILS_H
