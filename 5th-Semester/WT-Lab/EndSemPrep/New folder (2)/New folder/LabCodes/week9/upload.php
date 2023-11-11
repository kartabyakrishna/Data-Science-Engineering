<?php
    $file_name = $_FILES["resume"]["name"];
    $file_size = $_FILES["resume"]["size"];
    $tmp_name = $_FILES["resume"]["tmp_name"];
    $error = $_FILES["resume"]["error"];

    $img_ex = pathinfo($file_name, PATHINFO_EXTENSION);
    $img_ex_lc = strtolower($img_ex);
    $new_file_name = uniqid("PDF-",true).'.'.$img_ex_lc;

    $file_upload_path = 'uploads/'.$new_file_name;
    if(move_uploaded_file($tmp_name,$file_upload_path)){
        echo "File uploaded successfully";
    }
    else{
        echo "PROBLEM UPLOADING FILE";
    }
?>