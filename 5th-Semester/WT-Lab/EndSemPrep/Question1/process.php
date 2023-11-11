<?php
// Hardcoded user data
$users = array(
    array("username" => "user1", "email" => "user1@example.com", "phone" => "123-456-7890", "designation" => "Developer"),
    array("username" => "user2", "email" => "user2@example.com", "phone" => "234-567-8901", "designation" => "Designer"),
    array("username" => "user3", "email" => "user3@example.com", "phone" => "345-678-9012", "designation" => "Manager"),
    array("username" => "user4", "email" => "user4@example.com", "phone" => "456-789-0123", "designation" => "Admin"),
    array("username" => "user5", "email" => "user5@example.com", "phone" => "567-890-1234", "designation" => "Support")
);

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'];
    $email = $_POST['email'];
    $designation = $_POST['designation'];
    
    // Find the user by username
    $user = array_filter($users, function($user) use ($username) {
        return $user['username'] === $username;
    });

    if (!empty($user)) {
        // Return the user's information including email and designation as JSON
        $userData = array_shift($user);
        echo json_encode(array(
            "username" => $userData['username'],
            "email" => $userData['email'],
            "designation" => $userData['designation']
        ));
    } else {
        // Return a 404 status code to indicate user not found
        http_response_code(404);
    }
}
?>
