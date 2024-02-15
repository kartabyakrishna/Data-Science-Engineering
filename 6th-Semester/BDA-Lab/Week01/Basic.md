# HDFS Basic File Operations

## 1. File Upload:

```bash
hadoop fs -put <localsource> <hdfsdestination>
```

```bash
hdfs dfs -put <localsource> <hdfsdestination>
```

## 2. File Download:

```bash
hadoop fs -get <hdfssource> <localdestination>
```

```bash
hdfs dfs -get <hdfssource> <localdestination>
```

## 3. File Listing:

```bash
hadoop fs -ls <hdfslocation>
```

```bash
hdfs dfs -ls <hdfslocation>
```

## 4. File Deletion:

```bash
hadoop fs -rm <hdfsfile>
```

```bash
hdfs dfs -rm <hdfsfile>
```

## 5. File Moving/Renaming:

```bash
hadoop fs -mv <hdfsoldpath> <hdfsnewpath>
```

```bash
hdfs dfs -mv <hdfsoldpath> <hdfsnewpath>
```

## 6. File Copying:

```bash
hadoop fs -cp <hdfsfile> <hdfsdestination>
```

```bash
hdfs dfs -cp <hdfsfile> <hdfsdestination>
```

# Advanced File Operations:

## 7. Changing File Permissions:

```bash
hadoop fs -chmod <permissions> <hdfsfile>
```

```bash
hdfs dfs -chmod <permissions> <hdfsfile>
```

## 8. Changing File Ownership:

```bash
hadoop fs -chown <owner:group> <hdfsfile>
```

```bash
hdfs dfs -chown <owner:group> <hdfsfile>
```

## 9. File Block Size Alteration:

```bash
hadoop fs -Ddfs.block.size=<blocksize> -put <localsource> <hdfsdestination>
```

```bash
hdfs dfs -Ddfs.block.size=<blocksize> -put <localsource> <hdfsdestination>
```

## 10. Appending to Files (Hadoop 3.x and above):

```bash
hdfs dfs -appendToFile <localsource> <hdfsfile>
```

```bash
hdfs dfs -appendToFile <localsource> <hdfsfile>
```

## 11. Checksum Calculation:

```bash
hadoop fs -checksum <hdfsfile>
```

```bash
hdfs dfs -checksum <hdfsfile>
```

## 12. File Concatenation:

```bash
hadoop fs -concat <src1> <src2> <dst>
```

```bash
hdfs dfs -concat <src1> <src2> <dst>
```

# Extended File Operations:

## File Compression/Decompression:

```bash
hadoop fs -gzip <hdfsfile>
```

```bash
hadoop fs -gunzip <hdfsfile>
```

## File Checksum Comparison:

```bash
hadoop fs -compareChecksum <hdfsfile1> <hdfsfile2>
```

```bash
hadoop fs -diff <hdfsfile1> <hdfsfile2>
```

## File Content Summary:

```bash
hadoop fs -du -s -h <hdfslocation>
```

```bash
hadoop fs -count -q -h <hdfslocation>
```

## File Block Location Information:

```bash
hadoop fsck <hdfsfile> -files -blocks -locations
```

## File Replication Factor Modification:

```bash
hadoop fs -setrep -R <replicationfactor> <hdfslocation>
```

```bash
hadoop fs -setrep -w <replicationfactor> <hdfslocation>
```

## File Snapshot Creation and Management:

```bash
hadoop fs -createSnapshot <hdfslocation> <snapshotname>
```

```bash
hadoop fs -deleteSnapshot <hdfslocation> <snapshotname>
```

```bash
hadoop fs -renameSnapshot <hdfslocation> <oldsnapshotname> <newsnapshotname>
```

## File Encryption/Decryption (when encryption is enabled):

```bash
hadoop key create <keyname>
```

```bash
hadoop fs -encrypt -keyName <keyname> <hdfsfile>
```

```bash
hadoop fs -decrypt <hdfsfile>
```
#-----------------------
# Interacting with HDFS using the command line interface to understand the basic working structure of Hadoop cluster.

## List contents of a directory:

## Change current working directory:

## View the current working directory:
#-----------------------

## File Operations:

### Copy files/directories from the local file system to HDFS:

### Copy files/directories from HDFS to the local file system:

### Remove files/directories from HDFS:

### Rename files/directories in HDFS:

# File System Information:

## Get file information such as replication, block size, owner, etc.:

## Check disk usage of files/directories:

## Check the integrity of the file system:
#-----------------------

# Admin Operations:

## Change the replication factor of a file:

## View and modify HDFS quotas:

## Check cluster health and status:
#-----------------------

# Additional File Operations:

## 1. Appending to Files (Hadoop 3.x and above):

### Append content to a file in HDFS:

```bash
hdfs dfs -appendToFile <local-source> <hdfs-destination>
```

## 2. Concatenating Files:

### Concatenate multiple files into a single file in HDFS:

```bash
hdfs dfs -getmerge <hdfs-source> <local-destination>
```

## 3. File Content Summary:

### Get a summary of directory sizes and their contents:

```bash
hdfs dfs -du [-h] <path>
```

## 4. File Block Manipulation:

### Get information about blocks in a file:

```bash
hdfs fsck <hdfs-file> -files -blocks -locations
```

### Force an immediate block replication of a file:

```bash
hdfs dfs -setrep -R <replication-factor> <hdfs-file>
```

## 5. File Checksum Operations:

### Calculate the checksum of a file in HDFS:

```bash
hdfs dfs -checksum <hdfs-file>
```

### Compare checksums of two files:

```bash
hdfs dfs -compareChecksum <hdfs-file1> <hdfs-file2>
```

## 6. File Encryption/Decryption (when encryption is enabled):

### Create a new key for encryption:

```bash
hdfs crypto -createZone -keyName <key-name> -path <path>
```

### Encrypt a file:

```bash
hdfs crypto -encrypt -keyName <key-name> <hdfs-file>
```

### Decrypt a file:

```bash
hdfs crypto -decrypt <hdfs-file>
```
