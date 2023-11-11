<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="w3style.css">
</head>
<body>
    <div class="container">
        <h1>UPLOAD YOUR RESUME</h1>
        <form action="upload.php" method="POST" enctype="multipart/form-data">
            <input type="file" name="resume" accept='.pdf' required>
            <button type="submit">SUBMIT</button>
        </form>
    </div>  
</body>
</html>