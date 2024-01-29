# Q2. Perform Matrix operations using MapReduce by considering 3 * 3 matrix and perform following operations:
- i. Matrix addition and subtraction
- ii. Matrix Multiplication
- iii. Matrix transpose

## Setup

1. Open VM Player.
2. Open master.
3. Open client.
4. Start the Hadoop cluster with `start-all.sh`.

## Input Data

Create a file named `input2_2.txt` and paste the following content:

```plaintext
a,0,0,10
a,0,1,20
a,0,2,30
a,1,0,40
a,1,1,50
a,1,2,60
a,2,0,70
a,2,1,80
a,2,2,90
b,0,0,1
b,0,1,2
b,0,2,3
b,1,0,4
b,1,1,5
b,1,2,6
b,2,0,7
b,2,1,8
b,2,2,9
```
# Method 1
## Mapper
```python
#!/usr/bin/python3
import sys

#cache_info = open("cache.txt").readLines()[0].split(",")
row_a, col_b = 3,3

for line in sys.stdin:
        matrix_index, row, col, value = line.rstrip().split(",")
        if matrix_index == "a":
                        key = row + "," + col
                        print ("%s\t%s\t%s"%(matrix_index,key,value))

        else:
                        key = row + "," + col
                        print ("%s\t%s\t%s"%(matrix_index,key,value))

```
## Reducer
```pyhton
#!/usr/bin/python3

import sys

a = {}
b = {}
for line in sys.stdin:
    line = line.strip()
    key, pos, value = line.split('\t')
    p = pos.split(',')
    if key == 'a':
        a[(int(p[0]), int(p[1]))] = int(value)
    elif key == 'b':
        b[(int(p[0]), int(p[1]))] = int(value)

add = {}
sub = {}
mul = {}
result = 0

print("Addition of two matrices is :")
for i in range(0, 3):
    for j in range(0, 3):
        add[(i, j)] = a[(i, j)] + b[(i, j)]
        print("{0}  ".format(add[(i, j)]), end="")
    print()

print("\nSubtraction :")
for i in range(0, 3):
    for j in range(0, 3):
        sub[(i, j)] = a[(i, j)] - b[(i, j)]
        print("{0}  ".format(sub[(i, j)]), end="")
    print()

print("\nMultiplication :")
for i in range(0, 3):
    for j in range(0, 3):
        for k in range(0, 3):
            result = result + a[(i, k)] * b[(k, j)]
        mul[(i, j)] = result
        result = 0
        print("{0}  ".format(mul[(i, j)]), end="")
    print()

print("\nTranspose of the product matrix :")
for i in range(0, 3):
    for j in range(0, 3):
        print("{0}  ".format(mul[(j, i)]), end="")
    print()
```
## Output
```plaintext
Addition of two matrices is :
11  22  33
44  55  66
77  88  99

Subtraction :
9  18  27
36  45  54
63  72  81

Multiplication :
300  360  420
660  810  960
1020  1260  1500

Transpose of the product matrix :
300  660  1020
360  810  1260
420  960  1500
```
# Method 2
# Addition
## Mapper

Create a file named `mapper2_2.py` and paste the following Python code:

```python
#!/usr/bin/env python

import sys

for line in sys.stdin:
    matrix, row, col, value = line.strip().split(',')
    print(f'{row},{col}\t{matrix},{value}')
```

### Mapper Explanation

The Mapper reads input lines, extracts matrix elements along with their positions, and outputs key-value pairs in the format `(row,col)   matrix,value`. This format is essential for grouping values based on their positions during the MapReduce process.

## Reducer

Create a file named `reducer2_2.py` and paste the following Python code:

