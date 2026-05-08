---
title: "ACM 循环语句练习"
author: ["Donald Lo"]
date: 2026-03-03
lastmod: 2026-04-22T14:20:24+08:00
tags: ["ACM", "loop"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [输出一个 99 乘法表](#输出一个-99-乘法表)
- [鸡兔同笼问题](#鸡兔同笼问题)
- [求如下表达式的值](#求如下表达式的值)
- [打印三角形问题](#打印三角形问题)
- [水仙花数（Narcissistic Number）](#水仙花数-narcissistic-number)
- [素数](#素数)
    - [1. 试除法 (Trial Division)](#1-dot-试除法--trial-division)
    - [2. 埃拉托斯特尼筛法 (Sieve of Eratosthenes)](#2-dot-埃拉托斯特尼筛法--sieve-of-eratosthenes)
    - [3. 线性筛法 / 欧拉筛 (Linear Sieve / Euler Sieve)](#3-dot-线性筛法-欧拉筛--linear-sieve-euler-sieve)
    - [4. 米勒 - 拉宾素性测试 (Miller-Rabin Primality Test)](#4-dot-米勒-拉宾素性测试--miller-rabin-primality-test)
    - [5. AKS 素性测试 (AKS Primality Test)](#5-dot-aks-素性测试--aks-primality-test)
    - [总结与选择建议](#总结与选择建议)
- [冒泡排序](#冒泡排序)
    - [什么是冒泡排序？](#什么是冒泡排序)
    - [基本思想](#基本思想)
    - [图解](#图解)
    - [评价算法好坏](#评价算法好坏)
    - [实例分析](#实例分析)
    - [代码展示](#代码展示)
    - [优化？](#优化)
- [选择排序](#选择排序)
    - [什么是选择排序？](#什么是选择排序)
    - [基本思想](#基本思想)
    - [图解](#图解)
    - [评价算法好坏](#评价算法好坏)
    - [实例分析](#实例分析)
    - [代码展示](#代码展示)
    - [优化？](#优化)
    - [选择排序与冒泡排序的比较](#选择排序与冒泡排序的比较)

</div>
<!--endtoc-->



## 输出一个 99 乘法表 {#输出一个-99-乘法表}

{{< figure src="/content-org/acm/0003-loop-practice.org/2026-03-03_21-42-04_screenshot.png" width="90%" >}}

**注意：** 输出的时候不用输出格线

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            cout << j << "*" << i << "=" << i * j;
            if (j < i) cout << "\t";
        }
        cout << endl;
    }
    return 0;
}
```


## 鸡兔同笼问题 {#鸡兔同笼问题}

问：鸡兔同笼有30个头，90只脚，求鸡兔各有多少？

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    int heads = 30, feet = 90;

    for (int chicken = 0; chicken <= heads; chicken++) {
        int rabbit = heads - chicken;
        if (2 * chicken + 4 * rabbit == feet) {
            cout << "鸡: " << chicken << endl;
            cout << "兔: " << rabbit << endl;
        }
    }

    return 0;
}
```

当然除了上面的暴力循环的方式，还可以使用如下的方式解决（能用数学方法来解决的问题，就不要用循环的方式来处理）：

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    int heads = 30, feet = 90;

    // 设鸡有 x 只，兔有 y 只
    // x + y = heads
    // 2x + 4y = feet
    // 解得：y = (feet - 2*heads) / 2
    //       x = heads - y

    int rabbit = (feet - 2 * heads) / 2;
    int chicken = heads - rabbit;

    cout << "鸡: " << chicken << endl;
    cout << "兔: " << rabbit << endl;

    return 0;
}
```


## 求如下表达式的值 {#求如下表达式的值}

\\[ s = 1 + (1+2)+(1+2+3)+ ... + (1+2+3 .. +n) \\]

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, s = 0, sum = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    sum += i;
    s += sum;
  }
  cout << s << endl;
}
```


## 打印三角形问题 {#打印三角形问题}

```bash
*****
 ****
  ***
   **
    *
```

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  for(int i=0;i<n;i++) {
    for(int j=i;j<n;j++) {
      cout << '*';
    }
    cout << '\n'; // 如果使用 endl，会刷新缓冲区，导致速度下降
  }
}
```

上面这个程序能实现结果吗？你需要怎么修改？

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  for(int i=0;i<n;i++) {
    for(int j=0;j<i;j++) {
      cout << ' ';
    }
    for(int j=i;j<n;j++) {
      cout << '*';
    }
    cout << '\n'; // 如果使用 endl，会刷新缓冲区，导致速度下降
  }
}
```


## 水仙花数（Narcissistic Number） {#水仙花数-narcissistic-number}

定义： 水仙花数是指一个 \\(n\\) 位数，其各位数字的 \\(n\\) 次方之和等于该数本身。
示例：

-   3位数水仙花数：
    -   \\(153 = 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153\\)
    -   \\(370 = 3^3 + 7^3 + 0^3 = 27 + 343 + 0 = 370\\)
    -   \\(371 = 3^3 + 7^3 + 1^3 = 27 + 343 + 1 = 371\\)
    -   \\(407 = 4^3 + 0^3 + 7^3 = 64 + 0 + 343 = 407\\)
-   1位数：
    -   0, 1, 2, 3, 4, 5, 6, 7, 8, 9（各位数字的1次方等于自身）
-   4位数：1634、8208、9474 等
-   5位数：54748、92727、93084 等

别名： 也称为自恋数、阿姆斯特朗数（Armstrong Number）

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    for (int n = 100; n <= 999; n++) {
        int a = n / 100;       // 百位
        int b = n / 10 % 10;  // 十位
        int c = n % 10;        // 个位

        int sum = a*a*a + b*b*b + c*c*c;

        if (sum == n) {
            cout << n << endl;
        }
    }
    return 0;
}
```


## 素数 {#素数}

判断素数（Prime Number）的算法有很多，根据数据范围的大小和对效率的要求，可以选择不同的算法。以下是从基础到高级的常见算法分类：


### 1. 试除法 (Trial Division) {#1-dot-试除法--trial-division}

这是最直观、最基础的算法，适合判断 **单个较小整数** 是否为素数。

-   **基本思路** ：
    如果要判断 \\(n\\) 是否为素数，尝试用 \\(2\\) 到 \\(n-1\\) 之间的所有整数去除 \\(n\\)。如果都不能整除，则 \\(n\\) 是素数。
-   **优化版本（常用）** ：
    1.  只需试除到 \\(\sqrt{n}\\) 即可。因为如果 \\(n\\) 有因子，必然有一个因子小于等于 \\(\sqrt{n}\\)。
    2.  除了 2 以外，只需试除奇数。
-   **时间复杂度** ：\\(O(\sqrt{n})\\)
-   **适用场景** ：判断单个大数（如 \\(10^{9}\\) 以内）是否为素数。

**C++ 代码示例：**

```cpp
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false; // 排除偶数
    for (int i = 3; i * i <= n; i += 2) { // 只遍历奇数到 sqrt(n)
        if (n % i == 0) return false;
    }
    return true;
}
```

---


### 2. 埃拉托斯特尼筛法 (Sieve of Eratosthenes) {#2-dot-埃拉托斯特尼筛法--sieve-of-eratosthenes}

这是最经典的 **批量求素数** 算法，适合找出 \\(1\\) 到 \\(N\\) 范围内的所有素数。

-   **基本思路** ：
    1.  创建一个布尔数组，初始假设所有数都是素数。
    2.  从 2 开始，将 2 的所有倍数标记为合数。
    3.  找到下一个未被标记的数（即素数），将其所有倍数标记为合数。
    4.  重复直到处理完 \\(\sqrt{N}\\)。
-   **时间复杂度** ： \\(O(N \log \log N)\\)
-   **空间复杂度** ： \\(O(N)\\)
-   **适用场景** ： \\(N\\) 在 \\(10^7\\) 或 \\(10^8\\) 以内，需要快速获取大量素数。

**C++ 代码示例：**

```cpp
const int MAXN = 1000005;
bool is_prime[MAXN];
vector<int> primes;

void sieve(int n) {
    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    // 收集素数
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
}
```

---


### 3. 线性筛法 / 欧拉筛 (Linear Sieve / Euler Sieve) {#3-dot-线性筛法-欧拉筛--linear-sieve-euler-sieve}

埃氏筛法的缺点是某些合数会被多次标记（例如 6 会被 2 和 3 各标记一次）。线性筛法保证了 **每个合数只被其最小质因子标记一次** 。

-   **基本思路** ：
    维护一个素数表。遍历每个数 \\(i\\)，用当前已知的素数 \\(p\\) 去乘 \\(i\\) 来标记合数。一旦 \\(i\\) 能被 \\(p\\) 整除，就停止（保证 \\(p\\) 是 \\(i \times p\\) 的最小质因子）。
-   **时间复杂度** ： \\(O(N)\\) （真正的线性时间）
-   **适用场景** ：\\(N\\) 较大（如 \\(10^7\\) ~ \\(10^8\\)），且对时间要求极其严格，或者需要同时计算积性函数（如欧拉函数 \\(\phi\\)、莫比乌斯函数 \\(\mu\\)）。

**C++ 代码示例：**

```cpp
const int MAXN = 1000005;
bool is_prime[MAXN];
int primes[MAXN], cnt = 0;

void linear_sieve(int n) {
    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] <= n; ++j) {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0) break; // 关键步骤：保证线性复杂度
        }
    }
}
```

---


### 4. 米勒 - 拉宾素性测试 (Miller-Rabin Primality Test) {#4-dot-米勒-拉宾素性测试--miller-rabin-primality-test}

这是一种 **概率算法** ，用于判断 **非常大的整数** （如 \\(10^{18}\\) 甚至更大）是否为素数。

-   **基本思路** ：
    基于费马小定理和二次探测定理。通过选取若干个随机底数进行测试。如果通过了所有测试，该数极大概率是素数。
-   **特点** ：
    -   可以通过选取特定的基底，使其在 \\(64\\) 位整数范围内变成 **确定性算法** （即结果 100% 正确）。
    -   速度非常快。
-   **时间复杂度** ：\\(O(k \log^3 n)\\)，其中 \\(k\\) 是测试轮数。
-   **适用场景** ：判断单个超大整数（超过 \\(10^9\\)，甚至达到 \\(10^{18}\\) 或更高）是否为素数。

---


### 5. AKS 素性测试 (AKS Primality Test) {#5-dot-aks-素性测试--aks-primality-test}

-   **地位** ：第一个被证明的、通用的、确定性的、多项式时间的素性测试算法（2002年提出）。
-   **现状** ：虽然理论意义重大，但在实际应用中，由于常数项过大，速度远不如米勒 - 拉宾测试，因此很少在编程竞赛或工程中使用。

---


### 总结与选择建议 {#总结与选择建议}

| 场景                                                  | 推荐算法      | 原因                |
|-----------------------------------------------------|-----------|-------------------|
| **判断单个小整数** (\\(n < 10^9\\))                   | **试除法 (优化版)** | 代码简单，速度足够快。 |
| **批量求 \\(1 \sim N\\) 的素数** (\\(N \le 10^7\\))   | **埃拉托斯特尼筛法** | 实现简单，效率高。  |
| **批量求 \\(1 \sim N\\) 的素数** (\\(N\\) 很大) 或 **需计算积性函数** | **线性筛 (欧拉筛)** | 复杂度 \\(O(N)\\)，最优解。 |
| **判断单个超大整数** (\\(n > 10^9\\))                 | **米勒 - 拉宾测试** | 试除法太慢，筛法空间不够，此算法最快。 |


## 冒泡排序 {#冒泡排序}

{{< figure src="/content-org/acm/0003-loop-practice.org/v2-5a15e1d04745123a0cc6de5a90e881d9_b.gif" >}}

冒泡排序算法，一种通过交换数据元素位置来进行排序的交换排序算法。

---


### 什么是冒泡排序？ {#什么是冒泡排序}

定义来自于[维基百科，冒泡排序，Bubble Sort.](https://en.wikipedia.org/wiki/Bubble_sort)

冒泡排序，有时被称为“下沉排序”(sinking sort)，是一种简单的排序算法，它反复地遍历列表进行排序，[遍历过程](https://zhida.zhihu.com/search?content_id=8141823&content_type=Article&match_order=1&q=%E9%81%8D%E5%8E%86%E8%BF%87%E7%A8%8B&zhida_source=entity)中比较每一对相邻的项，如果它们的顺序是相反的，则交换它们。对列表的遍历是持续进行的，一直到列表变成有序，不需要交换为止。该算法是一种比较排序，它以更小或更大的元素（根据实际情况而定）“冒泡”到列表顶部的方式命名。该算法的优点是很简单，通俗易懂；但对于大多数问题来说，它太费时间且不切实际。如果输入列表中大部分元素都是有序的，只有一些很少的无序元素，那么气泡排序是可行的。

简而言之，我们假设要求是把输入数组中的元素按照从小到大排好序；那么从一个列表的头部开始，比较两个相邻的元素，如果第一个比第二大，则交换它们的位置，如果第二个比第一个大，就不用管它们；接着比较第二个和第三个，第三个和第四个...直到倒数第二个和倒数最后一个；第一遍结束的时候，我们至少可以保证最后一个元素是最大的。然后再继续重复这个过程（第二遍遍历的时候可以加上“保证倒数第二个元素是第二大的”，第三遍遍历的时候可以加上“保证倒数第三个元素是第三大的”......），直到列表中所有的元素都是有序，从小到大的。


### 基本思想 {#基本思想}

**输入** ：一系列的无序元素（比如说，数字）组成的输入数组A

**经过** ：冒泡排序的经过比较通俗易懂，就像我在什么是冒泡排序中介绍里说的一样，我们假设要求是把输入数组中的元素按照从小到大排好序；那么从一个列表的头部开始，比较两个相邻的元素，如果第一个比第二大，则交换它们的位置，如果第二个比第一个大，就不用管它们；接着比较第二个和第三个，第三个和第四个...直到倒数第二个和倒数最后一个；第一遍结束的时候，我们至少可以保证最后一个元素是最大的。然后再继续重复这个过程（第二遍遍历的时候可以加上“保证倒数第二个元素是第二大的”，第三遍遍历的时候可以加上“保证倒数第三个元素是第三大的”......），直到列表中所有的元素都是有序，从小到大的。

**输出** ：输出数组B，里面包含的元素都是A 中的但是已经按照要求拍好了顺序（比如说，从小到大）


### 图解 {#图解}

{{< figure src="/content-org/acm/0003-loop-practice.org/v2-9dd4ecd8b6cdea12a61f5faffbcfe411_b.gif" caption="<span class=\"figure-number\">&#22270;1&nbsp; </span>过程比较快，每次移动都是在对比后进行的" >}}


### 评价算法好坏 {#评价算法好坏}

分类：排序算法

目标数据结构：数组

最坏 时间复杂度 ：比较部分 \\(O(n^2)\\) ，交换部分 \\(O(n^2)\\) ；总体 \\(O(n^2)\\)

最优时间复杂度：比较部分 \\(O(n)\\) ，交换部分 \\(O(1)\\) ；总体 \\(O(n)\\) 【这里解释一下，最好情况也就是原本的输入数组A 里面的元素就是符合条件排好序了，只需要遍历一遍就可以了】

平均时间复杂度：比较部分 \\(O(n^2)\\) ，交换部分 \\(O(n^2)\\) ；总体 \\(O(n^2)\\)

最坏空间复杂度：\\(O(1)\\)


### 实例分析 {#实例分析}

假设现在有输入数组 A{6,5,3,1,8,7,2,4}

第一遍遍历，6和5对比，6比5大，所以交换位置；6和3对比，6比3大，再次交换位置；6和1比较，6比1大，交换位置；现在数组是{5,3,1,6,8,7,2,4}. 6和8对比，6比8小，不变；8和7对比，8比7大，交换位置；8和2对比，交换位置；8和4对比，交换位置；第一遍遍历结果是{5,3,1,6,7,2,4,8}. 我们找出了最大值是8.

第二遍遍历，过程和上述一样，我们找出了第二大的值是7.

第三遍遍历，过程和上述一样，我们找出了第三大的值是6.

......

第八遍遍历，过程和上述一样，我们找出了最小的值是1.

至此，我们得到了输出数组B{1,2,3,4,5,6,7,8}

**流程展示图**

{{< figure src="/content-org/acm/0003-loop-practice.org/v2-a4b8ad55cd4461c0173c92d7735bb106_b.gif" caption="<span class=\"figure-number\">&#22270;2&nbsp; </span>动图图解比较慢，按照从小到大的顺序要求排列" >}}


### 代码展示 {#代码展示}

**伪代码**

伪代码来源：[Bubble sort - Algorithmist](https://www.algorithmist.com/index.php/Bubble_sort)

```c
// 假设我们有一个array 名字是a，尺寸大小是n

swapped = true //设定一个flag, 一开始是正确的
while swapped  //开始交换循环
  swapped = false
  for j from 0 to n - 2  //从0到n-2，为什么是这个循环起始？
     if a[j] > a[j + 1]  //如果前一个数大于后一个数
        swap( a[j], a[j + 1] )   //交换两个数的位置
        swapped = true
```

```c
#include <bits/stdc++.h> // 万能头文件

using namespace std;

int main() {
    // 优化输入输出效率（虽然对于10个数没必要，但是好习惯）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int N = 10;
    int a[N];

    // 1. 输入 10 个整数
    cout << "请输入 10 个整数：" << endl;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    // 2. 执行冒泡排序算法 (严格遵循你的逻辑)
    bool swapped = true; // 设定一个 flag, 一开始是 true (对应伪代码的 "一开始是正确的"，意为需要开始检查)

    // while swapped: 只要发生过交换，就继续下一轮
    while (swapped) {
        swapped = false; // 每一轮开始前，假设已经是有序的（没有发生交换）

        // for j from 0 to n - 2 (修正：防止 a[j+1] 越界)
        // 伪代码中的 "0 to n-1" 通常隐含意思是比较 (j, j+1)，所以 j 只能到 n-2
        for (int j = 0; j < N - 1; ++j) {
            if (a[j] > a[j + 1]) { // 如果前一个数大于后一个数
                swap(a[j], a[j + 1]); // 交换两个数的位置 (使用 STL 的 swap)
                swapped = true;       // 标记发生了交换，说明还需要下一轮
            }
        }
    }

    // 3. 输出排序后的结果
    cout << "排序后的数组：" << endl;
    for (int i = 0; i < N; ++i) {
        cout << a[i] << (i == N - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
```


### 优化？ {#优化}

1.  每次遍历，都不需要考虑已经确定排序好的数。比如说，第一次遍历后，我们知道最后一个数已经确定了，那么最后一个数在下次遍历就不需要考虑了；第二次便利后，倒数第二个数和倒数第一个数就在第三次遍历中不需要被考虑了.....也就是说，第i 次遍历后，倒数第i 个数及其之后的数都不需要在i+1 次遍历中被考虑。

    **伪代码**
    ```c
        // 假设我们有一个array 名字是a，尺寸大小是n

        for i from 1 to n //还是会有n 遍遍历
            swaps = 0
            for j from 0 to n - i //常规交换步骤
            if a[j] > a[j + 1]
            swap( a[j], a[j + 1] )
            swaps = swaps + 1
            if swaps = 0  //当swaps 是0，退出该遍历即可
            break
    ```
    **代码实现：**
    ```c
        #include <bits/stdc++.h>

        using namespace std;

        int main() {
            // 优化输入输出
            ios::sync_with_stdio(false);
            cin.tie(nullptr);

            const int N = 10;
            int a[N];

            // 1. 输入 10 个整数
            cout << "请输入 10 个整数：" << endl;
            for (int i = 0; i < N; ++i) {
        	cin >> a[i];
            }

            // 2. 优化版冒泡排序
            // 伪代码: for i from 1 to n
            for (int i = 1; i <= N; ++i) {
        	int swaps = 0; // 初始化交换计数器

        	// 伪代码: for j from 0 to n - i
        	// 解释：每一轮 i 增加，末尾就有 i 个元素是已经排好序的，不需要再比较
        	// 当 i=1 时，j 跑到 N-2 (比较到 a[N-2] 和 a[N-1])
        	// 当 i=N 时，j < 0，循环直接不执行（虽然理论上此时应该已经 break 了）
        	for (int j = 0; j < N - i; ++j) {
        	    if (a[j] > a[j + 1]) {
        		swap(a[j], a[j + 1]);
        		swaps = swaps + 1;
        	    }
        	}

        	// 伪代码: if swaps = 0 then break
        	// 位置关键：必须在内层 for 循环结束后判断
        	if (swaps == 0) {
        	    // 如果这一轮一次都没交换，说明已经完全有序，提前退出
        	    break;
        	}
            }

            // 3. 输出结果
            cout << "优化算法排序后的数组：" << endl;
            for (int i = 0; i < N; ++i) {
        	cout << a[i] << (i == N - 1 ? "" : " ");
            }
            cout << endl;

            return 0;
        }
    ```
2.  是否能再改进一些？

    > 一个小小的改进就可以了。每次遍历，我们都去追踪数组中的元素是否交换了位置；如果没有，我们就可以放心大胆地认为序列里面的元素已经是有序排列好了的。
    > A small improvement can be made if each pass you keep track of whether or not an element was swapped. If not, you can safely assume the list is sorted.
    > 引自 [Bubble sort - Algorithmist](https://www.algorithmist.com/index.php/Bubble_sort)

    **伪代码**
    ```c
        // 假设我们有一个array 名字是a，尺寸大小是n

        for i from 2 to n //第一遍遍历我们追踪不了元素是否交换了位置，要从第二遍开始进行对比
            swaps = 0
            for j from 0 to n - 2 //只追踪到倒数第二大的数
            if a[j] > a[j + 1]
            swap( a[j], a[j + 1] )
            swaps = swaps + 1
            if swaps = 0
            break
    ```
    **代码实现：**
    ```c
        #include <bits/stdc++.h>

        using namespace std;

        int main() {
            // 优化输入输出
            ios::sync_with_stdio(false);
            cin.tie(nullptr);

            const int N = 10;
            int a[N];

            // 1. 输入 10 个整数
            cout << "请输入 10 个整数：" << endl;
            for (int i = 0; i < N; ++i) {
                cin >> a[i];
            }

            // 2. 优化版冒泡排序
            // 伪代码: for i from 1 to n
            for (int i = 1; i <= N; ++i) {
                int swaps = 0; // 初始化交换计数器

                // 伪代码: for j from 0 to n - i
                // 解释：每一轮 i 增加，末尾就有 i 个元素是已经排好序的，不需要再比较
                // 当 i=1 时，j 跑到 N-2 (比较到 a[N-2] 和 a[N-1])
                // 当 i=N 时，j < 0，循环直接不执行（虽然理论上此时应该已经 break 了）
                for (int j = 0; j < N - i; ++j) {
                    if (a[j] > a[j + 1]) {
                        swap(a[j], a[j + 1]);
                        swaps = swaps + 1;
                    }
                }

                // 伪代码: if swaps = 0 then break
                // 位置关键：必须在内层 for 循环结束后判断
                if (swaps == 0) {
                    // 如果这一轮一次都没交换，说明已经完全有序，提前退出
                    break;
                }
            }

            // 3. 输出结果
            cout << "优化算法排序后的数组：" << endl;
            for (int i = 0; i < N; ++i) {
                cout << a[i] << (i == N - 1 ? "" : " ");
            }
            cout << endl;

            return 0;
        }
    ```

    ---


## 选择排序 {#选择排序}

{{< figure src="../../static/content-org/acm/0003-loop-practice.org/selection-sort.gif" >}}

选择排序算法，一种通过选择最小（或最大）元素来进行排序的简单排序算法。

---


### 什么是选择排序？ {#什么是选择排序}

定义来自于[维基百科，选择排序，Selection Sort.](https://en.wikipedia.org/wiki/Selection_sort)

选择排序是一种简单直观的排序算法。它的工作原理是：首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置；然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。以此类推，直到所有元素排序完毕。该算法的优点是容易理解，实现简单；缺点是无论输入数据如何，时间复杂度都是 \\(O(n^2)\\)，效率较低。

简而言之，我们假设要求是把输入数组中的元素按照从小到大排好序；那么首先在所有元素中找到最小的元素，将它与第一个位置的元素交换；然后在剩下的元素中找到最小的，将它与第二个位置的元素交换；接着在剩下的元素中继续找最小的，与第三个位置交换......直到所有元素都排好序。


### 基本思想 {#基本思想}

**输入** ：一系列的无序元素（比如说，数字）组成的输入数组A

**经过** ：选择排序的基本思想是比较直观的。假设要求是把输入数组中的元素按照从小到大排好序。第一遍遍历，在所有元素中找到最小值，将它与第一个位置的元素交换；第二遍遍历，在剩下的元素中找到最小值，将它与第二个位置的元素交换；第三遍遍历，在剩下的元素中找到最小值，将它与第三个位置的元素交换......重复这个过程，直到倒数第二个元素也确定好了位置。

**输出** ：输出数组B，里面包含的元素都是A 中的但是已经按照要求排好了顺序（从小到大）


### 图解 {#图解}

{{< figure src="../../static/content-org/acm/0003-loop-practice.org/selection-sort-animation.gif" caption="<span class=\"figure-number\">&#22270;3&nbsp; </span>每次选择最小的元素放到前面" >}}


### 评价算法好坏 {#评价算法好坏}

分类：排序算法

目标数据结构：数组

最坏时间复杂度：比较部分 \\(O(n^2)\\)，交换部分 \\(O(n)\\)；总体 \\(O(n^2)\\)

最优时间复杂度：比较部分 \\(O(n^2)\\)，交换部分 \\(O(1)\\)；总体 \\(O(n^2)\\)

平均时间复杂度：比较部分 \\(O(n^2)\\)，交换部分 \\(O(n)\\)；总体 \\(O(n^2)\\)

最坏空间复杂度：\\(O(1)\\)


### 实例分析 {#实例分析}

假设现在有输入数组 A{64, 25, 12, 22, 11}

**流程展示图**

{{< figure src="/content-org/acm/0003-loop-practice.org/v2-9dd4ecd8b6cdea12a61f5faffbcfe411_b.gif" caption="<span class=\"figure-number\">&#22270;4&nbsp; </span>选择排序动态演示" >}}


### 代码展示 {#代码展示}

**伪代码**

伪代码来源：[Selection sort - Algorithmist](https://www.algorithmist.com/index.php/Selection_sort)

```c
// 假设我们有一个array 名字是a，尺寸大小是n

for i from 0 to n - 2  // 从第一个元素到倒数第二个元素
    min_idx = i         // 假设当前位置是最小值
    for j from i + 1 to n - 1  // 在剩下的元素中找最小值
        if a[j] < a[min_idx]   // 如果找到更小的
            min_idx = j        // 更新最小值索引
    if min_idx != i            // 如果最小值不是当前位置
        swap(a[i], a[min_idx]) // 交换
```

```c
#include <bits/stdc++.h>  // 万能头文件

using namespace std;

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int N = 10;
    int a[N];

    // 1. 输入 10 个整数
    cout << "请输入 10 个整数：" << endl;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    // 2. 执行选择排序算法
    // 外层循环：从第一个元素到倒数第二个元素
    for (int i = 0; i < N - 1; ++i) {
        int min_idx = i;  // 假设当前位置是最小值

        // 内层循环：在剩下的元素中找最小值
        for (int j = i + 1; j < N; ++j) {
            if (a[j] < a[min_idx]) {  // 如果找到更小的
                min_idx = j;           // 更新最小值索引
            }
        }

        // 如果最小值不是当前位置，交换
        if (min_idx != i) {
            swap(a[i], a[min_idx]);
        }
    }

    // 3. 输出排序后的结果
    cout << "排序后的数组：" << endl;
    for (int i = 0; i < N; ++i) {
        cout << a[i] << (i == N - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
```


### 优化？ {#优化}

选择排序的优化空间相对有限，但可以考虑以下改进：

1.  \*双向选择排序（鸡尾酒选择排序）\*：每次遍历同时找出最大值和最小值，分别放到两端。这样可以减少遍历次数约一半。

**伪代码**

```c
// 假设我们有一个array 名字是a，尺寸大小是n

left = 0
right = n - 1
while left < right
    min_idx = left
    max_idx = left
    for i from left to right
        if a[i] < a[min_idx]
            min_idx = i
        if a[i] > a[max_idx]
            max_idx = i
    swap(a[left], a[min_idx])
    // 注意：如果最大值在left位置，交换后会移动到min_idx位置
    if max_idx == left
        max_idx = min_idx
    swap(a[right], a[max_idx])
    left = left + 1
    right = right - 1
```

**代码实现：**

```c
#include <bits/stdc++.h>

using namespace std;

int main() {
    // 优化输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int N = 10;
    int a[N];

    // 1. 输入 10 个整数
    cout << "请输入 10 个整数：" << endl;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    // 2. 双向选择排序
    int left = 0, right = N - 1;

    while (left < right) {
        int min_idx = left;
        int max_idx = left;

        // 在当前范围内找最小值和最大值
        for (int i = left; i <= right; ++i) {
            if (a[i] < a[min_idx]) {
                min_idx = i;
            }
            if (a[i] > a[max_idx]) {
                max_idx = i;
            }
        }

        // 将最小值交换到左边
        swap(a[left], a[min_idx]);

        // 重要：如果最大值原本在left位置，现在被交换到了min_idx位置
        if (max_idx == left) {
            max_idx = min_idx;
        }

        // 将最大值交换到右边
        swap(a[right], a[max_idx]);

        left++;
        right--;
    }

    // 3. 输出结果
    cout << "双向选择排序后的数组：" << endl;
    for (int i = 0; i < N; ++i) {
        cout << a[i] << (i == N - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
```

---


### 选择排序与冒泡排序的比较 {#选择排序与冒泡排序的比较}

| 特性 | 选择排序      | 冒泡排序        |
|----|-----------|-------------|
| 交换次数 | 较少 \\(O(n)\\) | 较多 \\(O(n^2)\\) |
| 比较次数 | \\(O(n^2)\\)  | \\(O(n^2)\\)    |
| 最好情况 | \\(O(n^2)\\)  | \\(O(n)\\)      |
| 稳定性 | 不稳定        | 稳定            |
| 适用场景 | 交换成本高的情况 | 基本有序的数组  |

**选择排序适合交换成本高的情况（因为交换次数少），而冒泡排序适合基本有序的数组（最好情况可以是 \\(O(n)\\)）。**
