<?php
  include 'connect.php';

  $sql = "INSERT INTO readings (temperature, insideTemperature, humidity) VALUES ('".$_GET["outsideTemp"]."', '".$_GET["insideTemp"]."', '".$_GET["hum"]."')";

  if ($conn->query($sql) === TRUE)
  {
      echo "New record created successfully";
  }
  else 
  {
      echo "Error: " . $sql . "<br>" . $conn->error;
  }

  $conn->close();
?>
