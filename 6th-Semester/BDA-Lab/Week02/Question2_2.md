# Matrix Operations using MapReduce

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
## Testing

To check if the Mapper and Reducer are working, use the following commands:

```bash
cat input2_2.txt | python3 mapper2_2.py
cat input2_2.txt | python3 mapper2_2.py | sort | python3 reducer2_2.py
```

## Output

This should output the result of matrix operations using MapReduce.
```

```
