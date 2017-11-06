<html><!-- -->
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
        <a href="index.php">Home</a>
        <a href="graphs.php">Graphs</a>
        <a class="active" href="camera.php">Camera</a>
      </div>


      <div id="mainContent">
        <div id="subContent">
          <h2>SmartCoop Live Stream</h2>
          <img src="http://192.168.41.112:8080/?action=stream" />

          <p>Click to turn LED on and off.<br />
            <button type="button" onclick="ledOn();">On</button>
            <button type="button" onclick="ledOff();">Off</button>
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
