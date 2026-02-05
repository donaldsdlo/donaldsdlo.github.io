#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>

// 字符串工具函数头文件

// 计算字符串长度
size_t my_strlen(const char *str);

// 复制字符串
char *my_strcpy(char *dest, const char *src);

// 连接字符串
char *my_strcat(char *dest, const char *src);

// 比较字符串
int my_strcmp(const char *s1, const char *s2);

// 反转字符串
void my_strrev(char *str);

// 判断回文字符串
int is_palindrome(const char *str);

// 将字符串转换为大写
void to_upper(char *str);

// 将字符串转换为小写
void to_lower(char *str);

#endif // STRING_UTILS_H
