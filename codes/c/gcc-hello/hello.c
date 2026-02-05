#include <stdio.h>
#include <stdlib.h>

// 计算阶乘的函数
unsigned long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 计算斐波那契数列的函数
int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
    printf("=== C Program Demo ===\n\n");
    
    // 演示：计算阶乘
    printf("Factorial calculations:\n");
    for (int i = 0; i <= 10; i++) {
        printf("  %d! = %llu\n", i, factorial(i));
    }
    
    printf("\n");
    
    // 演示：斐波那契数列
    printf("Fibonacci sequence:\n");
    printf("  ");
    for (int i = 0; i < 15; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    
    printf("\n=== End of Demo ===\n");
    
    return 0;
}
