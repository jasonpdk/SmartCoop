<?php
  include 'connect.php';

  // readings
  $sql = "SELECT * FROM readings ORDER BY id DESC LIMIT 1";
  $result = $conn->query($sql);

  $row = $result->fetch_assoc();
  echo "{";
  echo "\"readings\":";
  echo json_encode($row);


  // times request
  $sql = "SELECT * FROM times ORDER BY id DESC LIMIT 1";
  $result = $conn->query($sql);

  $row = $result->fetch_assoc();
  echo ",\"times\":";
  echo json_encode($row);
  echo "}";

  $conn->close();
?>
