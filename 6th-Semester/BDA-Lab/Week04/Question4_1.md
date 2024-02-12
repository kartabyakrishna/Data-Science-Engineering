# Not Finall !

# Week 4A -  Pig Execution

## A. Run the program locally and test it on Hadoop using a normal text file:

1. **Create an input.txt file:**
   ```plaintext
   hi how are you
   i am good
   hope you doing good too
   how about you.
   i am in manipal
   studying Btech in Data science.
   ```

2. **Transfer to HDFS:**
   ```bash
   hdfs dfs -put /home/hdoop/input.txt bda1/
   ```

3. **Create Pig script file (e.g., pigscript.pig):**
   ```pig
   record = LOAD '/bda1/input.txt/';
   STORE record INTO '/bda1/out';
   ```

4. **Run Pig script in MapReduce mode:**
   ```bash
   pig -x mapreduce pigscript.pig
   ```

5. **Check the status of execution:**
   ```bash
   hdfs dfs -ls /bda1/out
   ```

6. **View the output file:**
   ```bash
   hdfs dfs -cat /bda1/out/part-m-00000
   ```

## B. Write a Pig program to count the number of word occurrences using Python in different modes (local mode, MapReduce mode):

Create an input file (input_word_count.txt):
   ```plaintext
   hello world
   hello pig
   world pig
   ```

Transfer to HDFS:
   ```bash
   hdfs dfs -put /home/hdoop/input_word_count.txt bda1/
   ```

Create a Pig script (word_count.pig):
   ```pig
   -- Load data
   data = LOAD '/bda1/input_word_count.txt' AS (line:CHARARRAY);

   -- Tokenize words
   words = FOREACH data GENERATE FLATTEN(TOKENIZE(line)) AS word;

   -- Group by word and count occurrences
   word_count = GROUP words BY word;
   word_count_result = FOREACH word_count GENERATE group AS word, COUNT(words) AS count;

   -- Store result
   STORE word_count_result INTO '/bda1/word_count_out';
   ```

Run the Pig script in MapReduce mode:
   ```bash
   pig -x mapreduce word_count.pig
   ```

Run the Pig script in Local mode:
   ```bash
   pig -x local word_count.pig
   ```

## C. Execute the Pig script to find the most popular movie in the dataset:

Download input files:
   ```bash
   wget https://raw.githubusercontent.com/ashaypatil11/hadoop/main/movies.item
   wget https://raw.githubusercontent.com/ashaypatil11/hadoop/main/ratings.data
   ```

Transfer to HDFS:
   ```bash
   hdfs dfs -put movies.item bda1/
   hdfs dfs -put ratings.data bda1/
   ```

Create a Pig script (most_popular_movie.pig):
   ```pig
   -- Load ratings data
   ratings = LOAD 'ratings.data' USING PigStorage('\t') AS (userID:INT, movieID:INT, rating:DOUBLE, timestamp:INT);

   -- Group ratings by movieID and calculate average rating
   avg_ratings = GROUP ratings BY movieID;
   avg_rating_result = FOREACH avg_ratings GENERATE group AS movieID, AVG(ratings.rating) AS avg_rating;

   -- Load movie data
   movies = LOAD 'movies.item' USING PigStorage('|') AS (movieID:INT, title:CHARARRAY, release_date:CHARARRAY, video_release_date:CHARARRAY, IMDb_URL:CHARARRAY, unknown:INT, Action:INT, Adventure:INT, Animation:INT, Childrens:INT, Comedy:INT, Crime:INT, Documentary:INT, Drama:INT, Fantasy:INT, Film_Noir:INT, Horror:INT, Musical:INT, Mystery:INT, Romance:INT, Sci_Fi:INT, Thriller:INT, War:INT, Western:INT);

   -- Join average ratings with movie data
   joined_data = JOIN avg_rating_result BY movieID, movies BY movieID;

   -- Order by average rating in descending order
   ordered_data = ORDER joined_data BY avg_rating_result::avg_rating DESC;

   -- Get the most popular movie
   most_popular_movie = LIMIT ordered_data 1;

   -- Display the result
   DUMP most_popular_movie;
   ```

Run the Pig script in MapReduce mode:
   ```bash
   pig -x mapreduce most_popular_movie.pig
   ```
