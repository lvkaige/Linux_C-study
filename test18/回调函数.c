#include<stdio.h>
#include<stdlib.h>

//函数功能：实现累加求和
int func_sum(int n)
{
        int sum = 0;
        if (n < 0)
        {
                printf("n must be > 0\n");
                exit(-1);
        }
        for (int i = 0; i < n; i++)
        {
                sum += i;
        }
        return sum;
}

//这个函数是回调函数，其中第二个参数为一个函数指针，通过该函数指针来调用求和函数，并把结果返回给主调函数
int callback(int n, int (*p)(int))
{
        return p(n);
}

int main(void)
{
        int n = 0;
        printf("please input number:");
        scanf("%d", &n);
        printf("the sum from 0 to %d is %d\n", n, callback(n, func_sum));       //此处直接调用回调函数，而不是直接调用func_sum函数
        return 0;
}

