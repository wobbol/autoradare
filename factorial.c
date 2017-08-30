#include <stdio.h>
#include <stdlib.h>

#include <math.h>


int main(int argc, char *argv[])
{
	//int n = atoi(argv[1]);
	int n = 100;
	if (n <= 1){
		printf("1\n");
		return 0;
	}
	int i;
	double long result = 1;
	for(i = 1; i < n+1; i++){
		result *= i;
	} 
	printf("%'.Lf\n",result);
	return 0;
}
