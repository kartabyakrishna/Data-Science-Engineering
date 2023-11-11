<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST["username"];
    $first_name = $_POST["first_name"];
    $last_name = $_POST["last_name"];
    $address = $_POST["address"];
    $phone_number = $_POST["phone_number"];
    $course = $_POST["course"];

    // Connect to the MySQL database
    $conn = new mysqli("localhost", "root", "", "user_registration");

    // Check the connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    // Check if the username already exists in the database
    $checkQuery = "SELECT * FROM users WHERE username = '$username'";
    $result = $conn->query($checkQuery);

    if ($result->num_rows > 0) {
        // User already exists, display welcome message
        echo "Welcome, $username!<br>";
    } else {
        // User does not exist, add to the database
        $insertQuery = "INSERT INTO users (username, first_name, last_name, address, phone_number, course)
                        VALUES ('$username', '$first_name', '$last_name', '$address', '$phone_number', '$course')";
        if ($conn->query($insertQuery) === TRUE) {
            echo "Welcome, you've signed up and can enjoy your course!<br>";
        } else {
            echo "Error: " . $insertQuery . "<br>" . $conn->error;
        }
    }

    // Display user information from the database
    echo "<h2>User Information</h2>";
    echo "<table border='1'>";
    echo "<tr><th>Username</th><th>First Name</th><th>Last Name</th><th>Address</th><th>Phone Number</th><th>Course</th></tr>";
    $selectQuery = "SELECT * FROM users";
    $result = $conn->query($selectQuery);
    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            echo "<tr>";
            echo "<td>{$row['username']}</td>";
            echo "<td>{$row['first_name']}</td>";
            echo "<td>{$row['last_name']}</td>";
            echo "<td>{$row['address']}</td>";
            echo "<td>{$row['phone_number']}</td>";
            echo "<td>{$row['course']}</td>";
            echo "</tr>";
        }
    }
    echo "</table>";

    // Close the database connection
    $conn->close();
}
?>
