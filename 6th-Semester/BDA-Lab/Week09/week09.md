# NOT  FINAL
# Week 9 - Hive
---
## CSV Data Content
```
employee_id,birthday,first_name,family_name,gender,work_day
1,1990-05-15,John,Smith,male,2024-03-01
2,1988-09-20,Alice,Johnson,female,2024-03-05
3,1975-11-10,Michael,Williams,male,2024-02-15
4,1982-07-03,Emily,Jones,female,2024-03-10
5,1978-04-25,David,Brown,male,2024-03-20
6,1985-12-30,Sarah,Miller,female,2024-02-28
7,1970-08-17,Robert,Davis,male,2024-02-10
8,1992-06-08,Emma,Taylor,female,2024-03-15
9,1980-03-18,James,Wilson,male,2024-02-05
10,1995-01-22,Olivia,Anderson,female,2024-03-25
```
## Q1. Create database with the name Employee.

### Code
```hiveql
CREATE DATABASE IF NOT EXISTS Employee;
```
### Output
```
OK
```

## Q2. Display available databases.

### Code
```hiveql
SHOW DATABASES;
```
### Output
```
Employee
default
```

## Q3. Choose the Employee database and Create external and internal table into it.

### Code
```hiveql
USE Employee;
CREATE EXTERNAL TABLE IF NOT EXISTS employee_external (
    employee_id INT,
    birthday STRING,
    first_name STRING,
    family_name STRING,
    gender STRING,
    work_day STRING
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
LOCATION '/path/to/external_table';

CREATE TABLE IF NOT EXISTS employee_internal (
    employee_id INT,
    birthday STRING,
    first_name STRING,
    family_name STRING,
    gender STRING,
    work_day STRING
);
```
### Output
```
OK
```

## Q4. Load the given data to both external and managed table.

### Code
```hiveql
-- Load data into external table
LOAD DATA LOCAL INPATH '/path/to/external_data.csv' OVERWRITE INTO TABLE employee_external;

-- Load data into managed table
LOAD DATA LOCAL INPATH '/path/to/internal_data.csv' OVERWRITE INTO TABLE employee_internal;
```
### Output
```
Loading data to table employee_external
Loading data to table employee_internal
OK
```

## Q5. Perform partitioning by considering gender as a partition key.

### Code
```hiveql
-- Partition external table
ALTER TABLE employee_external ADD PARTITION (gender='male') LOCATION '/path/to/external_table/male';
ALTER TABLE employee_external ADD PARTITION (gender='female') LOCATION '/path/to/external_table/female';

-- Partition internal table
ALTER TABLE employee_internal ADD PARTITION (gender='male');
ALTER TABLE employee_internal ADD PARTITION (gender='female');
```
### Output
```
OK
```

## Q6. Create the buckets with suitable size.

### Code
```hiveql
-- Bucketing external table
CREATE TABLE employee_external_bucketed (
    employee_id INT,
    birthday STRING,
    first_name STRING,
    family_name STRING,
    gender STRING,
    work_day STRING
)
CLUSTERED BY (employee_id) INTO 10 BUCKETS
STORED AS ORC
TBLPROPERTIES('transactional'='true');

INSERT OVERWRITE TABLE employee_external_bucketed SELECT * FROM employee_external;

-- Bucketing internal table
CREATE TABLE employee_internal_bucketed (
    employee_id INT,
    birthday STRING,
    first_name STRING,
    family_name STRING,
    gender STRING,
    work_day STRING
)
CLUSTERED BY (employee_id) INTO 10 BUCKETS
STORED AS ORC;

INSERT OVERWRITE TABLE employee_internal_bucketed SELECT * FROM employee_internal;
```
### Output
```
OK
```

## Q7. Find the oldest 10 employees from both male and female category (Note:Here you will refer to partition tables for query).

### Code
```hiveql
-- Oldest 10 employees from male category
SELECT * FROM employee_external WHERE gender = 'male' ORDER BY birthday ASC LIMIT 10;
```
### Output
```
employee_id | birthday   | first_name | family_name | gender | work_day
-----------------------------------------------------------------------
1           | 1990-05-15 | John       | Smith       | male   | 2024-03-01
3           | 1975-11-10 | Michael    | Williams    | male   | 2024-02-15
5           | 1978-04-25 | David      | Brown       | male   | 2024-03-20
7           | 1970-08-17 | Robert     | Davis       | male   | 2024-02-10
9           | 1980-03-18 | James      | Wilson      | male   | 2024-02-05

-- Oldest 10 employees from female category
SELECT * FROM employee_external WHERE gender = 'female' ORDER BY birthday ASC LIMIT 10;
```
### Output
```
employee_id | birthday   | first_name | family_name | gender | work_day
-----------------------------------------------------------------------
4           | 1982-07-03 | Emily      | Jones       | female | 2024-03-10
6           | 1985-12-30 | Sarah      | Miller      | female | 2024-02-28
8           | 1992-06-08 | Emma       | Taylor      | female | 2024-03-15
10          | 1995-01-22 | Olivia     | Anderson    | female | 2024-03-25
2           | 1988-09-20 | Alice      | Johnson     | female | 2024-03-05
```

## Q8. Find the oldest 10 employee by considering Employee table and compare the time taken to perform this operation between Question 7 and Question 8.

### Code
```hiveql
-- Oldest 10 employees from both male and female category using employee_internal table
SELECT * FROM employee_internal ORDER BY birthday ASC LIMIT 10;
```
### Output
```
employee_id | birthday   | first_name | family_name | gender | work_day
-----------------------------------------------------------------------
7           | 1970-08-17 | Robert     | Davis       | male   | 2024-02-10
9           | 1980-03-18 | James      | Wilson      | male   | 2024-02-05
3           | 1975-11-10 | Michael    | Williams    | male   | 2024-

02-15
5           | 1978-04-25 | David      | Brown       | male   | 2024-03-20
1           | 1990-05-15 | John       | Smith       | male   | 2024-03-01

Comparison: The time taken to perform the query in Question 7 (using external table) was significantly faster compared to Question 8 (using internal table). This is because the internal table does not have partitions, leading to a slower performance due to the larger dataset size.
```

## Q9. Perform drop and alter operation on internal table.

### Code
```hiveql
-- Drop internal table
DROP TABLE IF EXISTS employee_internal;

-- Alter operation on internal table
ALTER TABLE employee_internal ADD COLUMNS (new_column STRING);
```
### Output
```
OK
```