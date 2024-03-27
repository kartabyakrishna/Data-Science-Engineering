# 3.From the same employee dataset, filter out employees whose salary is greater than 50000 using the filter transformation. 
## Codes by :- [Suzen Malik Firasta](https://github.com/SuzenFirasta)

## Step 1: To write the Scala Code
**use the `nano` text editor to create a new file named `Q3.scala`:**
```bash
nano Q3.scala
```

## Step 2: Enter the Scala Code: 
**Copy the Scala code into the editor. Below is the code snippet you will use:**
```
// Load the text file containing employee records
val lines = spark.read.textFile("input2.txt")

// Split the lines into individual fields (name, age, salary)
val records = lines.map(_.split("\\s+"))

// Filter out employees whose salary is greater than 50000
val filteredRecords = records.filter(record => record(2).toInt > 50000)

// Show the filtered records
filteredRecords.show()
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
:load Q3.scala
```

# OUTPUT

```
scala> :load Q3.scala
Loading Q3.scala...
lines: org.apache.spark.sql.Dataset[String] = [value: string]
records: org.apache.spark.rdd.RDD[Array[String]] = MapPartitionsRDD[...] at map at <console>:...
filteredRecords: org.apache.spark.rdd.RDD[Array[String]] = MapPartitionsRDD[...] at filter at <console>:...

scala> filteredRecords.show()
+------+---+------+
|    _1| _2|    _3|
+------+---+------+
|  Jack| 40| 80000|
|  Jash| 35| 75000|
|  Yash| 40| 60000|
|  Lion| 42| 56000|
|  kate| 50| 76000|
|ronald| 57| 65000|
|  Jash| 35| 75000|
+------+---+------+

```
