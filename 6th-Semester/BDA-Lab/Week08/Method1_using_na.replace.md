
# Week 8: Consider a Spark datafraome as shown below, Need to replace a string in column Card type from Checking->Cash using PySpark and Spark with scala 
# Method 2: using na.replace
## Codes by :- [Suzen Malik Firasta](https://github.com/SuzenFirasta)

## Step 1: Create the Text File
**use the `nano` text editor to create a new file named `input.txt`:**
```bash
nano input.txt
```
## Step 2: Enter student details
**copy the following details in the below given format into the editor:**

```
Customer_NO,Card_type,Date,Category,Transaction Type,Amount
1000210,Platinum Card,3/17/2018,Fast Food,Debit,23.34
1000210,Silver Card,3/19/2018,Restaurants,Debit,36.48
1000210,Checking,3/19/2018,Utilities,Debit,35
1000210,Platinum Card,3/20/2018,Shopping,Debit,14.97
1000210,Silver Card,3/22/2018,Gas & Fuel,Debit,30.55
1000210,Platinum Card,3/23/2018,Credit Card Payment,Debit,559.91
1000210,Checking,3/23/2018,Credit Card Payment,Debit,559.91

```

## Step 3: Save and Exit
* To save the file, press Ctrl+O, then press **Enter** to confirm the filename.
* To exit nano, press Ctrl+X.

## Step 4: Saving the Scala Code
**use the `nano` text editor to create a new file named `Q8_A.scala`:**
```bash
nano Q8_B.scala
```

## Step 5: Enter the Scala Code: 
**Copy the Scala code into the editor. Below is the code snippet you will use:**
```
import org.apache.spark.sql.{SparkSession, DataFrame}
import org.apache.spark.sql.functions.col

object Q8 extends App {

  val spark = SparkSession.builder
    .appName("CardType Replacement")
    .getOrCreate()

  import spark.implicits._

  // Read the data from the input text file
  val df: DataFrame = spark.read
    .option("header", "true")
    .option("inferSchema", "true")
    .csv("input.txt")

  // Show the initial DataFrame
  println("Initial DataFrame:")
  df.show()

  // Replace "Checking" with "Cash" in the Card_type column using na.replace
  val updatedDf = df.na.replace("Card_type", Map("Checking" -> "Cash"))

  // Show the updated DataFrame
  println("Updated DataFrame:")
  updatedDf.show()

  spark.stop()
}

Q8.main(Array())


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
:load Q8_B.scala
```

# OUTPUT

```
scala> :load Q8_B.scala
Loading Q8_B.scala...
import org.apache.spark.sql.{SparkSession, DataFrame}
import org.apache.spark.sql.functions.col
defined object Q8
24/04/01 15:57:42 WARN SparkSession: Using an existing Spark session; only runtime SQL configurations will take effect.
Initial DataFrame:
+-----------+-------------+---------+-------------------+----------------+------+
|Customer_NO|    Card_type|     Date|           Category|Transaction Type|Amount|
+-----------+-------------+---------+-------------------+----------------+------+
|    1000210|Platinum Card|3/17/2018|          Fast Food|           Debit| 23.34|
|    1000210|  Silver Card|3/19/2018|        Restaurants|           Debit| 36.48|
|    1000210|     Checking|3/19/2018|          Utilities|           Debit|  35.0|
|    1000210|Platinum Card|3/20/2018|           Shopping|           Debit| 14.97|
|    1000210|  Silver Card|3/22/2018|         Gas & Fuel|           Debit| 30.55|
|    1000210|Platinum Card|3/23/2018|Credit Card Payment|           Debit|559.91|
|    1000210|     Checking|3/23/2018|Credit Card Payment|           Debit|559.91|
+-----------+-------------+---------+-------------------+----------------+------+

Updated DataFrame:
+-----------+-------------+---------+-------------------+----------------+------+
|Customer_NO|    Card_type|     Date|           Category|Transaction Type|Amount|
+-----------+-------------+---------+-------------------+----------------+------+
|    1000210|Platinum Card|3/17/2018|          Fast Food|           Debit| 23.34|
|    1000210|  Silver Card|3/19/2018|        Restaurants|           Debit| 36.48|
|    1000210|         Cash|3/19/2018|          Utilities|           Debit|  35.0|
|    1000210|Platinum Card|3/20/2018|           Shopping|           Debit| 14.97|
|    1000210|  Silver Card|3/22/2018|         Gas & Fuel|           Debit| 30.55|
|    1000210|Platinum Card|3/23/2018|Credit Card Payment|           Debit|559.91|
|    1000210|         Cash|3/23/2018|Credit Card Payment|           Debit|559.91|
+-----------+-------------+---------+-------------------+----------------+------+

```
