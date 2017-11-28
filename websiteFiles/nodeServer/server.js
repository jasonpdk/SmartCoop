// load the things we need
var express = require('express');
var request = require('request');

var app = express();

app.use(express.static(__dirname + '/public'));

// set the view engine to ejs
app.set('view engine', 'ejs');


var outsideTemp, insideTemp, humidity, sunrise, sunset;

// get the initial values
getValues();

// index page
app.get('/', function(req, res) {
  getValues();

  res.render('pages/index', {
    insideTemp: insideTemp,
    outsideTemp: outsideTemp,
    humidity: humidity,
    sunrise: sunrise,
    sunset: sunset
  });
});

// graphs page
app.get('/graphs', function(req, res) {
  res.render('pages/graphs');
});

// camera page
app.get('/camera', function(req, res) {
  res.render('pages/camera');
});

app.listen(80);
console.log('The server is on port 80');


function getValues() {
  url = "http://192.168.41.112/smartcoop/getLatest.php";

  request({
      url: url,
      json: true
    },

    function(error, response, body) {
      if (response.statusCode == 200) {
        outsideTemp = body.readings.temperature;
        insideTemp = body.reading.insideTemperature;
        humidity = body.readings.humidity;
        sunrise = body.times.sunrise;
        sunset = body.times.sunset;
      }
    })
}
