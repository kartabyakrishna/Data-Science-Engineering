<?php
// Start a PHP session
session_start();

// Define an array of user details (hardcoded for this example)
$users = array(
    "user1" => array(
        "email" => "user1@example.com",
        "phone" => "123-456-7890",
        "designation" => "Designer"
    ),
    "user2" => array(
        "email" => "user2@example.com",
        "phone" => "987-654-3210",
        "designation" => "Developer"
    ),
    "user3" => array(
        "email" => "user3@example.com",
        "phone" => "555-555-5555",
        "designation" => "Manager"
    ),
    "user4" => array(
        "email" => "user4@example.com",
        "phone" => "111-222-3333",
        "designation" => "Marketing"
    ),
    "user5" => array(
        "email" => "user5@example.com",
        "phone" => "777-888-9999",
        "designation" => "Sales"
    )
);

if ($_SERVER["REQUEST_METHOD"] === "POST" && isset($_POST["username"])) {
    $username = $_POST["username"];
    if (array_key_exists($username, $users)) {
        // Store the username in a session variable
        $_SESSION["username"] = $username;
        // Return the user details as a JSON response
        $userDetails = $users[$username];
        echo json_encode($userDetails);
    } else {
        // Username not found
        echo json_encode(null);
    }
} else {
    // Invalid request
    echo json_encode(null);
}
?>
