# 7_A. Consider the dataset given in Question B. Perform the following operations. sortByKey(),  groupByKey(), countBykey() 
## Codes by :- [Suzen Malik Firasta](https://github.com/SuzenFirasta)

## Step 1: To write the Scala Code
**use the `nano` text editor to create a new file named `Q7_A.scala`:**
```bash
nano Q7_A.scala
```

## Step 2: Enter the Scala Code: 
**Copy the Scala code into the editor. Below is the code snippet you will use:**
```
// Load the data
val data = spark.read.textFile("employee_records.txt")

// Convert the data to a Dataset[(Int, String, Int, Int)]
val employees = data.map(line => {
  val parts = line.split(" ")
  (parts(0).toInt, parts(1), parts(2).toInt, parts(3).toInt)
})

// Perform sortByKey
val sortedEmployees = employees.sort("_1")

// Perform groupByKey
val groupedEmployees = employees.groupByKey(_._1)

// Perform countByKey
val countByKeys = employees.rdd.map(_._1).countByValue()

// Print the results
println("Sorted by Key:")
sortedEmployees.show()

println("Grouped by Key:")
groupedEmployees.count().show()

println("Count by Key:")
countByKeys.foreach(println)


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
data: org.apache.spark.sql.Dataset[String] = [value: string]
employees: org.apache.spark.sql.Dataset[(Int, String, Int, Int)] = [_1: int, _2: string ... 2 more fields]
sortedEmployees: org.apache.spark.sql.Dataset[(Int, String, Int, Int)] = [_1: int, _2: string ... 2 more fields]
groupedEmployees: org.apache.spark.sql.KeyValueGroupedDataset[Int,(Int, String, Int, Int)] = KeyValueGroupedDataset: [key: [value: int], value: [_1: int, _2: string ... 2 more field(s)]]
countByKeys: scala.collection.Map[Int,Long] = Map(10 -> 1, 42 -> 1, 24 -> 2, 61 -> 1, 21 -> 2, 34 -> 2, 45 -> 2, 67 -> 2, 62 -> 1)
Sorted by Key:
+---+------+---+-----+
| _1|    _2| _3|   _4|
+---+------+---+-----+
| 10|ronald| 57|65000|
| 21| cassy| 51|40000|
| 21| cassy| 51|40000|
| 24|  John| 26|30000|
| 24|  John| 26|30000|
| 34|  Jack| 40|80000|
| 34|  Yash| 40|60000|
| 42|  Lion| 42|56000|
| 45|  Jash| 35|75000|
| 45|  Jash| 35|75000|
| 61| Joshi| 25|35000|
| 62|  kate| 50|76000|
| 67| Smith| 20|24000|
| 67| Smith| 20|24000|
+---+------+---+-----+

Grouped by Key:
+---+--------+
|key|count(1)|
+---+--------+
| 34|       2|
| 61|       1|
| 10|       1|
| 45|       2|
| 24|       2|
| 62|       1|
| 21|       2|
| 42|       1|
| 67|       2|
+---+--------+

Count by Key:
(10,1)
(42,1)
(24,2)
(61,1)
(21,2)
(34,2)
(45,2)
(67,2)
(62,1)


```
