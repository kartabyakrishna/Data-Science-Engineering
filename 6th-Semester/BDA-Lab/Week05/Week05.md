# Not Final !!!
## Week - 05 : Spark
### Task 1: Create a dataset and perform Word Count

```scala
// Start Spark Shell
$ spark-shell

// Create a dataset and perform Word Count
val dataset = List("Spark is powerful", "Spark is fast", "Word count with Spark")
val textRDD = sc.parallelize(dataset)

val wordCount = textRDD
  .flatMap(line => line.split(" "))
  .map(word => (word, 1))
  .reduceByKey(_ + _)
  .collect()

wordCount.foreach(println)

// Stop Spark Shell
:q
```

### Task 2: Map Transformation on Employee Records

```scala
// Start Spark Shell
$ spark-shell

// Create RDD from the employee dataset and apply map transformation
val employeeData = List(
  (24, "John", 26, 30000),
  (34, "Jack", 40, 80000),
  (61, "Joshi", 25, 35000),
  (45, "Jash", 35, 75000),
  (34, "Yash", 40, 60000),
  (67, "Smith", 20, 24000),
  (42, "Lion", 42, 56000),
  (62, "Kate", 50, 76000),
  (21, "Cassy", 51, 40000),
  (10, "Ronald", 57, 65000),
  (24, "John", 26, 30000),
  (67, "Smith", 20, 24000),
  (45, "Jash", 35, 75000),
  (21, "Cassy", 51, 40000)
)

val employeeRDD = sc.parallelize(employeeData)

val transformedRDD = employeeRDD.map(record => (record._1, record._2, record._3 * 2, record._4))
transformedRDD.collect()

// Stop Spark Shell
:q
```

### Task 3: Filter Transformation on Employee Records

```scala
val filteredRDD = employeeRDD.filter(record => record._4 > 50000)
filteredRDD.collect()
```

### Task 4: Create a text file and use flatMap transformation

```scala
val textData = List("Spark is powerful", "FlatMap transformation in Spark", "Processing text data")
val textRDD = sc.parallelize(textData)

val flatMapResult = textRDD.flatMap(line => line.split(" "))
flatMapResult.collect()
```

### Task 5: GroupBy Transformation on Student Dataset

```scala
val studentData = List(("Alice", "Math", 90), ("Bob", "Math", 85), ("Alice", "Physics", 88), ...)
val studentRDD = sc.parallelize(studentData)

val groupedBySubject = studentRDD.groupBy(record => record._2)
groupedBySubject.collect()
```

### Task 6: Collect the first 5 records as an array

```scala
val firstFiveRecords = employeeRDD.take(5)
```

### Task 7: RDD Creation and Operations

```scala
// Parallelized collection
val arrayRDD = sc.parallelize(Array(1, 2, 3, 4, 5))

// Existing RDD and finding sum
val sum = arrayRDD.reduce(_ + _)

// RDD from external sources
val externalRDD = sc.textFile("hdfs://your-hdfs-path/external/data.txt")

// DataFrame Creation for Employee Data
import org.apache.spark.sql.{SparkSession, Row}
import org.apache.spark.sql.types._

val spark = SparkSession.builder.appName("EmployeeData").getOrCreate()

val schema = StructType(Seq(
  StructField("RegNo", IntegerType, nullable = false),
  StructField("EmpName", StringType, nullable = false),
  StructField("Age", IntegerType, nullable = false),
  StructField("Salary", IntegerType, nullable = false)
))

val employeeDF = spark.createDataFrame(
  employeeRDD.map(record => Row(record._1, record._2, record._3, record._4)),
  schema
)

employeeDF.show()
```

For Task 7.A:

```scala
// Sort by key
val sortedRDD = externalRDD.map(line => (line.split(",")(0).toInt, line))
  .sortByKey()
  .collect()

// Group by key
val groupedByKey = externalRDD.map(line => (line.split(",")(0), line))
  .groupByKey()
  .collect()

// Count by key
val countByKey = externalRDD.map(line => (line.split(",")(0), 1))
  .countByKey()
```
