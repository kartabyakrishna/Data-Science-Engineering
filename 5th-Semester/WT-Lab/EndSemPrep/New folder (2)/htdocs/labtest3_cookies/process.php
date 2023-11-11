<?php
// Hardcoded user details
$users = array(
    'user1' => array('email' => 'user1@example.com', 'phone' => '1234567890', 'designation' => 'Developer'),
    'user2' => array('email' => 'user2@example.com', 'phone' => '9876543210', 'designation' => 'Designer'),
    'user3' => array('email' => 'user3@example.com', 'phone' => '5555555555', 'designation' => 'Manager'),
    'user4' => array('email' => 'user4@example.com', 'phone' => '1111111111', 'designation' => 'Tester'),
    'user5' => array('email' => 'user5@example.com', 'phone' => '9999999999', 'designation' => 'Analyst')
);

// Get the username from the query parameters
$username = $_GET['username'];

// Check if the username exists in the array
if (array_key_exists($username, $users)) {
    // If it exists, send the details as a JSON response
    $userDetails = $users[$username];
    echo json_encode($userDetails);

    // Set a cookie with the username
    setcookie('username', $username, time() + (86400 * 30), "/"); // Cookie valid for 30 days
} else {
    // If not, send an error message
    echo 'User not found';

    // Set a cookie with the entered username
    setcookie('username', $username, time() + (86400 * 30), "/"); // Cookie valid for 30 days
}
?>
