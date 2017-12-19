#include <stdio.h>
#include <stdlib.h>

int var1 = 0;
int var2;

char *var3;

static int var4;

void static_test(){
	static int num = 0;
	num ++;
	
	printf("num is %d\n", num);
}

int main(int argc, char * argv[]){
	
	int i;
	int *j;
	
	for (i = 0 ; i < 5 ; i ++){
		static_test();
	}
	
	j = (int *)malloc(sizeof(int));
	*j = 10;
	printf("j : %d\n", *j);
	
	return 0;
}
