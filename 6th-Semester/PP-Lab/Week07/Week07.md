# 1. Write a MPI program using synchronous send. The sender process sends a word to the receiver. The second process receives the word, toggles each letter of the word and sends it back to the first process. Both processes use synchronous send operations.

```cpp
```
## Output
```plaintext
```
---
# 2. Write a MPI program where the master process (process 0) sends a number to each of the slaves and the slave processes receive the number and prints it. Use standard send.

```cpp
```
## Output
```plaintext
```
---
# 3. Write a MPI program to read N elements of the array in the root process (process 0) where N is equal to the total number of process. The root process sends one value to each of the slaves. Let even ranked process finds square of the received element and odd ranked process finds cube of received element. Use Buffered send.

```cpp
```
## Output
```plaintext
```
---
# 4. Write a MPI program to read an integer value in the root process. Root process sends this value to Process1, Process1 sends this value to Process2 and so on. Last process sends the value back to root process. When sending the value each process will first increment the received value by one. Write the program using point to point communication routines. 

```cpp
```
## Output
```plaintext
```
---
# 5. Write a MPI program to read N elements of an array in the master process. Let N processes including master process check the array values are prime or not.

```cpp
```
## Output
```plaintext
```
---