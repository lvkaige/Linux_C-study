#include<stdio.h>
#include<stdlib.h>

struct person{
	char *name;
	int age;
};

struct person *create_person(char *n,int num){
	struct person *who=(struct person*)malloc(sizeof(struct person));
	who->name=n;
	who->age=num;
	return who;
};

void delete(struct person* who){
	free(who);
}

int main(){
	struct person *tom=create_person("tom",30);
	printf("%s\n%d\n",tom->name,tom->age);
	delete(tom);
	return 0;
}
