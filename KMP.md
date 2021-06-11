### KMP （The Knuth-Morris-Pratt Algorithm）

本文代码来自于[中国大学MOOC](https://www.icourse163.org/learn/ZJU-93001?tid=1003997005#/learn/content?type=detail&id=1007588527&cid=1009165213)

[KMP课件下载](https://nos.netease.com/edu-lesson-pdfsrc/5C4C0E5034E43DB3AD5A994156BD4D8D-1541934012176?download=KMP.pdf&Signature=Kv6I%2FJ3dPtxt5e4xw26MboN3s0jpTH5Q9AN14toQuA0%3D&Expires=1621614432&NOSAccessKeyId=7db2f370ff9a412987155d36d55a6ead)

注释内容为自己理解，如有错误请评论，或者私信给我，谢谢
```c
#include <stdio.h>
#include "stdlib.h"
#include "string.h"

typedef int Position;

Position KMP(char string[25], char pattern[7]);

void BuildMatch(char *pattern, int *pInt);

#define NotFound -1

int main() {
    char string[] = "this is a simple example";
    char pattern[] = "simple";
    Position p = KMP(string, pattern);
    if (p == NotFound) printf("Not found.\n");
    else {
        printf("%s\n", string + p);
        printf("%f\n", p);
    }
    return 0;
}

Position KMP(char *string, char *pattern) {
    int n = strlen(string);
    int m = strlen(pattern);
    int s, p, *match;

    if (m > n) return NotFound;
    match = (int *) malloc(sizeof(int) * m);
    // 查询match最长匹配字符串位置值 例如：图1-1
    // pattern a    b   c   a   b
    // index   0    1   2   3   4
    // match   -1   -1  -1  0   1
    BuildMatch(pattern, match);

    s = p = 0;
    while (s < n && p < m) {
        if (string[s] == pattern[p]) {
            s++;
            p++;
        } else if (p > 0) {
            // 将p置为 前p-1个元素 最大子串长度+1
            // 如图1-2
            p = match[p - 1] + 1;
        } else
            s++;
    }
    return (p == m) ? (s - m) : NotFound;
}

void BuildMatch(char *pattern, int *match) {
    int i, j;
    int m = strlen(pattern);
    match[0] = -1;// -1 表示子串长度不存在，无任何相同的元素
    for (int j = 1; j < m; ++j) {
        // i表示前j-1个元素最大相同子串长度 数组索引位置 index-length 0-1
        i = match[j - 1];

        while ((i >= 0) && (pattern[i + 1] != pattern[j]))
            // 第j个下标的字符和(match[j-1]+1)下标上的元素比较
            // 如果不匹配，则根据下标为match[j-1]的相同串基础上进行条件比较
            // 因为match[j-1]已经存在，那么绿紫色整块和后面绿紫块肯定一样
            // 又第一个小绿块为match[match[j-1]]，绿块和紫块相同
            // 所以第一个绿块和最后一个紫块相同，只需比较问号位置的值即可
            // char[match[match[j-1]]+1] 和 char[j] 的值是否相等
            // 如图 1-3
            i = match[i];

        if (pattern[i + 1] == pattern[j])
            // 如图 1-4
            match[j] = i + 1;
            // 如果都匹配不上就直接设置为-1
        else match[j] = -1;
    }
}
```


![图1-1](https://img2020.cnblogs.com/blog/2023890/202105/2023890-20210522003400396-1490389296.png)
<div style="text-align: center;">图1-1</div>

`match[j]`的值实际上是前j个（包括j）元素的最大子串长度 对应到数组中的位置 比如图中 `j = 6;` 最大子串(abca)的长度为4, 在数组中的索引为3

-------
![图1-2](https://img2020.cnblogs.com/blog/2023890/202105/2023890-20210522003416750-869603514.png)
<div style="text-align: center;">图1-2</div>

当比较到后面不相等时，模式串相当于要后移到从上往下的第三个横条的情形，也就是把第二个横条情况`p = match[p-1]+1`

-------
![图1-3](https://img2020.cnblogs.com/blog/2023890/202105/2023890-20210522003428839-760678242.png)
<div style="text-align: center;">图1-3</div>

- 第j个下标的字符和`(match[j-1]+1)`下标上的元素比较
- 如果不匹配，则根据下标为`match[j-1]`的相同串基础上进行条件比较
- 因为`match[j-1]`已经存在，那么绿紫色整块和后面绿紫块肯定一样
- 又第一个小绿块为`match[match[j-1]]`，绿块和紫块相同
- 所以第一个绿块和最后一个紫块相同，只需比较问号位置的值即可
- `char[match[match[j-1]]+1]` 和 `char[j]` 的值是否相等
-------
![图1-4](https://img2020.cnblogs.com/blog/2023890/202105/2023890-20210522003447948-744442378.png)
<div style="text-align: center;">图1-4</div>
