<?php
// Hardcoded user data
$users = array(
    'user1' => array(
        'firstname' => 'John',
        'lastname' => 'Doe',
        'address' => '123 Main St',
        'phone' => '555-1234',
        'course' => 'Course 1'
    ),
    'user2' => array(
        'firstname' => 'Jane',
        'lastname' => 'Smith',
        'address' => '456 Elm St',
        'phone' => '555-5678',
        'course' => 'Course 2'
    ),
    'user3' => array(
        'firstname' => 'Alice',
        'lastname' => 'Johnson',
        'address' => '789 Oak St',
        'phone' => '555-9012',
        'course' => 'Course 3'
    ),
    'user4' => array(
        'firstname' => 'Bob',
        'lastname' => 'Brown',
        'address' => '101 Pine St',
        'phone' => '555-3456',
        'course' => 'Course 1'
    ),
    'user5' => array(
        'firstname' => 'Eve',
        'lastname' => 'Williams',
        'address' => '202 Cedar St',
        'phone' => '555-7890',
        'course' => 'Course 2'
    )
);

// Check if the form is submitted
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Retrieve user input
    $username = $_POST['username'];

    // Check if the entered username exists in the array
    if (array_key_exists($username, $users)) {
        // Store user information in a session
        session_start();
        $_SESSION['user_info'] = $users[$username];

        // Store user information in a cookie
        setcookie('user_info', json_encode($users[$username]), time() + 3600);

        // Redirect back to the form page
        header('Location: index.html');
    } else {
        echo "Username not found.";
    }
} else {
    echo "Invalid request.";
}
?>
