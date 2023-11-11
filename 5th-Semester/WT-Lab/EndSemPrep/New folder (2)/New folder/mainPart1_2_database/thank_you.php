<?php
session_start();

if (isset($_SESSION["user_details"])) {
    $user_details = $_SESSION["user_details"];
    echo "<h2>Thank you for submitting your details, " . $user_details["first_name"] . "!</h2>";
    echo "<h3>Your Details:</h3>";
    echo "<p>First Name: " . $user_details["first_name"] . "</p>";
    echo "<p>Email ID: " . $user_details["email"] . "</p>";
    echo "<p>Date of Birth: " . $user_details["dob"] . "</p>";
    echo "<p>Phone Number: " . $user_details["phone_number"] . "</p>";
    echo "<p>Designation: " . $user_details["designation"] . "</p>";
} else {
    echo "<h2>Thank you for submitting your details!</h2>";
    echo "User details not found in the session.";
}
?>
+ 