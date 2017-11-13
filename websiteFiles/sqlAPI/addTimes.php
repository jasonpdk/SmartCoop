<?php
  include 'connect.php';

  $sql = "INSERT INTO SmartCoop.times (sunrise, sunset) VALUES ('".$_GET["sunrise"]."', '".$_GET["sunset"]."')";

  if ($conn->query($sql) === TRUE) {
      echo "New record created successfully";
  }
  else {
      echo "Error: " . $sql . "<br>" . $conn->error;
  }

  $conn->close();
?>
