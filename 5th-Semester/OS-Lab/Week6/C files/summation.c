#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 
void* sumFunction(void* arg){
	int n = *((int*)arg);
	int* sum = malloc(sizeof(int));
	*sum = 0;
	for (int i=1; i<=n; ++i)
		*sum = *sum + i;
	return sum;
}

int main(){
	int n;
	printf ("Enter any non-negative integer : ");
	scanf ("%d", &n);
	
	pthread_t sumThread;
	pthread_create (&sumThread, NULL, &sumFunction, &n);
	
	void* result;
	pthread_join(sumThread, &result);
	
	int* sum = (int*) result;
	printf("Sum of the non-negative numbers from 1 to %d is : %d", n, *sum);
	
	return 49;
}
