## Q3 - Write a multithreaded program for generating _prime numbers_ from a given starting number to the given ending number.

### C program - **primeNumbers.c**

```c
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
```

### Command to compile the C program
```
gcc -o primeNumbers primeNumbers.c
```

### Command to run the program
```
./primeNumbers
```

### Output
![image](https://github.com/shrudex/DSE/assets/91502997/5fab2f14-17d6-4321-befa-60a0146df219)
![image](https://github.com/shrudex/DSE/assets/91502997/311f678a-f351-4885-a347-a5bcdf6b62db)

