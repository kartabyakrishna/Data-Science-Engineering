1. **Create a Directory in HDFS:**
   ```bash
   hdfs dfs -mkdir /user/your_username/your_directory
   ```

2. **Create an Empty File:**
   ```bash
   hdfs dfs -touchz /user/your_username/your_directory/your_file
   ```

3. **Copy Files/Folders from Local File System to HDFS:**
   ```bash
   hdfs dfs -copyFromLocal your_local_path /user/your_username/your_directory/
   ```

4. **Print File Contents:**
   ```bash
   hdfs dfs -cat /user/your_username/your_directory/your_file
   ```

5. **Copy Files/Folders from HDFS to Local File System:**
   ```bash
   hdfs dfs -copyToLocal /user/your_username/your_directory/your_file your_local_path
   ```

6. **Move File from Local to HDFS:**
   ```bash
   hdfs dfs -put your_local_path/your_file /user/your_username/your_directory/
   ```

7. **Copy Files Within HDFS:**
   ```bash
   hdfs dfs -cp /user/your_username/source_dir/* /user/your_username/destination_dir/
   ```

8. **Move Files Within HDFS:**
   ```bash
   hdfs dfs -mv /user/your_username/source_dir/your_file /user/your_username/destination_dir/
   ```

9. **Size of Each File in Directory:**
   ```bash
   hdfs dfs -du -h /user/your_username/your_directory/
   ```

10. **Total Size of Directory/File:**
    ```bash
    hdfs dfs -du -s -h /user/your_username/your_directory/
    ```

11. **Last Modified Time of Directory or Path:**
    ```bash
    hdfs dfs -stat "%Y" /user/your_username/your_directory/
    ```

12. **Change the Replication Factor of a File/Directory in HDFS:**
    ```bash
    hdfs dfs -setrep -w 3 /user/your_username/your_directory/your_file
    ```

13. **List Contents of a Directory in HDFS:**
    ```bash
    hdfs dfs -ls /user/your_username/your_directory/
    ```

14. **Remove a File from HDFS:**
    ```bash
    hdfs dfs -rm /user/your_username/your_directory/your_file
    ```

15. **Change File Permissions:**
    ```bash
    hdfs dfs -chmod 755 /user/your_username/your_directory/your_file
    ```

16. **Changing File Ownership:**
    ```bash
    hdfs dfs -chown new_owner:new_group /user/your_username/your_directory/your_file
    ```

17. **Checksum Calculation:**
    ```bash
    hdfs dfs -checksum /user/your_username/your_directory/your_file
    ```

18. **File Concatenation:**
    ```bash
    hdfs dfs -getmerge /user/your_username/source_dir/ /your_local_path/combined_file
    ```

19. **File Compression/Decompression:**
    ```bash
    hdfs dfs -Dmapreduce.output.fileoutputformat.compress=true -Dmapreduce.output.fileoutputformat.compress.codec=org.apache.hadoop.io.compress.GzipCodec -Dmapreduce.output.fileoutputformat.compress.type=BLOCK -cp /user/your_username/source_dir/* /user/your_username/destination_dir/
    ```

20. **File Block Location Information:**
    ```bash
    hdfs fsck /user/your_username/your_directory/your_file -files -blocks -locations
    ```

21. **File Encryption/Decryption:**
    (Assuming Hadoop is configured with encryption)
    ```bash
    hdfs crypto -createZone -keyName zone_key -path /user/your_username/your_directory/
    ```