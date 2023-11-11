<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    session_start();

    $first_name = $_POST["first_name"];
    $email = $_POST["email"];
    $dob = $_POST["dob"];
    $phone_number = $_POST["phone_number"];
    $designation = $_POST["designation"];

    $_SESSION["user_details"] = array(
        "first_name" => $first_name,
        "email" => $email,
        "dob" => $dob,
        "phone_number" => $phone_number,
        "designation" => $designation
    );

    header("Location: thank_you.php");
    exit;
}
?>
