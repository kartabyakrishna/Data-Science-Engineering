# 1. Create the dataset of your choice and perform word count program using spark tool.
## Codes by :- [Suzen Malik Firasta](https://github.com/SuzenFirasta)


## Step 1: Create the Text File
**use the `nano` text editor to create a new file named `input.txt`:**
```bash
nano input.txt
```
## Step 2: Enter the Employee Data
**copy the following text into the editor:**

 ```plaintext
   hi how are you
   i am good
   hope you doing good too
   how about you.
   i am in manipal
   studying Btech in Data science.
   ```
## Step 3: Save and Exit
* To save the file, press Ctrl+O, then press **Enter** to confirm the filename.
* To exit nano, press Ctrl+X.

## Step 4: Saving the Scala Code
**use the `nano` text editor to create a new file named `Q1.scala`:**
```bash
nano Q1.scala
```

## Step 5: Enter the Scala Code: 
**Copy the Scala code into the editor. Below is the code snippet you will use:**
```
   // Load the text file
    val lines = spark.read.textFile("input.txt").rdd
   
    // Split the lines into words, count each word
    val words = lines.flatMap(_.split("\\s+"))
    val wordCounts = words.map(word => (word, 1)).reduceByKey(_ + _)
   
    // Show the word counts
    wordCounts.collect().foreach(println)
```

## Step 6: Save and Exit
* To save the file, press Ctrl+O, then press **Enter** to confirm the filename.
* To exit nano, press Ctrl+X.

## Step 7: Launch the Spark Shell
**In your terminal, type the following command to open the Spark shell:**
```
spark-shell
```

## Step 8: To execute the Scala Code
**Once the Spark shell is ready, load your Scala script by typing**
```
:load Q1.scala
```

# OUTPUT

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
