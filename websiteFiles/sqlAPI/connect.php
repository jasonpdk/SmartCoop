<?php
  $servername = "localhost";
  $username = "SmartCoopUser";
  $password = "password";
  $dbname = "SmartCoop";

  $conn = new mysqli($servername, $username, $password, $dbname);

  if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
  }

?>
