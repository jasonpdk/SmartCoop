<?php
$servername = "localhost";
$username = "root";
$password = "***REMOVED***";
$dbname = "SmartCoop";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "INSERT INTO readings (temperature, insideTemperature, humidity) VALUES ('".$_GET["outsideTemp"]."', '".$_GET["insideTemp"]."', '".$_GET["hum"]."')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
