
# Setting up MPI with Visual Studio 2022

## 1. Download and Install Visual Studio 2022

Download the latest [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/) Community version, as it is free. Follow the installation process.

## 2. Choose the “Desktop development with C++” workload

During installation, choose the "Desktop development with C++" workload. This can be found in the installation options.

![Desktop Development with C++](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/mpi-setup/Desktop%20Development.gif)

## 3. Download MS-MPI

Download MS-MPI SDK and Redist installers (msmpisetup.exe and msmpisdk.msi) and install them.
You can get them [here](https://www.microsoft.com/en-us/download/details.aspx?id=105289)

![msmpi Download](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/mpi-setup/msmpi%20Download.png)

Verify the installation by running the command `set MSMPI` in the command prompt. The output should be as shown below:

![Verify Installation](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/mpi-setup/verfyInstall.png)

## 4. Create a new project

Open Visual Studio 2022 and create a new Empty Project (Console App). Name it as desired.

## 5. Add a C++ Source File

Click on the project name in the solution explorer and add a new C++ Source File (Project -> Add New Item -> C++ File).

## 6. Use the following MPI code

```cpp
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Get the rank of the process
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    // Print the message
    printf("Hello World! My rank is %d\n", my_rank);
    // Finalize the MPI environment.
    MPI_Finalize();
}
```

## 7. Configure MPI for the project

- Open the “Property Pages” (Project -> Properties).
- Add the following in the **C/C++ >> General >> Additional Include Directories** area:
  - For x64: `$(MSMPI_INC);$(MSMPI_INC)\x64`
  - For x86: `$(MSMPI_INC);$(MSMPI_INC)\x86`

Apply the changes.

## 8. Set up the linker library

Add `msmpi.lib` to the **Linker >> Input >> Additional Dependencies** . Remember to add a semicolon after `msmpi.lib`.

## 9. Additional Library Directories

Add the following to the **Linker >> General >> Additional Library Directories** :
- For x64: `$(MSMPI_LIB64)`
- For x86: `$(MSMPI_LIB32)`

## 10. Build the solution

Build the solution (Build -> Build Solution).
![Build Solution](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/mpi-setup/build%20Soln.png)

## 11. Test the program

To test or execute the program, go to the Debug directory and execute the following commands:

```bash
mpiexec –n <number_of_processing_elements> ./<executable_file>
```
![Build Soln]([link_to_pic3](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/mpi-setup/output%20using%20mpiexec.png))

Replace `<number_of_processing_elements>` and `<executable_file>` accordingly.

Congratulations! The setup is complete. You can further analyze the code in another article.
