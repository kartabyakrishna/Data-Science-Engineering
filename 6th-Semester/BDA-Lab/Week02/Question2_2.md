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
            # Multiply corresponding elements and accumulate the sum
            result = sum(val_a * val_b for (matrix_a, val_a), (matrix_b, val_b) in current_values)
            print(f'{current_key}\t{result}')
        current_key = key
        current_values = [(matrix, val)]

# Print the last key's result
if current_key:
    result = sum(val_a * val_b for (matrix_a, val_a), (matrix_b, val_b) in current_values)
    print(f'{current_key}\t{result}')

```

### Reducer Explanation

The Reducer processes the key-value pairs emitted by the Mapper. It accumulates the values based on their positions and matrix, performing matrix addition and subtraction. The output is in the format `(row,col)   result`.

## Testing

To check if the Mapper and Reducer are working, use the following commands:

```bash
cat input2_2.txt | python3 mapper2_2.py
cat input2_2.txt | python3 mapper2_2.py | sort | python3 reducer2_2.py
```
## Output

This should output the result of matrix operations using MapReduce.
```
hdoop@hadoop-client:~$ cat input.txt |python3 mapper2.py
0,0	a,10
0,1	a,20
0,2	a,30
1,0	a,40
1,1	a,50
1,2	a,60
2,0	a,70
2,1	a,80
2,2	a,90
0,0	b,1
0,1	b,2
0,2	b,3
1,0	b,4
1,1	b,5
1,2	b,6
2,0	b,7
2,1	b,8
2,2	b,9
```
```
hdoop@hadoop-client:~$ cat input.txt | python3 mapper2.py | sort | python3 reducer2.py
0,0	300
0,1	360
0,2	420
1,0	660
1,1	810
1,2	960
2,0	1020
2,1	1260
2,2	1500
```
