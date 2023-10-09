#include <stdio.h>

int main(int argc, char *argv[])
{
    // 建立整形数组保存年龄，字符串数组保存名字
		int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // 打印每个名字对应的年龄
    for(i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }

    printf("---\n");

    // 指针是保存地址的变量，cur_age与cue_name各自指向了数组的首地址（第一个元素）
    int *cur_age = ages;
    char **cur_name = names;

    // 注意这里的*符号，是一个取此地址数据的符号
    for(i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }

    printf("---\n");

    // 指针指向了数组，此时可以把指针名字当作是数组名字，使用[]符号就可以访问各个元素
    for(i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // fourth way with pointers in a stupid complex way
    // 不难理解，只是写法有点复杂，本质和第29行的方法一样
		for(cur_name = names, cur_age = ages;
            (cur_age - ages) < count;
            cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }

    return 0;
}
