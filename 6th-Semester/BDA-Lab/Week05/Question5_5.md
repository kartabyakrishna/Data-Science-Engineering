
# 5.Create a dataset having student details such as (name, subject, score), from this dataset group students by subject using the groupBy transformation. 

## Step 1: Create the Text File
**use the `nano` text editor to create a new file named `student_details.txt`:**
```bash
nano student_details.txt
```
## Step 2: Enter student details
**copy the following student details in the format: name,subject,score into the editor:**

```
Kk_utk,Math,85
Utkarsh,Science,90
Suzen,Science,80
Kartabya,Math,95
```

## Step 3: Save and Exit
* To save the file, press Ctrl+O, then press **Enter** to confirm the filename.
* To exit nano, press Ctrl+X.

## Step 4: Saving the Scala Code
**use the `nano` text editor to create a new file named `Q5.scala`:**
```bash
nano Q5.scala
```

## Step 5: Enter the Scala Code: 
**Copy the Scala code into the editor. Below is the code snippet you will use:**
```
// Define a case class for Student
case class Student(name: String, subject: String, score: Int)

// Load the text file containing student details
val studentDetails = spark.read.textFile("student_details.txt")

// Convert each line into a Student object
val students = studentDetails.map(line => {
  val parts = line.split(",")
  Student(parts(0), parts(1), parts(2).toInt)
})

// Convert RDD to DataFrame
import spark.implicits._
val studentDF = students.toDF()

// Group students by subject
val groupedStudents = studentDF.groupBy("subject")

// Show the resulting groups
groupedStudents.count().show()

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
:load Q5.scala
```

# OUTPUT

```
scala> :load Q5.scala
Loading Q5.scala...
studentDetails: org.apache.spark.sql.Dataset[String] = [value: string]
students: org.apache.spark.sql.Dataset[Student] = [name: string, subject: string, score: int]
studentDF: org.apache.spark.sql.DataFrame = [name: string, subject: string, score: int]
groupedStudents: org.apache.spark.sql.RelationalGroupedDataset = RelationalGroupedDataset: [grouping expressions: [subject: string], value: [name: string, subject: string, score: int], type: GroupBy]
+--------+-----+
|subject |count|
+--------+-----+
|Math    |  2  |
|Science |  2  |
+--------+-----+

```
