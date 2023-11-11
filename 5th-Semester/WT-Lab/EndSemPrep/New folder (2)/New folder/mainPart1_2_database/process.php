<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    session_start();

    // Get user details from the form
    $first_name = $_POST["first_name"];
    $email = $_POST["email"];
    $dob = $_POST["dob"];
    $phone_number = $_POST["phone_number"];
    $designation = $_POST["designation"];

    // Store user details in a session variable
    $_SESSION["user_details"] = array(
        "first_name" => $first_name,
        "email" => $email,
        "dob" => $dob,
        "phone_number" => $phone_number,
        "designation" => $designation
    );

    // Connect to the MySQL database
    $conn = new mysqli("localhost", "root", "", "user_registration");

    // Check the connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    // Insert user details into the database
    $insertQuery = "INSERT INTO users (first_name, email, dob, phone_number, designation) 
                    VALUES ('$first_name', '$email', '$dob', '$phone_number', '$designation')";

    if ($conn->query($insertQuery) === TRUE) {
        header("Location: thank_you.php");
        exit;
    } else {
        echo "Error: " . $insertQuery . "<br>" . $conn->error;
    }

    // Close the database connection
    $conn->close();
}
?>