```python
#!/usr/bin/env python

import sys

current_key = None
current_values = []

for line in sys.stdin:
    key, value = line.strip().split('\t')
    row, col = key.split(',')
    matrix, val = value.split(',')
    val = int(val)

    if current_key == key:
        current_values.append((matrix, val))
    else:
        if current_key:
            # Add corresponding elements for matrix addition
            add_result = sum(val_a for (_, val_a) in current_values if matrix == 'a') + \
                         sum(val_b for (_, val_b) in current_values if matrix == 'b')
            
            print(f'{current_key}\t{add_result}')
        current_key = key
        current_values = [(matrix, val)]

# Print the last key's result
if current_key:
    add_result = sum(val_a for (_, val_a) in current_values if matrix == 'a') + \
                 sum(val_b for (_, val_b) in current_values if matrix == 'b')
    
    print(f'{current_key}\t{add_result}')

```

### Reducer Explanation

The Reducer processes the key-value pairs emitted by the Mapper. It accumulates the values based on their positions and matrix, performing matrix addition and subtraction. The output is in the format `(row,col)   result`.

## Output

This should output the result of matrix operations using MapReduce.
```

```
# Subtraction
## Mapper

```python
#!/usr/bin/env python

import sys

for line in sys.stdin:
    matrix, row, col, value = line.strip().split(',')
    print(f'{row},{col}\t{matrix},{value}')

```
## Reducer

```python
#!/usr/bin/env python

import sys

current_key = None
values_dict = {} 

for line in sys.stdin:

  key, value = line.strip().split('\t')

  row, col = key.split(',')

  matrix, val = value.split(',')

  val = int(val)

  if current_key != key:

    if current_key:

      a_val = values_dict['a'][current_key]
      b_val = values_dict['b'][current_key]
      
      print(f'{current_key}\t{a_val - b_val}')

    current_key = key  
    values_dict = {}

  if matrix not in values_dict:
    values_dict[matrix] = {}
  
  values_dict[matrix][current_key] = val

# Print last key
if current_key:

  a_val = values_dict['a'][current_key]
  b_val = values_dict['b'][current_key]

  print(f'{current_key}\t{a_val - b_val}')
```

## Output

This should output the result of matrix operations using MapReduce.
```

```
# Transpose
## Mapper
```python
#!/usr/bin/env python
import sys

# Mapper function for matrix transpose
for line in sys.stdin:
    # Split the input line into words
    words = line.strip().split(',')

    # Extract matrix information
    matrix_name = words[0]
    row = int(words[1])
    col = int(words[2])
    value = int(words[3])

    # Output key-value pair for each element in the matrix
    # Key: (matrix_name, col), Value: (row, value)
    print(f'{matrix_name},{col}\t{row},{value}')

```
## Reducer
```python
#!/usr/bin/env python
import sys

# Reducer function for matrix transpose
current_key = None
values = []

for line in sys.stdin:
    # Split the input line into key and value
    key, value = line.strip().split('\t')
    matrix_name, col = key.split(',')
    row, element_value = value.split(',')

    # Check if the key has changed
    if current_key is None:
        current_key = key
        values.append((row, element_value))
    elif current_key == key:
        values.append((row, element_value))
    else:
        # Output the transposed matrix element
        for val in values:
            print(f'{matrix_name},{val[0]},{col}\t{val[1]}')
        
        # Reset values for the new key
        current_key = key
        values = [(row, element_value)]

# Output the last transposed matrix element
for val in values:
    print(f'{matrix_name},{val[0]},{col}\t{val[1]}')

```

## Output

This should output the result of matrix operations using MapReduce.
```
a,0,1   10
a,1,1   40
a,2,1   70
a,0,2   20
a,1,2   50
a,2,2   80
b,0,0   30
b,1,0   60
b,2,0   90
b,0,1   1
b,1,1   4
b,2,1   7
b,0,2   2
b,1,2   5
b,2,2   8
b,0,2   3
b,1,2   6
b,2,2   9
```
## Testing

To check if the Mapper and Reducer are working, use the following commands:

```bash
cat input2_2.txt | python3 mapper2_2.py
cat input2_2.txt | python3 mapper2_2.py | sort | python3 reducer2_2.py
```

