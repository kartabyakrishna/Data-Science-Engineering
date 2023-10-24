#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

int nums[MAX_SIZE];

void* genPrime (void* arg){
	int* range = (int*) arg;
	int st = range[0];
	int end = range[1];
	int count = 0;
	
	bool isPrime[end + 1];
    	for (int i = 0; i <= end; ++i)
    		isPrime[i] = true;

    	for (int p = 2; p*p <= end; ++p) {
        	if (isPrime[p]) {
            		for (int i = p*p; i <= end; i += p)
            			isPrime[i] = false;
    		}
    	}
    	
    	for (int i = st; i <= end; ++i) {
        	if (isPrime[i])	
        		nums[count++] = i;
	}
	nums[count] = -1;
	
	return NULL;
}
int main() {
    int st, end;
    int range[2];

    printf("Enter the starting number: ");
    scanf("%d", &st);
    range[0] = st;
    printf("Enter the ending number: ");
    scanf("%d", &end);
    range[1] = end;

    pthread_t threadPrime;

    pthread_create(&threadPrime, NULL, genPrime, range);

    pthread_join(threadPrime, NULL);
    
    printf("The prime numbers between %d and %d are : \n", st, end);
    for (int i=0; nums[i]!=-1; ++i)
    	printf("%d  ", nums[i]);

    return 49;
}
