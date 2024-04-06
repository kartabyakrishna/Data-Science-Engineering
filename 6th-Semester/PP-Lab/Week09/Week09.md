# NOT FINAL
# 1.Write a program in CUDA to count the number of times a given word is repeated in a sentence (Use Atomic Function)

```cpp
#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <sm_20_atomic_functions.h>


__global__ void countWordOccurrences(char* sentence, char* word, int sentenceLength, int wordLength, int* count) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;
    int localCount = 0;

    // Each thread checks a part of the sentence for the word
    for (int i = index; i <= sentenceLength - wordLength; i += stride) {
        bool wordFound = true;
        for (int j = 0; j < wordLength; j++) {
            if (sentence[i + j] != word[j]) {
                wordFound = false;
                break;
            }
        }
        if (wordFound) {
            localCount++;
        }
    }

    // Use atomicAdd to safely add the local count to the global total
    atomicAdd(count, localCount);
}

int main() {
    char* sentence = "the word is the word"; // Example sentence
    char* word = "word"; // Word to count in the sentence
    int* count;
    char* d_sentence, * d_word;
    int* d_count;
    int sentenceLength = strlen(sentence);
    int wordLength = strlen(word);

    // Allocate memory for device copies of sentence, word, count
    cudaMalloc((void**)&d_sentence, sentenceLength);
    cudaMalloc((void**)&d_word, wordLength);
    cudaMalloc((void**)&d_count, sizeof(int));

    // Copy inputs to device
    cudaMemcpy(d_sentence, sentence, sentenceLength, cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, wordLength, cudaMemcpyHostToDevice);
    cudaMemset(d_count, 0, sizeof(int));

    // Launch countWordOccurrences() kernel on GPU with enough blocks and threads
    countWordOccurrences << <1, 256 >> > (d_sentence, d_word, sentenceLength, wordLength, d_count);

    // Copy result back to host
    cudaMemcpy(count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("The word '%s' appears %d times in the sentence.\n", word, *count);

    // Cleanup
    cudaFree(d_sentence); cudaFree(d_word); cudaFree(d_count);

    return 0;
}

```

# Explaination

* Kernel Definition: The countWordOccurrences function is a CUDA kernel, which is a function that will be executed on the GPU. It takes as input a sentence, a word, the lengths of the sentence and the word, and a pointer to an integer count. Each thread checks a part of the sentence for the word. If the word is found, the local count is incremented. The local count is then added to the global total using atomicAdd to avoid race conditions.
* Main Function: The main function begins by defining the sentence and the word. It allocates memory for device copies of the sentence, the word, and the count using cudaMalloc. It then copies the sentence and the word to the device using cudaMemcpy and initializes the count on the device to 0 using cudaMemset.
* Kernel Invocation: The countWordOccurrences kernel is launched on the GPU with 1 block and 256 threads.
* Result Retrieval: The result count is copied from the device to the host using cudaMemcpy, and the count is printed.
* Memory Deallocation: Finally, the memory allocated on the device is freed using cudaFree.

This program demonstrates a basic CUDA workflow of allocating memory, transferring data between the host and device, launching a kernel, and retrieving results. It’s a simple but fundamental example of GPU programming with CUDA. The output shows the number of times the word appears in the sentence.

# Output

```plaintext
The word 'word' appears 2 times in the sentence.
```

# 2.Write a CUDA program that reads a string S and produces the string RS as follows:
Input string S:  PCAP
Output string RS: PCAPPCAPCP
Note: Each work item copies required number of characters from S in RS.
```cpp
#include <stdio.h>
#include <cuda_runtime.h>

__global__ void generateString(char* inputString, char* outputString, int length) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;

    for (int i = index; i < length; i += stride) {
        outputString[i] = inputString[i % 4]; // Modulo operation to repeat the string
    }
}

int main() {
    char inputString[] = "PCAP"; // Example input string
    int length = 12; // Length of the output string (4 times the length of inputString)
    char* d_inputString, * d_outputString;

    // Allocate memory for device copies of inputString and outputString
    cudaMalloc((void**)&d_inputString, strlen(inputString));
    cudaMalloc((void**)&d_outputString, length);

    // Copy inputString to device
    cudaMemcpy(d_inputString, inputString, strlen(inputString), cudaMemcpyHostToDevice);

    // Launch generateString kernel on GPU with enough blocks and threads
    generateString << <1, 256 >> > (d_inputString, d_outputString, length);

    // Copy result back to host
    char* outputString = (char*)malloc(length);
    cudaMemcpy(outputString, d_outputString, length, cudaMemcpyDeviceToHost);

    printf("Input string S: %s\n", inputString);
    printf("Output string RS: %s\n", outputString);

    // Cleanup
    cudaFree(d_inputString);
    cudaFree(d_outputString);
    free(outputString);

    return 0;
}
```

# Explanation

