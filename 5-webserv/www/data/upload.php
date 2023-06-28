<?php
$targetDir = "../_uploads/";
$targetFile = $targetDir . basename($_FILES["uploadForm"]["name"]);

if ($_SERVER["REQUEST_METHOD"] === "POST" || isset($_FILES['upload'])) {
    print_r($_FILES);

    if (move_uploaded_file($_FILES["uploadForm"]["tmp_name"], $targetFile)) {
        echo "File uploaded successfully.";
    } else {
        echo "Error uploading file.";
    }
}
else
    echo "Hello World.";
?>