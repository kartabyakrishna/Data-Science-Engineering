# Week 5

**Q1. Create the dataset of your choice and perform word count program using spark tool.**

1. **Create an input.txt file:**
   ```plaintext
   hi how are you
   i am good
   hope you doing good too
   how about you.
   i am in manipal
   studying Btech in Data science.
   ```

2. **Create the spark script**
   ```
   sudo gedit Q1.scala
   ```
3. **Write the following code inside the Q1.scala spark script**
   ```
   // Load the text file
    val lines = spark.read.textFile("input.txt").rdd
   
    // Split the lines into words, count each word
    val words = lines.flatMap(_.split("\\s+"))
    val wordCounts = words.map(word => (word, 1)).reduceByKey(_ + _)
   
    // Show the word counts
    wordCounts.collect().foreach(println)
   ```
4. **Execute the prgram in Spark Shell**
   ```
   :load Q1.scala
   ```
5. **Output**
   ```
    scala> :load a.scala
    Loading Q1.scala...
    lines: org.apache.spark.rdd.RDD[String] = MapPartitionsRDD[1] at textFile at <console>:24
    words: org.apache.spark.rdd.RDD[String] = MapPartitionsRDD[2] at flatMap at <console>:26
    wordCounts: org.apache.spark.rdd.RDD[(String, Int)] = ShuffledRDD[3] at reduceByKey at <console>:28
    (hi,1)
    (how,2)
    (are,1)
    (you,3)
    (i,2)
    (am,2)
    (good,2)
    (hope,1)
    (doing,1)
    (too,1)
    (about,1)
    (in,1)
    (manipal,1)
    (studying,1)
    (Btech,1)
    (Data,1)
    (science.,1)
    ```