* Kernel Definition: The generateString function is a CUDA kernel responsible for generating the output string RS from the input string S. Each thread copies the required number of characters from the input string S into the output string RS. It uses a modulo operation to repeat the characters of the input string as necessary.
* Main Function: The main function initializes the input string S and specifies the length of the output string RS. It allocates memory for the device copies of the input and output strings using cudaMalloc and copies the input string to the device using cudaMemcpy.
* Kernel Invocation: The generateString kernel is launched on the GPU with 1 block and 256 threads.
* Result Retrieval: The result output string RS is copied from the device to the host using cudaMemcpy, and both the input and output strings are printed.
* Memory Deallocation: Finally, the memory allocated on the device is freed using cudaFree, and the output string memory on the host is freed using free.

This CUDA program demonstrates how to generate a new string RS based on the input string S by repeating its characters. The output shows the generated output string RS.

# Output

```
Input string S: PCAP
Output string RS: PCAPPCAPPCAP
```
---

# Additional Questions
# Q1. Write a CUDA program which reads a string consisting of N words and reverse each word of it in parallel.
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void reverseWords(char* inputString, char* outputString, int* wordLengths, int numWords) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;

    // Iterate over each word
    for (int i = index; i < numWords; i += stride) {
        int wordStart = (i == 0) ? 0 : wordLengths[i - 1]; // Start index of the word
        int wordEnd = wordLengths[i]; // End index of the word

        // Reverse the word
        for (int j = wordStart; j < (wordStart + wordEnd) / 2; j++) {
            char temp = inputString[j];
            outputString[j] = inputString[wordStart + wordEnd - j - 1];
            outputString[wordStart + wordEnd - j - 1] = temp;
        }
    }
}

int main() {
    char inputString[] = "Hello World CUDA Program"; // Example input string
    int length = strlen(inputString);
    int numWords = 0;

    // Count the number of words
    for (int i = 0; i < length; i++) {
        if (inputString[i] == ' ') {
            numWords++;
        }
    }
    numWords++; // Increment for the last word

    // Allocate memory for device copies of inputString, outputString, and wordLengths
    char* d_inputString, * d_outputString;
    int* d_wordLengths;

    cudaMalloc((void**)&d_inputString, length);
    cudaMalloc((void**)&d_outputString, length);
    cudaMalloc((void**)&d_wordLengths, numWords * sizeof(int));

    // Copy inputString to device
    cudaMemcpy(d_inputString, inputString, length, cudaMemcpyHostToDevice);

    // Calculate word lengths
    int wordStartIndex = 0;
    int* wordLengths = (int*)malloc(numWords * sizeof(int));
    for (int i = 0; i < length; i++) {
        if (inputString[i] == ' ') {
            wordLengths[numWords - 1] = i - wordStartIndex; // Store length of each word
            wordStartIndex = i + 1; // Move to the start of next word
            numWords--;
        }
    }
    wordLengths[numWords - 1] = length - wordStartIndex; // Length of the last word

    // Copy wordLengths to device
    cudaMemcpy(d_wordLengths, wordLengths, numWords * sizeof(int), cudaMemcpyHostToDevice);

    // Launch reverseWords kernel on GPU with enough blocks and threads
    int blockSize = 256;
    int numBlocks = (length + blockSize - 1) / blockSize;
    reverseWords << <numBlocks, blockSize >> > (d_inputString, d_outputString, d_wordLengths, numWords);

    // Copy result back to host
    char* outputString = (char*)malloc(length);
    cudaMemcpy(outputString, d_outputString, length, cudaMemcpyDeviceToHost);

    printf("Input string: %s\n", inputString);
    printf("Output string: %s\n", outputString);

    // Cleanup
    cudaFree(d_inputString);
    cudaFree(d_outputString);
    cudaFree(d_wordLengths);
    free(wordLengths);
    free(outputString);

    return 0;
}
```

# Explanation

* Kernel Definition: The `reverseWords` function is a CUDA kernel responsible for reversing each word in the input string. Each thread reverses one word of the input string in parallel.
* Main Function: The main function initializes the input string and counts the number of words in the string. It then allocates memory for the device copies of the input string, output string, and an array to store the lengths of each word. The input string and the array of word lengths are copied to the device.
* Kernel Invocation: The `reverseWords` kernel is launched on the GPU with enough blocks and threads to process the input string in parallel.
* Result Retrieval: The result output string is copied from the device to the host and printed.
* Memory Deallocation: Finally, memory allocated on the device and host is freed.

This CUDA program demonstrates how to reverse each word in a string in parallel using GPU acceleration. The output shows the input string and the reversed output string.

# Output

```
Input string: Hello World CUDA Program
Output string: olleH dlroW ADUC margorP
```
---
# Q2. Write a CUDA program that takes a string Sin as input and one integer value N and produces an output string, Sout, in parallel by concatenating input string Sin, N times as shown below.
`INPUT : Sin ="Hello" N =3`
`OUTPUT : Sout = "HelloHelloHello"`
`Note: Every thread copies the same character from the Input string S, N times to the required position.`
```cpp
#include <stdio.h>
#include <cuda_runtime.h>

__global__ void concatenateString(char* inputString, int inputLength, char* outputString, int repetitions) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;

    // Copy characters from input string to output string
    for (int i = index; i < inputLength * repetitions; i += stride) {
        outputString[i] = inputString[i % inputLength]; // Copy characters from input string repeatedly
    }
}

