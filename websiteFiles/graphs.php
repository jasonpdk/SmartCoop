<?php
  include 'connect.php';

  $sql = "SELECT * FROM ( SELECT * FROM readings ORDER BY id DESC LIMIT 100) sub ORDER BY id ASC";
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
          <h2>An Automated Chicken Coops</h2>
        </div>
      </div>


      <div id="navBar">
        <a href="index.php">Home</a>
        <a class="active" href="graphs.php">Graphs</a>
        <a href="camera.php">Camera</a>
      </div>


      <div id="mainContent">
        <div id="subContent">
          <h2>Graphs</h2>
          <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/351486/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&api_key=4FTN1ZL8P525S956&results=60&type=line&update=15"></iframe>
          <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/351486/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&api_key=4FTN1ZL8P525S956&results=60&type=line&update=15"></iframe>
          <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/351486/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&api_key=4FTN1ZL8P525S956&results=60&type=line&update=15"></iframe>
          <br /><br />
          <h2>Previous 100 Values</h2>
          <?php
            echo "<table border='1'>
            <tr>
            <th>ID</th>
            <th>Outside Temperature</th>
            <th>Inside Temperature</th>
            <th>Humidity</th>
            <th>Time Logged</th>
            </tr>";

            while($row = $result->fetch_assoc())
            {
              echo "<tr>";
              echo "<td>" . $row['id'] . "</td>";
              echo "<td>" . $row['temperature'] . "</td>";
              echo "<td>" . $row['insideTemperature'] . "</td>";
              echo "<td>" . $row['humidity'] . "</td>";
              echo "<td>" . $row['timeLogged'] . "</td>";

              echo "</tr>";
            }
            echo "</table>";
            $conn->close();
          ?>
        </div>
      </div>

      <div id="footer">
        <p>SmartCoop: An Automated Chicken Coop - Jason Keane
          <p>
      </div>

    </div>
  </body>
</html>
