# 4. Create a text file that will have few sentences, use flatMap transformation to split each sentence into words. 
## Codes by :- [Suzen Malik Firasta](https://github.com/SuzenFirasta)


## Step 1: Create the Text File
**use the `nano` text editor to create a new file named `input.txt`:**
```bash
nano input.txt
```
## Step 2: Enter a sentence
**copy the following sentence into the editor:**

```
This is the first sentence. Here is another one. And the final sentence.
```
## Step 3: Save and Exit
* To save the file, press Ctrl+O, then press **Enter** to confirm the filename.
* To exit nano, press Ctrl+X.

## Step 4: Saving the Scala Code
**use the `nano` text editor to create a new file named `Q4.scala`:**
```bash
nano Q4.scala
```

## Step 5: Enter the Scala Code: 
**Copy the Scala code into the editor. Below is the code snippet you will use:**
```
// Load the text file containing sentences
val sentences = spark.read.textFile("input4.txt")

// Split each sentence into words using flatMap transformation
val words = sentences.flatMap(_.split("\\s+"))

// Show the resulting words
words.show()
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
:load Q4.scala
```

# OUTPUT

```
scala> :load Q4.scala
Loading Q4.scala...
sentences: org.apache.spark.sql.Dataset[String] = [value: string]
words: org.apache.spark.sql.Dataset[String] = [value: string]
+-----+
|value|
+-----+
|This |
|is   |
|the  |
|first|
|sentence.|
|Here |
|is   |
|another|
|one. |
|And  |
|the  |
|final|
|sentence.|
+-----+
```
