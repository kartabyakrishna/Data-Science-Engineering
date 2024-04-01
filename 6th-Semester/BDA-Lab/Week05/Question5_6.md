# 6.From the employee dataset, collect the first 5 records as an array using the collect action. 
## Codes by :- [Suzen Malik Firasta](https://github.com/SuzenFirasta)

## Step 1: To write the Scala Code
**use the `nano` text editor to create a new file named `Q6.scala`:**
```bash
nano Q6.scala
```

## Step 2: Enter the Scala Code: 
**Copy the Scala code into the editor. Below is the code snippet you will use:**
```
// Define a case class for Employee
case class Employee(RegNo: Int, EmpName: String, Age: Int, Salary: Int)

// Load the text file containing employee details
val employeeDetails = spark.read.textFile("employee_records.txt")

// Convert each line into an Employee object
val employees = employeeDetails.map(line => {
  val parts = line.split("\\s+")
  Employee(parts(0).toInt, parts(1), parts(2).toInt, parts(3).toInt)
})

// Convert RDD to DataFrame
import spark.implicits._
val employeeDF = employees.toDF()

// Collect the first 5 records as an array
val firstFiveRecords = employeeDF.take(5)

// Print the first 5 records
firstFiveRecords.foreach(println)

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
:load Q6.scala
```

# OUTPUT

```
scala> :load Q6.scala
Loading Q6.scala...
employeeDetails: org.apache.spark.sql.Dataset[String] = [value: string]
employees: org.apache.spark.sql.Dataset[Employee] = [RegNo: int, EmpName: string, Age: int, Salary: int]
employeeDF: org.apache.spark.sql.DataFrame = [RegNo: int, EmpName: string, Age: int, Salary: int]
firstFiveRecords: Array[Array[String]] = Array(
  Array(24, John, 26, 30000),
  Array(34, Jack, 40, 80000),
  Array(61, Joshi, 25, 35000),
  Array(45, Jash, 35, 75000),
  Array(34, Yash, 40, 60000)
)
```
**This is the alternative way to check the output:**

```
scala> firstFiveRecords.foreach(record => println(record.mkString(" ")))
```

**This will print:**
```
24 John 26 30000
34 Jack 40 80000
61 Joshi 25 35000
45 Jash 35 75000
34 Yash 40 60000
```
