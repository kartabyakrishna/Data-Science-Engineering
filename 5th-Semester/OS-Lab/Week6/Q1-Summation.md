## Q1 - Write a multithreaded program that calculates the _summation_ of non-negative integers in a separate thread and passes the result to the main thread.

### C program - **summation.c**

```c
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
```

### Command to compile the C program
```
gcc -o summation summation.c
```

### Command to run the program
```
./summation
```

### Output
![image](https://github.com/shrudex/DSE/assets/91502997/7fc54f40-7e30-4eb7-88f0-84ad2314352d)
![image](https://github.com/shrudex/DSE/assets/91502997/084a7365-6916-46db-b7ec-6f4a5ff33b31)

