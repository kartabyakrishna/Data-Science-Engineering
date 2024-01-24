# MapReduce Finding Unit-wise Salary

## Input Data

Create a file named `input3_1.txt` and paste the following content:

```plaintext
EmpNo,EmpName,Unit,Designation,Salary
1001,John,IMST,TA,30000
1002,Jack,CLOUD,PM,80000
1003,Joshi,FNPR,TA,35000
1004,Jash,ECSSAP,PM,75000
1005,Yash,FSADM,SPM,60000
1006,Smith,ICS,TA,24000
1007,Lion,IMST,SPM,56000
1008,Kate,FNPR,PM,76000
1009,Cassy,MFGADM,TA,40000
1010,Ronald,ECSSAP,SPM,65000
```

## Creating Input File

To create the input file, open a terminal and run the following command:

```bash
sudo gedit input3_1.txt
```

Paste the above content into the text editor and save the file.

## Mapper

Create a file named `mapper3_1.py` and paste the following Python code:

```python
#!/usr/bin/env python

import sys

# Input comes from standard input (stdin)
for line in sys.stdin:
    # Remove leading and trailing whitespaces
    line = line.strip()
    
    # Split the line into fields
    fields = line.split(',')
    
    # Check if the line has the expected number of fields
    if len(fields) == 5:
        # Extract relevant information
        emp_no, emp_name, unit, designation, salary = fields
        
        # Output the unit and salary as key-value pairs, separated by a tab
        print(f"{unit}\t{salary}")

```

### Mapper Explanation

The Mapper reads input lines, extracts unit and salary information, and outputs key-value pairs in the format `unit   salary`. This format is necessary for grouping salaries by unit during the MapReduce process.

## Reducer

Create a file named `reducer3_1.py` and paste the following Python code:

```python
#!/usr/bin/env python

import sys

current_unit = None
total_salary = 0

# Input comes from standard input (stdin)
for line in sys.stdin:
    # Remove leading and trailing whitespaces
    line = line.strip()

    # Skip the header line
    if line.startswith("EmpNo,EmpName,Unit,Designation,Salary"):
        continue
    
    # Split the line into key and value
    unit, salary = line.split('\t')
    
    try:
        # Convert salary to an integer
        salary = int(salary)
    except ValueError:
        # Skip lines where salary cannot be converted to an integer
        continue
    
    # Check if the current unit is the same as the previous line
    if current_unit == unit:
        # Add the salary to the total for the current unit
        total_salary += salary
    else:
        # Output the unit and total salary for the previous unit
        if current_unit is not None:
            print(f"{current_unit}\t{total_salary}")
        
        # Update the current unit and reset the total salary
        current_unit = unit
        total_salary = salary

# Output the unit and total salary for the last unit
if current_unit is not None:
    print(f"{current_unit}\t{total_salary}")

```

### Reducer Explanation

The Reducer processes the key-value pairs emitted by the Mapper. It accumulates the total salary for each unit. The output is in the format `unit   total_salary`.

## Testing

To check if the Mapper and Reducer are working, use the following commands:

```bash
cat input4.txt | python3 mapper4.py
cat input4.txt | python3 mapper4.py | sort | python3 reducer4.py
```
## Output
This should output the total salary for each unit.
```
CLOUD   80000
ECSSAP  140000
FNPR    111000
FSADM   60000
ICS     24000
IMST    86000
MFGADM  40000
```
