# CUDA Setup Guide

## Prerequisites

Before setting up CUDA on your system, make sure you have the following prerequisites:

1. **Visual Studio for C++ Desktop Development:**
   - Ensure that you have Visual Studio installed for C++ desktop development.
   - For installation steps, refer to [this guide](https://github.com/kartabyakrishna/Data-Science-Engineering/blob/main/6th-Semester/PP-Lab/Week06/MPI-Setup.md).

2. **NVIDIA GPU:**
   - You need an NVIDIA GPU for CUDA development.

### Step 1: Download and Install CUDA

1. Download the CUDA toolkit from the official website: [CUDA Toolkit](https://developer.nvidia.com/cuda-downloads).
![Cuda_download](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/cuda-Install/cuda-downlaod.png)
2. Follow the prompted installation steps as follows : 
![Cuda_install](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/cuda-Install/CUDA-install.gif)
### Step 2: Configure CUDA Project

1. Once CUDA is installed, open **Visual Studio 2022**.

2. Create a new project:
   - Choose "Empty Project" template.
   - Specify a project name.

3. Right-click on "Source File" -> "Add Item" -> "New Item" -> Select "CUDA C/C++ File".

4. Right-click on the project -> "Build Dependencies" -> "Build Customizations".

5. Select project properties:
   - Go to Properties -> Linker -> Input -> Additional Dependencies.
   - Add `cudart_static.lib` to the list.

# OR
1. Open **Visual Studio 2022** .
2. Click on **Create a New Project** .
3. Choose **CUDA Runtime 12.3** by searching in the template search bar.
4. Click **Next** >> Click **Create** .
5. Run using **Step 4**.
#### ***Steps are shown below :***
![Cuda_ConfigureProject](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/cuda-Install/cuda%20-%20ProjectSetup.gif)

### Step 3: Sample CUDA Program

```cpp
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void add_arrays_gpu(int* a, int* b, int* c)
{
    c[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x];
}

int main()
{
    const auto count = 5;
    int host_a[] = { 1, 2, 3, 4, 5 };
    int host_b[] = { 10, 20, 30, 40, 60 };
    int host_c[count];
    int* device_a, * device_b, * device_c;
    const int size = count * sizeof(int);

    cudaMalloc(&device_a, size);
    cudaMalloc(&device_b, size);
    cudaMalloc(&device_c, size);

    cudaMemcpy(device_a, host_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(device_b, host_b, size, cudaMemcpyHostToDevice);

    add_arrays_gpu<<<1, count>>>(device_a, device_b, device_c);

    cudaMemcpy(host_c, device_c, size, cudaMemcpyDeviceToHost);

    for (auto i = 0; i < count; i++)
    {
        printf("%d ", host_c[i]);
    }

    getchar();
    return 0;
}
```
### Step 4: Run the CUDA Program

1. Once you've completed the configuration steps in "Step 3," you can run the CUDA program using the following simple method:

   - Click on the **Start Debugging** button (usually a green arrow or "Local Windows Debugger") in the toolbar.

   - Alternatively, press **F5** to build and run the CUDA program in debug mode.

   - The program output should appear in the console window, displaying the results of the CUDA computation.

Congratulations! You've successfully set up and run a CUDA program using Visual Studio. If you encounter any issues, make sure to check the configuration and dependencies.
