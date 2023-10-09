#include<stdio.h>

int main(int argc,char *argv[]){

	// printf("%d %s\n",argc,argv[0]);

	for(int i=0;i<argc;i++){
		printf("第%d个参数. %s\n",i+1,argv[i]);
	}

	return 0;
}
