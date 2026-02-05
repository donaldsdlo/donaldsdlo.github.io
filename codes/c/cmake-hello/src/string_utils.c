#include "string_utils.h"
#include <ctype.h>

size_t my_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char *my_strcpy(char *dest, const char *src) {
    char *original = dest;
    while ((*dest++ = *src++) != '\0');
    return original;
}

char *my_strcat(char *dest, const char *src) {
    char *original = dest;
    
    // 移动到 dest 的末尾
    while (*dest != '\0') {
        dest++;
    }
    
    // 复制 src
    while ((*dest++ = *src++) != '\0');
    
    return original;
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

void my_strrev(char *str) {
    if (!str || !*str) return;
    
    int len = my_strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int is_palindrome(const char *str) {
    if (!str) return 0;
    
    int left = 0;
    int right = my_strlen(str) - 1;
    
    while (left < right) {
        // 跳过非字母数字字符
        while (left < right && !isalnum((unsigned char)str[left])) left++;
        while (left < right && !isalnum((unsigned char)str[right])) right--;
        
        if (tolower((unsigned char)str[left]) != tolower((unsigned char)str[right])) {
            return 0;
        }
        
        left++;
        right--;
    }
    
    return 1;
}

void to_upper(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

void to_lower(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}
