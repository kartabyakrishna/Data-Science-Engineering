## Q) Write a MapReduce program in Python using Hadoop Distributed File System (HDFS) to calculate the average of all numeric values in an input.txt file. The program should filter out non-numeric data. The input file is stored in HDFS, and the output should display the computed average. Ensure that the solution is implemented using the MapReduce paradigm.
#### input.txt
`Note : This isn't the actual input which was given in the exam.`
```plaintext
The price of the product is 45.50 .
John has 3 apples and 2 oranges.
-10.5 is the temperature in Celsius.
The stock gained 2.75 yesterday.
The value of pi is approximately 3.14159 .
Alice spent 20.75 on lunch.
My current balance is -5.09 .
```
#### mapper.py
```pyhton
#!/usr/bin/env python

import sys

for line in sys.stdin:
    # Split the line into words
    words = line.strip().split()

    # Iterate through words and emit (key, value) pairs for numeric values
    for word in words:
        try:
            value = float(word)
            print("numeric", value)
        except ValueError:
            pass  # Ignore non-numeric values

```
#### reducer.py
```python
#!/usr/bin/env python

import sys

total_sum = 0
count = 0

for line in sys.stdin:
    # Split the line into words
    words = line.strip().split()

    if len(words) == 2:
        key, value = words
        if key == "numeric":
            total_sum += float(value)
            count += 1

# Calculate the average
average = total_sum / count if count > 0 else 0

print("Average:", average)

```