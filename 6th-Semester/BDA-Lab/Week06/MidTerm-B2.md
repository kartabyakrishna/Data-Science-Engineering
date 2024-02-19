### HDFS Commands (0.5W + 1E)x3 + (1W + 2E)x1
To copy all local files from a local folder to an HDFS (Hadoop Distributed File System) folder, you can use the hdfs dfs command. The syntax is as follows:
```bash
hdfs dfs -copyFromLocal <local-source> <hdfs-destination>
# EX
hdfs dfs -copyFromLocal /path/to/local/folder/* /user/your_username/hdfs_folder

```
To move a directory in HDFS from one location to another, you can use the hdfs dfs -mv command. Here's an example of how you can move the directory called "olddata" to the new location "/bda244/archive":
```bash
hdfs dfs -mv /path/to/olddata /bda244/archive
```
To delete all files and a folder in HDFS, you can use the hdfs dfs -rm and hdfs dfs -rmdir commands. Here's how you can do it:
```bash
# Delete all files in the folder
hdfs dfs -rm -r /path/to/folder/*

# Delete the empty folder
hdfs dfs -rmdir /path/to/folder
```
To merge several files in a folder located at /user/kartaya/small_files/directory in HDFS into a single file named merged_txt.txt, you can use the hadoop fs -getmerge command. Here's an example:
```bash
hadoop fs -getmerge /user/kartabya/small_files/directory merged_txt.txt
```
This command retrieves all files from the specified HDFS directory and merges them into a single local file named merged_txt.txt. The merged file will be created in the local file system where you run the command.

Make sure to have enough local storage space for the merged file, and be aware that this operation pulls the data from HDFS to the local file system. If the data is very large, consider doing the merge operation on the Hadoop cluster itself to avoid unnecessary data transfer.

After running the command, you can then copy the merged file back to HDFS if needed:
```bash
hadoop fs -copyFromLocal merged_txt.txt /user/kartabya/small_files/
```

### Q) Write a MapReduce program in Python using Hadoop Distributed File System (HDFS) to calculate the average of all numeric values in an input.txt file. The program should filter out non-numeric data. The input file is stored in HDFS, and the output should display the computed average. Ensure that the solution is implemented using the MapReduce paradigm. (3W + 10E)
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
```python
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