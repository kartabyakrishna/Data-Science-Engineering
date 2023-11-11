<?php
    $d = date('d-m-Y H:i:s');
    if(isset($_COOKIE["lasttime"])){
        $time = $_COOKIE["lasttime"];
        echo "CURRENT TIME IS $d\n";
        echo "the last visited time is $time";
        setcookie("lasttime",$d,time()+3600,'/');
    }
    else{
        echo "CURRENT TIME IS $d\n";
        setcookie("lasttime",$d,time()+3600,'/');
        echo "cookie set for $d";
    }

?>