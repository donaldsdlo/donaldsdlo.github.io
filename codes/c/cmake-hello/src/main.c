#include <stdio.h>
#include "math_utils.h"
#include "string_utils.h"

int main(void) {
    printf("=== CMake Multi-File Project Demo ===\n\n");
    
    // 演示数学工具函数
    printf("=== Math Utils Demo ===\n");
    printf("Factorial of 5: %llu\n", factorial(5));
    printf("2^10: %.2f\n", power(2.0, 10));
    printf("sqrt(2): %.6f\n", sqrt_newton(2.0));
    printf("Is 17 prime? %s\n", is_prime(17) ? "Yes" : "No");
    printf("GCD(48, 18): %d\n", gcd(48, 18));
    printf("LCM(4, 6): %d\n", lcm(4, 6));
    
    printf("\n=== String Utils Demo ===\n");
    char str1[100] = "Hello";
    char str2[100] = "World";
    char str3[100] = "A man a plan a canal Panama";
    
    printf("Original string: %s\n", str1);
    printf("Length: %zu\n", my_strlen(str1));
    
    my_strcat(str1, " ");
    my_strcat(str1, str2);
    printf("After concatenation: %s\n", str1);
    
    to_upper(str1);
    printf("Uppercase: %s\n", str1);
    
    to_lower(str1);
    printf("Lowercase: %s\n", str1);
    
    my_strrev(str2);
    printf("Reversed 'World': %s\n", str2);
    
    // 移除空格后检查回文
    printf("\n=== Palindrome Check ===\n");
    printf("String: \"%s\"\n", str3);
    printf("Is palindrome (ignoring spaces): %s\n", 
           is_palindrome(str3) ? "Yes" : "No");
    
    printf("\n=== End of Demo ===\n");
    
    return 0;
}
