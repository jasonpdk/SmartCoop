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
          <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/351486/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&api_key=4FTN1ZL8P525S956&results=60&type=line&update=15"></iframe>
          <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/351486/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&api_key=4FTN1ZL8P525S956&results=60&type=line&update=15"></iframe>
          <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/351486/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&api_key=4FTN1ZL8P525S956&results=60&type=line&update=15"></iframe>
        </div>
      </div>

      <div id="footer">
        <p>SmartCoop: An Automated Chicken Coop - Jason Keane
          <p>
      </div>

    </div>
  </body>
</html>
