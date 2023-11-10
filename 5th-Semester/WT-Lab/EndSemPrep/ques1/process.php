<?php
// Hardcoded user details
$users = array(
    "user1" => array("email" => "user1@example.com", "phone" => "123-456-7890", "designation" => "Manager"),
    "user2" => array("email" => "user2@example.com", "phone" => "987-654-3210", "designation" => "Developer"),
    "user3" => array("email" => "user3@example.com", "phone" => "555-555-5555", "designation" => "Designer"),
    "user4" => array("email" => "user4@example.com", "phone" => "999-999-9999", "designation" => "Analyst"),
    "user5" => array("email" => "user5@example.com", "phone" => "777-777-7777", "designation" => "Assistant")
);

if (isset($_POST["username"])) {
    $username = $_POST["username"];
    if (array_key_exists($username, $users)) {
        $userDetails = $users[$username];
        echo "Username: " . $username . "<br>";
        echo "Email: " . $userDetails["email"] . "<br>";
        echo "Phone: " . $userDetails["phone"] . "<br>";
        echo "Designation: " . $userDetails["designation"];
    } else {
        echo "User not found.";
    }
}
?>
