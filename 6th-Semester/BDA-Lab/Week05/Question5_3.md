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
import spark.implicits._

// Define a case class to represent the Employee
case class Employee(regNo: Int, empName: String, age: Int, salary: Int)

// Load the dataset from a text file
val employeeData = spark.read.textFile("employees.txt")

// Convert each line into an Employee object
val employees = employeeData.map { line =>
 val parts = line.split("\\s+")
 Employee(parts(0).toInt, parts(1), parts(2).toInt, parts(3).toInt)
}

// Filter employees whose salary is greater than 50000
val highSalaryEmployees = employees.filter(_.salary > 50000)

// Show the result
highSalaryEmployees.show()

// Optionally, save the result to a text file
highSalaryEmployees.write.csv("high_salary_employees.csv")
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
scala> :load Q5_3.scala
Loading Q5_3.scala...
import spark.implicits._
defined class Employee
employeeData: org.apache.spark.sql.Dataset[String] = [value: string]
employees: org.apache.spark.sql.Dataset[Employee] = [regNo: int, empName: string ... 2 more fields]
highSalaryEmployees: org.apache.spark.sql.Dataset[Employee] = [regNo: int, empName: string ... 2 more fields]
+-----+-------+---+------+
|regNo|empName|age|salary|
+-----+-------+---+------+
|   34|   Jack| 40| 80000|
|   45|   Jash| 35| 75000|
|   34|   Yash| 40| 60000|
|   42|   Lion| 42| 56000|
|   62|   kate| 50| 76000|
|   10| ronald| 57| 65000|
|   45|   Jash| 35| 75000|
+-----+-------+---+------+

```
