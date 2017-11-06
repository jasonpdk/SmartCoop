<?php
  $servername = "localhost";
  $username = "root";
  $password = "Quartsr2d2";
  $dbname = "SmartCoop";

  $conn = new mysqli($servername, $username, $password, $dbname);

  if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
  }

?>
