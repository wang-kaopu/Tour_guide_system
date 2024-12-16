#include "main.h"

#include <locale.h>

int main() {
    // setlocale(LC_ALL, ""); // 设置区域信息

    char str[100];

    printf("请输入中文字符串: ");

    // fgets(str, sizeof(str), stdin);
    scanf("%s", &str);

    printf("你输入的中文字符串是: %s", str);

    return 0;
}