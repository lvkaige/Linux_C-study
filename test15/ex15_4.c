#include<stdio.h>

int main(){
	int num[5]={1,2,3,4,5};
	int *p=num;
	for(int i=0;i<5;i++){
		printf("%d\n",p++);
	}
	return 0;
}
