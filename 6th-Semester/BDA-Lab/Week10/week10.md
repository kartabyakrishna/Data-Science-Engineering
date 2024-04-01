# Week 10 - HBase
credit : 🐐Aakash Gangurde🐐 
## Q1. Create hbase table as per the given data.

### Code
```hbase
create 'emp','rowid','personal_data','professional_data'
```
### Output
```
Created table emp
Took 1.0852 seconds
```

## Q2. Describe the table after inserting all rows of data into it.

### Code
```hbase
put 'emp', '1', 'personal_data:name', 'Angela'; put 'emp', '1', 'personal_data:city', 'chicago'; put 'emp', '1', 'personal_data:age', '31'; put 'emp', '1', 'professional_data:designation', 'Architect'; put 'emp', '1', 'professional_data:salary', '70000'
put 'emp', '2', 'personal_data:name', 'dwayne'; put 'emp', '2', 'personal_data:city', 'bostan'; put 'emp', '2', 'personal_data:age', '35'; put 'emp', '2', 'professional_data:designation', 'Web devloper'; put 'emp', '2', 'professional_data:salary', '65000'
put 'emp', '3', 'personal_data:name', 'david'; put 'emp', '3', 'personal_data:city', 'seattle'; put 'emp', '3', 'personal_data:age', '29'; put 'emp', '3', 'professional_data:designation', 'Engineer'; put 'emp', '3', 'professional_data:salary', '55000'
put 'emp', '4', 'personal_data:name', 'rahul'; put 'emp', '4', 'personal_data:city', 'USA'; put 'emp', '4', 'personal_data:age', '31'; put 'emp', '4', 'professional_data:designation', 'architect'; put 'emp', '4', 'professional_data:salary', '70000'
put 'emp', '5', 'personal_data:name', 'jony'; put 'emp', '5', 'personal_data:city', 'chicago'; put 'emp', '5', 'personal_data:age', '29'; put 'emp', '5', 'professional_data:designation', 'Data analyst'; put 'emp', '5', 'professional_data:salary', '80000'
put 'emp', '6', 'personal_data:name', 'sony'; put 'emp', '6', 'personal_data:city', 'bostan'; put 'emp', '6', 'personal_data:age', '29'; put 'emp', '6', 'professional_data:designation', 'Data analyst'; put 'emp', '6', 'professional_data:salary', '80000'
```

## Q3. Update the salary of an empid 3 from 55000 to 65000 and describe the table to show updates.

### Code
```hbase
put 'emp','3','professional_data:salary','65000'
```
### Output
```
No specific output
```

## Q4. Retrieve employees details whose salary is greater than or equals to 70000.

### Code
```hbase
scan 'emp', {FILTER => "ValueFilter(>=, 'binary:70000')"}
```
### Output
```
ROW                                                   COLUMN+CELL
 1                                                    column=personal_data:city, timestamp=2024-04-01T13:39:41.824, value=chicago
 1                                                    column=personal_data:name, timestamp=2024-04-01T13:39:41.819, value=Angela
 1                                                    column=professional_data:designation, timestamp=2024-04-01T13:39:41.831, value=Architect
 1                                                    column=professional_data:salary, timestamp=2024-04-01T13:39:41.835, value=70000
 2                                                    column=personal_data:city, timestamp=2024-04-01T13:39:41.864, value=bostan
 2                                                    column=personal_data:name, timestamp=2024-04-01T13:39:41.859, value=dwayne
 2                                                    column=professional_data:designation, timestamp=2024-04-01T13:39:41.871, value=Web devloper
 4                                                    column=personal_data:city, timestamp=2024-04-01T13:39:41.933, value=USA
 4                                                    column=personal_data:name, timestamp=2024-04-01T13:39:41.930, value=rahul
 4                                                    column=professional_data:designation, timestamp=2024-04-01T13:39:41.940, value=architect
 4                                                    column=professional_data:salary, timestamp=2024-04-01T13:39:41.943, value=70000
 5                                                    column=personal_data:city, timestamp=2024-04-01T13:39:41.968, value=chicago
 5                                                    column=personal_data:name, timestamp=2024-04-01T13:39:41.964, value=jony
 5                                                    column=professional_data:designation, timestamp=2024-04-01T13:39:41.974, value=Data analyst
 5                                                    column=professional_data:salary, timestamp=2024-04-01T13:39:41.977, value=80000
 6                                                    column=personal_data:city, timestamp=2024-04-01T13:39:41.999, value=bostan
 6                                                    column=personal_data:name, timestamp=2024-04-01T13:39:41.996, value=sony
 6                                                    column=professional_data:designation, timestamp=2024-04-01T13:39:42.005, value=Data analyst
 6                                                    column=professional_data:salary, timestamp=2024-04-01T13:39:42.009, value=80000
6 row(s)
Took 0.0760 seconds
```

## Q5. Read the personal data of an employee whose name is David.

### Code
```hbase
get 'emp','3',{COLUMN => 'personal_data'}
```
### Output
```
COLUMN                                                CELL
 personal_data:age                                    timestamp=2024-04-01T13:39:41.901, value=29
 personal_data:city                                   timestamp=2024-04-01T13:39:41.898, value=seattle
 personal_data:name                                   timestamp=2024-04-01T13:39:41.895, value=david
1 row(s)
Took 0.0045 seconds
```

## Q6. Describe the employee details whose designation is data analyst.

### Code
```hbase
scan 'emp', {FILTER => "SingleColumn

ValueFilter('professional_data', 'designation', =, 'binary:Data analyst')"}
```
### Output
```
ROW                                                   COLUMN+CELL
 5                                                    column=personal_data:age, timestamp=2024-04-01T13:39:41.971, value=29
 5                                                    column=personal_data:city, timestamp=2024-04-01T13:39:41.968, value=chicago
 5                                                    column=personal_data:name, timestamp=2024-04-01T13:39:41.964, value=jony
 5                                                    column=professional_data:designation, timestamp=2024-04-01T13:39:41.974, value=Data analyst
 5                                                    column=professional_data:salary, timestamp=2024-04-01T13:39:41.977, value=80000
 6                                                    column=personal_data:age, timestamp=2024-04-01T13:39:42.002, value=29
 6                                                    column=personal_data:city, timestamp=2024-04-01T13:39:41.999, value=bostan
 6                                                    column=personal_data:name, timestamp=2024-04-01T13:39:41.996, value=sony
 6                                                    column=professional_data:designation, timestamp=2024-04-01T13:39:42.005, value=Data analyst
 6                                                    column=professional_data:salary, timestamp=2024-04-01T13:39:42.009, value=80000
2 row(s)
Took 0.0099 seconds
```

## Q7. Count the number of rows and columns present in the created table.

### Code
```hbase
count 'emp';
```
### Output
```
6 row(s)
Took 0.0291 seconds
```

## Q8. Delete the age column from personal data.

### Code
```hbase
alter 'emp', {NAME => 'personal_data', METHOD => 'delete', COLUMN => 'age'}
```
### Output
```
Unknown argument ignored: COLUMN
Updating all regions with the new schema...
1/1 regions updated.
Done.
Took 1.8459 seconds
```