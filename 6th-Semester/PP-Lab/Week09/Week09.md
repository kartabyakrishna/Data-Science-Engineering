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

