<?php

    $json_data = '[{"name": "John", "age": 30, "city": "New York"},
    {"name": "Alice", "age": 25, "city": "Los Angeles"},
    {"name": "Bob", "age": 35, "city": "Chicago"}]';
    $decoded_data = json_decode($json_data, true);
    if ($decoded_data !== null) {
        echo "<table border=1><thead><tr><td>name</td><td>age</td><td>city</td></tr></thead><tbody>";
        foreach ($decoded_data as $item) {
            echo '<tr><td>' . $item['name'] . '</td>';
            echo '<td>' . $item['age'] . '</td>';
            echo '<td>' . $item['city'] . '</td>';
            echo '</tr>';
        }
        echo "</tbody></table>";
    } else {
        echo 'Error decoding JSON data.';
    }

?>