# 2. Given a dataset of employee records containing (name, age, salary), use map transformation to transform each record into a tuple of (name, age * 2, salary)?
## Codes by :- [Suzen Malik Firasta](https://github.com/SuzenFirasta)

## Step 1: Create the Text File
**use the `nano` text editor to create a new file named `employee_records.txt`:**
```bash
nano employee_records.txt
```
## Step 2: Enter the Employee Data
**copy the following employee data into the editor. Ensure each record is on a new line:**

```
24 John 26 30000
34 Jack 40 80000
61 Joshi 25 35000
45 Jash 35 75000
34 Yash 40 60000
67 Smith 20 24000
42 Lion 42 56000
62 kate 50 76000
21 cassy 51 40000
10 ronald 57 65000
24 John 26 30000
67 Smith 20 24000
45 Jash 35 75000
21 cassy 51 40000
```
## Step 3: Save and Exit
* To save the file, press Ctrl+O, then press **Enter** to confirm the filename.
* To exit nano, press Ctrl+X.

## Step 4: Saving the Scala Code
**use the `nano` text editor to create a new file named `Q2.scala`:**
```bash
nano Q2.scala
```

## Step 5: Enter the Scala Code: 
**Copy the Scala code into the editor. Below is the code snippet you will use:**
```
import spark.implicits._

// Load the dataset from a text file
val employeeData = spark.read.textFile("employees.txt")

// Define a case class to represent the Employee
case class Employee(regNo: Int, empName: String, age: Int, salary: Int)

// Convert each line into an Employee object
val employees = employeeData.map { line =>
 val parts = line.split("\\s+")
 Employee(parts(0).toInt, parts(1), parts(2).toInt, parts(3).toInt)
}

// Transform each Employee into a tuple of (name, age * 2, salary)
val result = employees.map(emp => (emp.empName, emp.age * 2, emp.salary))

// Show the result
result.show()

// Optionally, save the result to a text file
result.write.text("transformed_employees.txt")
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
:load Q2.scala
```

# OUTPUT

```
scala> :load Q2.scala
Loading Q2.scala...
lines: org.apache.spark.sql.Dataset[String] = [value: string]
records: org.apache.spark.rdd.RDD[Array[String]] = MapPartitionsRDD[...] at map at <console>:...
transformedRecords: org.apache.spark.rdd.RDD[(String, Int, Int)] = MapPartitionsRDD[...] at map at <console>:...
+------+----+------+
|  Name| Age|Salary|
+------+----+------+
|  John|  52| 30000|
|  Jack|  80| 80000|
| Joshi|  50| 35000|
|  Jash|  70| 75000|
|  Yash|  80| 60000|
| Smith|  40| 24000|
|  Lion|  84| 56000|
|  kate| 100| 76000|
| cassy| 102| 40000|
|ronald| 114| 65000|
|  John|  52| 30000|
| Smith|  40| 24000|
|  Jash|  70| 75000|
| cassy| 102| 40000|
+------+----+------+
```
