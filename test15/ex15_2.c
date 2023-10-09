#include<stdio.h>

int main(){
	
	//int age[]={1,2,3,4,5};
	//char *name[]={"tom","jerry","bob","sam","alice"};
	
	//int count=sizeof(age)/sizeof(age[0]);

	/*
	for(int i=0;i<count;i++){
		printf("%s => %d\n",name[i],age[i]);
	}
	*/

	/*
	int *p1=age;
	char **p2=name;
	for(int i=0;i<count;i++){
		printf("%s => %d\n",*(p2++),*(p1++));
	}
	*/

	int num[5];
	int *age=num,**name;
	*(age++)=1;
	*(age++)=2;
	*(age++)=3;
	*(age++)=4;
	*age=5;
	age-=4;

	printf("%d\n",*age);

	return 0;
}
