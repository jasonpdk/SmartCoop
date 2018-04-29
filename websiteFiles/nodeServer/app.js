// load the things we need
var express = require('express');
var mysql = require('mysql');
var fs = require('fs');

var app = express();

app.use(express.static(__dirname + '/public'));

/* GLOBALS */
var outsideTemp, insideTemp, humidity, doorStatus, lightStatus;
var sql0 = "SELECT * FROM readings ORDER BY id DESC LIMIT 1";
var sunrise, sunset;
var sql1 = "SELECT * FROM times ORDER BY id DESC LIMIT 1";
/* END GLOBALS */

/* FUNCTIONS */
function getLightStatus() {
	fs.readFile('/home/root/lightStatus.txt', 'utf8', function(err, data) {
		if (err) throw err;
		if (data[0] == 0)
		{
			lightStatus = "Off";
		}
		else
		{
			lightStatus = "On";
		}
	});
}

function getDoorStatus() {
	fs.readFile('/home/root/doorStatus.txt', 'utf8', function(err, data) {
		if (err) throw err;
		if (data[0] == 0)
		{
			doorStatus = "Closed";
		}
		else
		{
			doorStatus = "Open";
		}
	});
}

function makeSQLQueries() {
	con.query(sql0, function (err, result) {
		if (err) throw err;
		outsideTemp = result[0].temperature;
		insideTemp = result[0].insideTemperature;
		humidity = result[0].humidity;
	});

	con.query(sql1, function (err, result) {
		sunrise = result[0].sunrise;
		sunset = result[0].sunset;
	});
}
/* END FUNCTIONS */

var con = mysql.createConnection({
	host: "192.168.41.11",
	user: "root",
	password: "password",
	database: "SmartCoop"
});


con.connect(function(err) {
	if (err) throw err;
	console.log("Connected to MySQL");
});

// set the view engine to ejs
app.set('view engine', 'ejs');

// make initial queries
makeSQLQueries();

// initial status check
getDoorStatus();
getLightStatus();

// index page
app.get('/', function(req, res) {
	// query the database everytime index is requested
	makeSQLQueries();

	// get door status from text file
	getDoorStatus();
	getLightStatus();

	// put scheduled closing time string together, 1 hour later than sunset
	var sCTokens = sunset.split(':');
	var sCHour = Number(sCTokens[0])+1;
	var scheduledClosing = "0" + sCHour + ":" + sCTokens[1] + ":" + sCTokens[2];

	// get heat lamp and fan status based on temperature
	var heatLamp = "Off", fan = "Off";
	if (insideTemp <= 1)
	{
		heatLamp =  "On";
		fan = "Off";
	}
	else if (insideTemp > 26)
	{
		heatLamp = "Off";
		fan = "On";
	}
	else
	{
		heatLamp = "Off";
		fan = "Off";
	}

	res.render('pages/index', {
		insideTemp: insideTemp,
		outsideTemp: outsideTemp,
		humidity: humidity,
		sunrise: sunrise,
		sunset: sunset,
		doorStatus: doorStatus,
		scheduledOpening: sunrise,
		scheduledClosing: scheduledClosing,
		lightStatus: lightStatus,
		heatLamp: heatLamp,
		fan: fan
	});
});

// graphs page
app.get ('/graphs', function(req, res) {
	res.render('pages/graphs');
});

// camera page
app.get ('/camera', function(req, res) {
	getLightStatus();

	res.render('pages/camera', {
		lightStatus: lightStatus
	});
});

app.listen(80);
console.log('The server is on port 80');
