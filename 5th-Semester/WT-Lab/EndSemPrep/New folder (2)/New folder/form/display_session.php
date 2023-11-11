<?php
session_start();

// Display the contents of the user_info session variable
if (isset($_SESSION["user_info"])) {
    echo "<h2>Session Data</h2>";
    echo "<pre>";
    var_dump($_SESSION["user_info"]);
    echo "</pre>";
} else {
    echo "Session data not found.";
}
?>
