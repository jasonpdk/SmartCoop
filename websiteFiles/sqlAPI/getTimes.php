<?php
  include 'connect.php';

  $sql = "SELECT * FROM times ORDER BY id DESC LIMIT 1";

  $result = $conn->query($sql);

  if ($result->num_rows > 0)
  {
    while($row = $result->fetch_assoc())
    {
      echo json_encode($row);
    }
  }
  else
  {
    echo "0 results";
  }

  $conn->close();
?>
