# PIG TOOL: Pig Latin

## 1. Objective
Learn the execution modes and running Pig programs locally and on Hadoop.

## 2. Resources
- VMWare stack (Hadoop)
- __ GB RAM
- Web browser
- Hard Disk __ GB

## 3. Program Logic
Focus on data transformations with Apache Pig for tasks like Wordcount and finding the most popular movie.

### Execution Modes:
- **MapReduce Mode (Default):**
  - Command: `pig –x mapreduce`

- **Local Mode:**
  - Command: `pig –x local`

### Running Modes:
- **Interactive Mode:**
  - Grunt shell: `grunt>`

- **Batch Mode:**
  - Create Pig script with `.pig` extension.

### Execution Steps:
1. Write Pig statements in a file (e.g., `wordcount.pig`).
2. Execute script in local or MapReduce mode.

### Execution in MapReduce Mode:
```bash
pig -x mapreduce wordcount.pig
```

## Sample Pig Program (Wordcount):

### Pig Script (`wordcount.pig`):
```pig
-- Load input text file
record = LOAD '/bda1/input.txt' USING PigStorage() AS (line:chararray);

-- Tokenize each line using Python UDF
tokenized = FOREACH record GENERATE FLATTEN(TOKENIZE_PYTHON(line)) AS word;

-- Group and count word occurrences
word_count = FOREACH (GROUP tokenized BY word) GENERATE group AS word, COUNT(tokenized) AS count;

-- Store the result
STORE word_count INTO '/bda1/wordcount_output';

-- Python UDF for tokenization
DEFINE TOKENIZE_PYTHON org.apache.pig.scripting.jython.JythonFunction 'tokenize.py' SHIP ('/path/to/tokenize.py') CACHE;
```

### Python Script (`tokenize.py`):
```python
# tokenize.py

@outputSchema("word:chararray")
def tokenize(line):
    words = line.split()
    return [word.lower() for word in words]
```

### Execution Steps:
1. Upload input file to HDFS: `hdfs dfs -put /home/hdoop/input.txt bda1/`
2. Run Pig script: `pig -x mapreduce wordcount.pig`
3. Check output: `hdfs dfs -cat /bda1/wordcount_output/part-m-00000`

## 4A: Pig Execution
### A. Running Modes
Consider a normal text file for learning Pig running modes and execution modes. Run the program locally and test it on Hadoop.

### B. Pig Program for Word Occurrences
Write a Pig program to count word occurrences using Python in different modes (local mode, MapReduce mode).

### C. Find Most Popular Movie
Execute a Pig script to find the most popular movie in the dataset using `ratings.data` and `movies.item`.

#### Steps and Code:
```bash
# Download dataset
wget https://raw.githubusercontent.com/ashaypatil11/hadoop/main/movies.item
wget https://raw.githubusercontent.com/ashaypatil11/hadoop/main/ratings.data

# Pig script to find most popular movie
# (code not provided, as it requires understanding dataset and specific logic)
```

Feel free to adapt the Pig script for wordcount to Python as needed for your specific use case.
```

Replace `'/path/to/tokenize.py'` with the actual path to your Python script for tokenization.
