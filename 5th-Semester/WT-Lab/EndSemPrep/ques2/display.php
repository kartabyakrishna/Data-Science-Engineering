<?php
// Start the session
session_start();

// Retrieve user information from the session
$userInfoFromSession = $_SESSION['user_info'];

// Retrieve user information from the cookie
$userInfoFromCookie = json_decode($_COOKIE['user_info'], true);

?>
<!DOCTYPE html>
<html>
<head>
    <title>User Information</title>
</head>
<body>
    <h2>User Information</h2>
    <table border="1">
        <tr>
            <th>Field</th>
            <th>Value (from Session)</th>
            <th>Value (from Cookie)</th>
        </tr>
        <tr>
            <td>First Name</td>
            <td><?php echo $userInfoFromSession['firstname']; ?></td>
            <td><?php echo $userInfoFromCookie['firstname']; ?></td>
        </tr>
        <tr>
            <td>Last Name</td>
            <td><?php echo $userInfoFromSession['lastname']; ?></td>
            <td><?php echo $userInfoFromCookie['lastname']; ?></td>
        </tr>
        <tr>
            <td>Address</td>
            <td><?php echo $userInfoFromSession['address']; ?></td>
            <td><?php echo $userInfoFromCookie['address']; ?></td>
        </tr>
        <tr>
            <td>Phone Number</td>
            <td><?php echo $userInfoFromSession['phone']; ?></td>
            <td><?php echo $userInfoFromCookie['phone']; ?></td>
        </tr>
        <tr>
            <td>Selected Course</td>
            <td><?php echo $userInfoFromSession['course']; ?></td>
            <td><?php echo $userInfoFromCookie['course']; ?></td>
        </tr>
    </table>
</body>
</html>
