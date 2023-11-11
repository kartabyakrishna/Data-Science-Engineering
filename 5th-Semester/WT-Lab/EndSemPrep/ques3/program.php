<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST["username"];
    $first_name = $_POST["first_name"];
    $last_name = $_POST["last_name"];
    $address = $_POST["address"];
    $phone_number = $_POST["phone_number"];
    $course = $_POST["course"];

    // Define a hardcoded array of user records
    $userRecords = array(
        "user1" => array(
            "first_name" => "John",
            "last_name" => "Doe",
            "address" => "123 Main St",
            "phone_number" => "123-456-7890",
            "course" => "Math"
        ),
        "user2" => array(
            "first_name" => "Jane",
            "last_name" => "Smith",
            "address" => "456 Elm St",
            "phone_number" => "555-123-4567",
            "course" => "Science"
        )
        // Add more user records as needed
    );

    if (array_key_exists($username, $userRecords)) {
        // User already exists, display welcome message
        echo "Welcome, $username!<br>";
    } else {
        // User does not exist, add to the list
        $userRecords[$username] = array(
            "first_name" => $first_name,
            "last_name" => $last_name,
            "address" => $address,
            "phone_number" => $phone_number,
            "course" => $course
        );
        echo "Welcome, you've signed up and can enjoy your course!<br>";
    }

    // Store user information in a cookie
    setcookie("user_info", json_encode($userRecords), time() + 3600, "/");

    // Store user information in a session variable
    session_start();
    $_SESSION["user_info"] = $userRecords;

    // Display user information in a table
    echo "<h2>User Information</h2>";
    echo "<table border='1'>";
    echo "<tr><th>Username</th><th>First Name</th><th>Last Name</th><th>Address</th><th>Phone Number</th><th>Course</th></tr>";
    foreach ($userRecords as $user => $info) {
        echo "<tr>";
        echo "<td>$user</td>";
        echo "<td>{$info['first_name']}</td>";
        echo "<td>{$info['last_name']}</td>";
        echo "<td>{$info['address']}</td>";
        echo "<td>{$info['phone_number']}</td>";
        echo "<td>{$info['course']}</td>";
        echo "</tr>";
    }
    echo "</table>";
}
?>
