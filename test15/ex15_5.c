#include<stdio.h>

void show(int *q){
	for(int i=0;i<5;i++){
		printf("%d\n",*(q++));
	}
}

int main(){
	int num[5]={2,4,6,8,10};
	int *p=num;
	show(p);
	return 0;
}
