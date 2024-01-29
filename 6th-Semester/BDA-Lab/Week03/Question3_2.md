# Q2. Consider the following sample text file to compute the the average, minimum and maximum recorded temperature by year wise using concept of Map Reduce.

## Input Data

Create a file named `input3_2.txt` and paste the following content:

```plaintext
2014 44
2013 42
2012 30
2013 44
2010 45
2014 38
2011 42
2010 44
```

## Creating Input File

To create the input file, open a terminal and run the following command:

```bash
sudo gedit input3_2.txt
```

Paste the above content into the text editor and save the file.

## Mapper

Create a file named `mapper3_2.py` and paste the following Python code:

```python
#!/usr/bin/env python

import sys

for line in sys.stdin:
    year, temperature = line.strip().split()
    print(f'{year}\t{temperature}')
```

### Mapper Explanation

The Mapper reads input lines, extracts year and temperature information, and outputs key-value pairs in the format `year   temperature`. This format is necessary for grouping temperatures by year during the MapReduce process.

## Reducer

Create a file named `reducer3_2.py` and paste the following Python code:

```python
#!/usr/bin/env python

import sys

current_year = None
total_temperature = 0
count = 0
min_temperature = float('inf')
max_temperature = float('-inf')

for line in sys.stdin:
    key, value = line.strip().split('\t')
    year = key
    temperature = int(value)

    if current_year is None:
        current_year = year

    if current_year == year:
        total_temperature += temperature
        count += 1
        min_temperature = min(min_temperature, temperature)
        max_temperature = max(max_temperature, temperature)
    else:
        average_temperature = total_temperature / count
        print(f'{current_year}\t{average_temperature}\t{min_temperature}\t{max_temperature}')

        # Reset variables for the new year
        current_year = year
        total_temperature = temperature
        count = 1
        min_temperature = temperature
        max_temperature = temperature

# Print the last year's result
if current_year:
    average_temperature = total_temperature / count
    print(f'{current_year}\t{average_temperature}\t{min_temperature}\t{max_temperature}')

```

### Reducer Explanation

The Reducer processes the key-value pairs emitted by the Mapper. It accumulates the total temperature, counts the number of records, and tracks the minimum and maximum temperatures for each year. The output is in the format `year   average_temperature   min_temperature   max_temperature`.

## Testing

To check if the Mapper and Reducer are working, use the following commands :

```bash
cat input3_2.txt | python3 mapper3_2.py
cat input3_2.txt | python3 mapper3_2.py | sort | python3 reducer3_2.py
```
## Output
This should output the average, minimum, and maximum recorded temperatures by year.
```
2010    44.5    44      45
2011    42.0    42      42
2012    30.0    30      30
2013    43.0    42      44
2014    41.0    38      44
```