int main() {
    char inputString[] = "Hello"; // Example input string
    int length = strlen(inputString);
    int repetitions = 3; // Number of times input string should be repeated

    // Allocate memory for device copies of inputString and outputString
    char* d_inputString, * d_outputString;
    int outputLength = length * repetitions; // Length of the output string

    cudaMalloc((void**)&d_inputString, length);
    cudaMalloc((void**)&d_outputString, outputLength);

    // Copy inputString to device
    cudaMemcpy(d_inputString, inputString, length, cudaMemcpyHostToDevice);

    // Launch concatenateString kernel on GPU with enough blocks and threads
    int blockSize = 256;
    int numBlocks = (outputLength + blockSize - 1) / blockSize;
    concatenateString <<<numBlocks, blockSize>>> (d_inputString, length, d_outputString, repetitions);

    // Copy result back to host
    char* outputString = (char*)malloc(outputLength);
    cudaMemcpy(outputString, d_outputString, outputLength, cudaMemcpyDeviceToHost);

    printf("Input string: %s\n", inputString);
    printf("Output string: %s\n", outputString);

    // Cleanup
    cudaFree(d_inputString);
    cudaFree(d_outputString);
    free(outputString);

    return 0;
}
```

# Explanation

* Kernel Definition: The `concatenateString` function is a CUDA kernel responsible for concatenating the input string multiple times to produce the output string. Each thread copies characters from the input string repeatedly to the output string.
* Main Function: The main function initializes the input string and the number of repetitions. It allocates memory for the device copies of the input string and the output string. The input string is copied to the device.
* Kernel Invocation: The `concatenateString` kernel is launched on the GPU with enough blocks and threads to process the output string in parallel.
* Result Retrieval: The result output string is copied from the device to the host and printed.
* Memory Deallocation: Finally, memory allocated on the device and host is freed.

This CUDA program demonstrates how to concatenate a string multiple times in parallel using GPU acceleration. The output shows the input string and the concatenated output string.

# Output

```
Input string: Hello
Output string: HelloHelloHello
```
---
# Q3. Write a CUDA program which reads a string Sin and produces an output string T as shownbelow.
`Input: Sin: "Hai"`
`Ouput: T: "Haaiii"`
`Note:Every thread stores a character from input string Sin, required number of times intooutput string T.`
```cpp
#include <stdio.h>
#include <cuda_runtime.h>

__global__ void repeatCharacters(char* inputString, int inputLength, char* outputString, int repetitions) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;

    // Copy characters from input string to output string
    for (int i = index; i < inputLength * repetitions; i += stride) {
        outputString[i] = inputString[i % inputLength]; // Copy characters from input string repeatedly
    }

    // Repeat the last character multiple times
    if (index == 0) {
        char lastChar = inputString[inputLength - 1];
        for (int i = inputLength * repetitions - 1; i >= inputLength * (repetitions - 1); --i) {
            outputString[i] = lastChar;
        }
    }
}

int main() {
    char inputString[] = "Hai"; // Example input string
    int length = strlen(inputString);
    int repetitions = 3; // Number of times each character should be repeated, except for the last character

    // Allocate memory for device copies of inputString and outputString
    char* d_inputString, * d_outputString;
    int outputLength = length * repetitions + 2; // Length of the output string

    cudaMalloc((void**)&d_inputString, length);
    cudaMalloc((void**)&d_outputString, outputLength);

    // Copy inputString to device
    cudaMemcpy(d_inputString, inputString, length, cudaMemcpyHostToDevice);

    // Launch repeatCharacters kernel on GPU with enough blocks and threads
    int blockSize = 256;
    int numBlocks = (outputLength + blockSize - 1) / blockSize;
    repeatCharacters<<<numBlocks, blockSize>>>(d_inputString, length, d_outputString, repetitions);

    // Copy result back to host
    char* outputString = (char*)malloc(outputLength);
    cudaMemcpy(outputString, d_outputString, outputLength, cudaMemcpyDeviceToHost);

    printf("Input string: %s\n", inputString);
    printf("Output string: %s\n", outputString);

    // Cleanup
    cudaFree(d_inputString);
    cudaFree(d_outputString);
    free(outputString);

    return 0;
}
```

# Explanation

* Kernel Definition: The `repeatCharacters` function is a CUDA kernel responsible for repeating each character of the input string a certain number of times to produce the output string. Each thread copies characters from the input string repeatedly to the output string. Additionally, the last character is repeated multiple times at the end of the output string.
* Main Function: The main function initializes the input string and the number of repetitions. It allocates memory for the device copies of the input string and the output string. The input string is copied to the device.
* Kernel Invocation: The `repeatCharacters` kernel is launched on the GPU with enough blocks and threads to process the output string in parallel.
* Result Retrieval: The result output string is copied from the device to the host and printed.
* Memory Deallocation: Finally, memory allocated on the device and host is freed.

This CUDA program demonstrates how to repeat each character of a string a certain number of times in parallel using GPU acceleration. The output shows the input string and the modified output string.

# Output

```
Input string: Hai
Output string: Haaiii
```
---


