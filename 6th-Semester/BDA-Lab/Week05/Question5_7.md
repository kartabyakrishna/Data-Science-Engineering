# 7. Demonstrate the creation of RDD using Parallelized collection, existing RDD by finding the sum of all elements in an RDD1(which holds array elements). Also, create an RDD from external sources. 
## Codes by :- [Suzen Malik Firasta](https://github.com/SuzenFirasta)


## Step 1: To write the Scala Code
**use the `nano` text editor to create a new file named `Q7.scala`:**
```bash
nano Q7.scala
```

## Step 2: Enter the Scala Code: 
**Copy the Scala code into the editor. Below is the code snippet you will use:**
```
// Create an RDD using parallelized collection
val rdd1 = spark.sparkContext.parallelize(Array(1, 2, 3, 4, 5))

// Find the sum of all elements in the RDD
val sum = rdd1.reduce(_ + _)
println(s"Sum: $sum")

// Create an RDD from an external source (text file)
val rdd2 = spark.sparkContext.textFile("employee_records.txt")

// Print the first 5 lines of the RDD
rdd2.take(5).foreach(println)


```

## Step 3: Save and Exit
* To save the file, press Ctrl+O, then press **Enter** to confirm the filename.
* To exit nano, press Ctrl+X.

## Step 4: Launch the Spark Shell
**In your terminal, type the following command to open the Spark shell:**
```
spark-shell
```

## Step 5: To execute the Scala Code
**Once the Spark shell is ready, load your Scala script by typing**
```
:load Q7.scala
```

# OUTPUT

```
scala> :load Q7.scala
defined class Employee
rdd1: org.apache.spark.rdd.RDD[Int] = ParallelCollectionRDD[0] at parallelize at <console>:...
sum: Int = 15
Sum: 15
rdd2: org.apache.spark.rdd.RDD[String] = employee_records.txt MapPartitionsRDD[2] at textFile at <console>:...
24 John  26 30000
34 Jack  40  80000
61 Joshi  25 35000
45 Jash  35 75000
34 Yash  40  60000


```
