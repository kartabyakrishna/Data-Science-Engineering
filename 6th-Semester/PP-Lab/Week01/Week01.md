Sure, here are C programs for each of the scenarios you provided:

### 1) Reverse Digits of an Integer Array
```c
#include <stdio.h>

void reverseDigits(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        int num = arr[i];
        int reversed = 0;
        
        while (num > 0) {
            int digit = num % 10;
            reversed = reversed * 10 + digit;
            num /= 10;
        }
        
        arr[i] = reversed;
    }
}

int main() {
    int arr[] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Reverse the digits
    reverseDigits(arr, size);

    // Display the reversed array
    printf("Output array: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
```

### 2) Calculator Simulation
```c
#include <stdio.h>

int main() {
    double A, B;

    // Input values
    printf("Enter value for A: ");
    scanf("%lf", &A);
    printf("Enter value for B: ");
    scanf("%lf", &B);

    // Perform operations
    printf("A + B = %.2f\n", A + B);
    printf("A - B = %.2f\n", A - B);
    printf("A * B = %.2f\n", A * B);

    // Check for division by zero
    if (B != 0) {
        printf("A / B = %.2f\n", A / B);
    } else {
        printf("Cannot divide by zero.\n");
    }

    return 0;
}
```

### 3) Toggle Characters in a String
```c
#include <stdio.h>

void toggleCharacters(char str[]) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += ('a' - 'A');
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= ('a' - 'A');
        }
    }
}

int main() {
    char str[] = "HeLLo";

    // Toggle characters
    toggleCharacters(str);

    // Display the result
    printf("Toggled string: %s\n", str);

    return 0;
}
```

### 4) Pattern Generation from Input Word
```c
#include <stdio.h>

void printPattern(char word[], int length) {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < i; ++j) {
            printf("%c", word[i]);
        }
    }
    printf("\n");
}

int main() {
    char word[20];
    
    // Input word
    printf("Enter a word: ");
    scanf("%s", word);

    // Display the pattern
    printPattern(word, strlen(word));

    return 0;
}
```

Note: These programs assume valid inputs and may need additional error handling for production use.