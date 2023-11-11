<?php
    session_start();
    if(isset($_SESSION["visited"])){
        $count = $_SESSION["visited"];
        echo "PAGE VISITED $count times";
        $_SESSION["visited"] = $_SESSION["visited"]+1;
    }
    else{
        $_SESSION["visited"] = 1;
        $count = $_SESSION["visited"];
        echo "page has been visited $count times";
    }  
?>
