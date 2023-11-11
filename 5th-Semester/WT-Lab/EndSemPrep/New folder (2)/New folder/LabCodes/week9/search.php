<?php
// Assuming you have data or a database where you perform the search

if (isset($_GET['q'])) {
    // Get the search query from the GET parameters
    $searchQuery = $_GET['q'];

    // Perform the search (replace this with your search logic)
    // For demonstration, a simple array of items is used for search
    $items = ['Apple', 'Banana', 'Orange', 'Pear', 'Pineapple'];

    $searchQuery = strtolower($searchQuery);
    $matches = [];

    foreach ($items as $item) {
        if (stripos($item, $searchQuery) !== false) {
            $matches[] = $item;
        }
    }

    // Output the search results
    if (empty($matches)) {
        echo 'No results found.';
    } else {
        echo 'Search Results:<br>';
        foreach ($matches as $match) {
            echo $match . '<br>';
        }
    }
} else {
    echo 'Invalid search query.';
}
?>
