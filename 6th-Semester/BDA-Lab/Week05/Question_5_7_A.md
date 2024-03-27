# 7_A. Consider the dataset given in Question B. Perform the following operations. sortByKey(),  groupByKey(), countBykey() 

## Step 1: To write the Scala Code
**use the `nano` text editor to create a new file named `Q7_A.scala`:**
```bash
nano Q7_A.scala
```

## Step 2: Enter the Scala Code: 
**Copy the Scala code into the editor. Below is the code snippet you will use:**
```
// Read the text file containing employee records
val lines = spark.read.textFile("employee_records.txt")

// Split the lines into individual fields (Reg.No, EmpName, Age, Salary)
val records = lines.map(_.split("\\s+"))

// Convert records to key-value pairs (Reg.No as key, entire record as value)
val keyValuePairs = records.map(record => (record(0), record.mkString(" ")))

// sortByKey()
val sortedRecords = keyValuePairs.sortByKey()

// groupByKey()
val groupedRecords = keyValuePairs.groupByKey()

// countByKey()
val countsByKey = keyValuePairs.countByKey()

// Show the sorted records
println("Sorted Records:")
sortedRecords.collect().foreach(println)

// Show the grouped records
println("\nGrouped Records:")
groupedRecords.collect().foreach{case (key, values) => println(s"Key: $key, Values: ${values.mkString(", ")}")}

// Show the counts by key
println("\nCounts by Key:")
countsByKey.foreach{case (key, count) => println(s"Key: $key, Count: $count")}

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
:load Q7_A.scala
```

# OUTPUT

```
scala> :load Q7_A.scala
Loading Q7_A.scala...
lines: org.apache.spark.sql.Dataset[String] = [value: string]
records: org.apache.spark.rdd.RDD[Array[String]] = MapPartitionsRDD[1] at map at Q7_A.scala:5
keyValuePairs: org.apache.spark.rdd.RDD[(String, String)] = MapPartitionsRDD[2] at map at Q7_A.scala:9
sortedRecords: org.apache.spark.rdd.RDD[(String, String)] = ShuffledRDD[3] at sortByKey at Q7_A.scala:12
groupedRecords: org.apache.spark.rdd.RDD[(String, Iterable[String])] = ShuffledRDD[4] at groupByKey at Q7_A.scala:15
countsByKey: scala.collection.Map[String,Long] = Map(42 -> 1, 21 -> 2, 34 -> 2, 10 -> 1, 24 -> 2, 45 -> 2, 62 -> 1, 61 -> 1, 67 -> 2)

scala> println("Sorted Records:")
Sorted Records:
(10, 10 ronald 57 65000)
(21, 21 cassy 51 40000)
(21, 21 cassy 51 40000)
(24, 24 John 26 30000)
(24, 24 John 26 30000)
(34, 34 Jack 40 80000)
(34, 34 Yash 40 60000)
(42, 42 Lion 42 56000)
(45, 45 Jash 35 75000)
(45, 45 Jash 35 75000)
(61, 61 Joshi 25 35000)
(62, 62 kate 50 76000)
(67, 67 Smith 20 24000)
(67, 67 Smith 20 24000)

scala> println("\nGrouped Records:")
Grouped Records:
Key: 10, Values: 10 ronald 57 65000
Key: 21, Values: 21 cassy 51 40000, 21 cassy 51 40000
Key: 24, Values: 24 John 26 30000, 24 John 26 30000
Key: 34, Values: 34 Jack 40 80000, 34 Yash 40 60000
Key: 42, Values: 42 Lion 42 56000
Key: 45, Values: 45 Jash 35 75000, 45 Jash 35 75000
Key: 61, Values: 61 Joshi 25 35000
Key: 62, Values: 62 kate 50 76000
Key: 67, Values: 67 Smith 20 24000, 67 Smith 20 24000

scala> println("\nCounts by Key:")
Counts by Key:
Key: 42, Count: 1
Key: 21, Count: 2
Key: 34, Count: 2
Key: 10, Count: 1
Key: 24, Count: 2
Key: 45, Count: 2
Key: 62, Count: 1
Key: 61, Count: 1
Key: 67, Count: 2

```
