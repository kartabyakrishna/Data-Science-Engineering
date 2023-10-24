## Q4 - Write a multithreaded program that generates the _Fibonacci_ series. 

### C program - **fibonacci.c**

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 

#define MAX_SIZE 100
int fibNums[MAX_SIZE];

void* genFib (void* arg){
	int n = *((int*)arg);
	
	int t1 = 0, t2 = 1;
  	int nextTerm = t1 + t2;
  	
  	fibNums[0] = 0;
  	fibNums[1] = 1;
  	
  	int count = 2;
  	
  	for (int i = 3; i <= n; ++i) {
		fibNums[count++] = nextTerm;
    		t1 = t2;
    		t2 = nextTerm;
    		nextTerm = t1 + t2;
  	}
  	fibNums[count] = -1;
  	
  	return NULL;
}
int main(){
	int n;
	printf ("How many Fibonacci numbers need to generate? : ");
	scanf ("%d", &n); 
	
	pthread_t threadFibo;

    	pthread_create(&threadFibo, NULL, genFib, &n);

    	pthread_join(threadFibo, NULL);
    
    	printf("The fibonacci sequence of %d numbers is : \n", n);
    	for (int i=0; fibNums[i]!=-1; ++i)	
    		printf("%d  ", fibNums[i]);

    	return 49;
}
```

### Command to compile the C program
```
gcc -o fibonacci fibonacci.c
```

### Command to run the program
```
./fibonacci
```

### Output
![image](https://github.com/shrudex/DSE/assets/91502997/b8da1026-14ef-4e0c-a55e-cdc75a3adf09)
![image](https://github.com/shrudex/DSE/assets/91502997/4151bb2a-5905-41b8-af92-bb6056cac56b)

