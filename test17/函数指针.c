#include <stdio.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int main(void)
{
    int (*p)(int, int); //函数指针的定义
    //int (*p)();       //函数指针的另一种定义方式，不过不建议使用
    //int (*p)(int a, int b);   //也可以使用这种方式定义函数指针
    
    p = max;    //函数指针初始化

    int ret = p(10, 15);    //函数指针的调用
    //int ret = (*max)(10,15);
    //int ret = (*p)(10,15);
    //以上两种写法与第一种写法是等价的，不过建议使用第一种方式
    printf("max = %d \n", ret);
    return 0;
}

