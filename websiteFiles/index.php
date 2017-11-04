<?php
  $servername = "localhost";
  $username = "root";
  $password = "Quartsr2d2";
  $dbname = "SmartCoop";

  $conn = new mysqli($servername, $username, $password, $dbname);

  if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
  }

  $sql = "SELECT * FROM readings ORDER BY id DESC LIMIT 1";

  $result = $conn->query($sql);


?>

<html>

  <head>
    <title>SmartCoop</title>
    <link rel="stylesheet" type="text/css" href="style.css" />
    <script type="text/javascript" src="javascript.js"></script>
  </head>

  <body>
    <div id="wrapper">
      <div id="header">
        <div id="logo">
          <h1>SmartCoop</h1>
          <h2>An Automated Chicken Coop</h2>
        </div>
      </div>


      <div id="navBar">
        <a class="active" href="index.php">Home</a>
        <a href="graphs.php">Graphs</a>
        <a href="camera.php">Camera</a>
      </div>


      <div id="mainContent">
        <div id="subContent">
          <h2>Sensor Readings</h2>
          <p class="readings">
            <?php
              while($row = $result->fetch_assoc())
              {
                echo "The outside temperature is " . $row['temperature'] . "<br />The inside temperature is " . $row['insideTemperature'] . "<br />The humidity is " . $row['humidity'] . "<br />";
              }
            ?>

            <a href="graphs">Click here to see the historical values on a graph.</a>
          </p>

          <h2>Sunrise and Sunset Times</h2>
          <p>
            The sunrise time today is:
            <!-- INSERT PHP --><br /> The sunset time today is:
            <!-- INSERT PHP --><br />
          </p>

          <h2>Control</h2>

          <p>Click to turn LED on and off.<br />
            <button type="button" onclick="ledOn();">On</button>
            <button type="button" onclick="ledOff();">Off</button>
          </p>


          <p>Click to open/close door.<br />
            <button type="button" onclick="openDoor();">Open</button>
            <button type="button" onclick="closeDoor();">Close</button>
          </p>

        </div>
      </div>

      <div id="footer">
        <p>SmartCoop: An Automated Chicken Coop - Jason Keane
          <p>
      </div>

    </div>
  </body>
</html>
