<?php

  $servername = "localhost";
  $username = "root";
  $password = "Quartsr2d2";
  $dbname = "SmartCoop";

  // Create connection
  $conn = new mysqli($servername, $username, $password, $dbname);

  if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
  }

  $sql = "SELECT * FROM readings ORDER BY id DESC LIMIT 1";

  $result = $conn->query($sql);

  if ($result->num_rows > 0)
  {
    while($row = $result->fetch_assoc())
    {
      //echo "humidity: " . $row["humidity"] . " Outside Temperature: " . $row["temperature"] . "Inside Temperature " . $row["insideTemperature"] . " Entered On " . $row["timeLogged"] . "<br  />";
      echo json_encode($row);
    }
  }
  else
  {
    echo "0 results";
  }

  $conn->close();
?>
